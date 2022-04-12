#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "ELTMSGprimitives.h"
#include "../SMS/SDD_SMS.h"

void heureLire(HEURE * h) {
    time_t s;
    struct tm* current_time;
    // time in seconds
    s = time(NULL);
    // to get current time
    current_time = localtime(&s);
    h->seconde = current_time->tm_sec;
    h->minute = current_time->tm_min;
    h->heure = current_time->tm_hour;
}

void dateLire(DATE * d) {
    time_t ss;
    struct tm* current_time2;
    // time in seconds
    ss = time(NULL);
    // to get current time
    current_time2 = localtime(&ss);
    d->jour = current_time2->tm_mday;
    d->mois = current_time2->tm_mon + 1;
    d->annee = current_time2->tm_year + 1900;
}

void dateAffichage(DATE d) {
    printf("%02d,%02d,%04d",d.jour,d.mois,d.annee);
}

void heureAffichage(HEURE h) {
    printf("%02d:%02d:%02d",h.heure,h.minute,h.seconde);
}


ELEMENT_MSG MSGelementCreer (void) {
    ELEMENT_MSG e;
    e = (ELEMENT_MSG)malloc(sizeof(MESSAGE));
    return e;
}

void MSGelementDetruire (ELEMENT_MSG elt) {
    SMSlisteDetruire(elt->msg);
    free(elt);
}

void MSGelementAffecter(ELEMENT_MSG * e1, ELEMENT_MSG e2) {
    *e1 = e2 ;
}

void MSGelementCopier(ELEMENT_MSG * e1, ELEMENT_MSG e2) {
    *e1 = e2 ;
}

void MSGelementLire(ELEMENT_MSG * elt) {
    int i,test = 0;
    do {
        clearBuffer();
        printf("\nSaisir le numero de destinataire : ");
        if (!fgets((*elt)->recepteur,9,stdin)) {
            printf("Erreur");
            exit(0);
        }
        
        if ((*elt)->recepteur[0] == '5') {
            test = 1;
        } else if ((*elt)->recepteur[0] == '2') {
            test = 1;
        } else if ((*elt)->recepteur[0] == '9') {
            test = 1;
        } else {
            printf("\nLe numero de desitinataire doit commence avec 2,5 ou 9 et contient 8 chiffres");
        }
    } while (strlen((*elt)->recepteur) != 8 || test == 0);
    LISTE_SMS L = SMSlisteCreer();
    ELEMENT_SMS sms;

    //Lire le message a envoyer
    char smsTemp[1224];
    printf("\nSaisir le texte à envoyer : ");
    clearBuffer();
    fflush(stdin);
    
    if(!fgets(smsTemp,1224,stdin)) {
        printf("\nErreur");
        exit(0);
    }

    //Taille de message
    size_t typeSMS;
    if (type_de_SMS(smsTemp) != -1) {
        typeSMS = 67;
        // printf("\nSMS speciale");
    } else {
        typeSMS = 153;
        // printf("\nSMS standard");
    }

    //Nombre de SMS
    double c = ceil(strlen(smsTemp) / typeSMS) + 1;
    if (c == 1) {
        if (typeSMS == 67) {
            typeSMS = 70;
        } else {
            typeSMS = 160;
        }
    }
    // printf("\nL'Operation : %ld / %ld", strlen(smsTemp), typeSMS);
    c = (int)(c);
    int p = 0;
    char temp[typeSMS + 1];
    if(c == 1) {
        sms = SMSelementCreer();
        SMSelementLire(&sms,smsTemp);
        SMSinserer(L,sms,1);
    } else {
        printf("\nTESTTT c = %f",c);
        for (i = 1; i <= c; i++) {
            printf("\nTESTTT i = %d",i);
            sms = SMSelementCreer();
            // printf("\nTEST smsTEMP = \"%s\" la taille de ce message est : %ld",smsTemp,strlen(smsTemp));
            strncpy(temp,smsTemp + p,typeSMS + 1);
            temp[typeSMS + 1] = '\0';
            // printf("\n|THIS IS A TEST temp = \"%s\"",temp);
            // printf("\n|THIS IS A TEST i = %d; Lenght(Temp) = %ld; Longueur d'un sms : %ld",i,strlen(temp),typeSMS);
            SMSelementLire(&sms,temp);
            SMSinserer(L,sms,i);
            p += typeSMS + 1;
        }
    }
    
    (*elt)->msg = L; 
    (*elt)->prix = 0.050 * c;
    dateLire(&(*elt)->date_envoi);
    heureLire(&(*elt)->heure_envoi);
}

void MSGelementAfficher(ELEMENT_MSG elt) {
    printf("\n--------");
    printf("\nAffichage de conversation est en cours... :");
    printf("%s ",elt->recepteur);
    // SMSlisteAfficher(elt->msg);

    /* test */
    char * ch;
    ch = (char *)malloc(sizeof(500));
    for (int i = 1; i <= SMSlisteTaille(elt->msg); i++) {
        strcat(ch,elt->msg->elements[i]->text);
    }
    ch[strlen(ch)+1] = '\0';
    /* test */
    printf("\nMessage : %s",ch);
    free(ch);
    printf("\n");
    int typeSMS = -1;
    int i = 1; 
    do {
        if (type_de_SMS(elt->msg->elements[i]->text) != -1) {
            typeSMS = 1;
        }
        i++;
    } while (typeSMS == -1 && i <= SMSlisteTaille(elt->msg));
    int nbrChar,nbrSMS = SMSlisteTaille(elt->msg);
    if (typeSMS == -1) {
        nbrChar = 153;
    } else {
        nbrChar = 67;
    }
    if (nbrSMS == 1) {
        if (typeSMS == 67) {
            typeSMS = 70;
        } else {
            typeSMS = 160;
        }
    }
    printf("(%d) - %d/%d ",nbrSMS,elt->msg->elements[SMSlisteTaille(elt->msg)]->taille + (nbrChar * (nbrSMS - 1)),nbrChar*nbrSMS);
    heureAffichage(elt->heure_envoi);
    printf(" | ");
    dateAffichage(elt->date_envoi);
    printf(" | Prix : %.3f",elt->prix);
    printf("\n--------");
}

int MSGelementComparer(ELEMENT_MSG e1, ELEMENT_MSG e2) {
    return e1->prix - e2->prix;
}