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

    smsTemp[strcspn(smsTemp, "\n")] = 0;

    printf("\nTaille original : %ld",strlen(smsTemp) - 1);
    printf("\nRetour de type_de_SMS : %d",type_de_SMS(smsTemp));
    size_t length =  strlen(smsTemp) - 1 - type_de_SMS(smsTemp);
    printf("\nTaille finale : %ld",length);

    //Taille de message
    size_t typeSMS;
    if (type_de_SMS(smsTemp) != 0) {
        typeSMS = 67;
        // printf("\nSMS speciale");
    } else {
        typeSMS = 153;
        // printf("\nSMS standard");
    } 
    //Nombre de SMS
    double fractpart,intpart,c;
    if (type_de_SMS(smsTemp) != 0){
        if (length <= 70) {
            c = 1;
        } else {
            fractpart = modf(length / 67, &intpart);
            c = intpart + (1 - fractpart);
        }
    } else {
        if (length <= 160) {
            c = 1;
        } else {
            fractpart = modf(length / 153, &intpart);
            c = intpart + (1 - fractpart) ;
        }
    }
    printf("\nTESTTT c = %f",c);
    if (c == 1) {
        if (typeSMS == 67) {
            typeSMS = 70;
        } else {
            typeSMS = 160;
        }
    }
    // printf("\nL'Operation : %ld / %ld", strlen(smsTemp), typeSMS);
    c = (int)(c);
    char temp[typeSMS + 1];
    if(c == 1) {
        sms = SMSelementCreer();
        SMSelementLire(&sms,smsTemp);
        SMSinserer(L,sms,1);
    } else {
        // for (i = 1; i <= c; i++) {
        //     printf("\nTESTTT i = %d",i);
        //     sms = SMSelementCreer();
        //     // printf("\nTEST smsTEMP = \"%s\" la taille de ce message est : %ld",smsTemp,strlen(smsTemp));
        //     strncpy(temp,smsTemp + p,typeSMS);
        //     temp[typeSMS] = '\0';
        //     temp[strcspn(temp, "\n")] = 0;
        //     // printf("\n|THIS IS A TEST temp = \"%s\"",temp);
        //     // printf("\n|THIS IS A TEST i = %d; Lenght(Temp) = %ld; Longueur d'un sms : %ld",i,strlen(temp),typeSMS);
        //     SMSelementLire(&sms,temp);
        //     SMSinserer(L,sms,i);
        //     p += typeSMS;
        // }
        int c1,c2,k1,k2;
        int j,charFound = 0;
        int pq = 0;
        char carSpe[50] = "çœàéè";
        int nb_car_spe = 0,nb_car_a_copier = 0;
        for (int pos = 1; pos <= c; pos++) {
            memset(temp,0,strlen(temp));
            sms = SMSelementCreer();
            nb_car_spe = 0;
            nb_car_a_copier = 0;
            j = 0;
            while(nb_car_a_copier < typeSMS && pq < strlen(smsTemp)) {
                if (smsTemp[pq + j] == '\0'){
                    printf("\nsmsTemp est finie");
                    break;
                }
                charFound = 0;
                c1 = (int)(smsTemp[j+pq]);
                c2 = (int)(smsTemp[j+pq+1]);
                for (i = 0; i <= strlen(carSpe); i+=2){
                    k1 = (int)(carSpe[i]);
                    k2 = (int)(carSpe[i+1]);
                    if (c1 == k1 && c2 == k2 && charFound == 0){
                        strncat(temp,smsTemp + j + pq ,2);
                        j+=2;
                        charFound = 1;
                        nb_car_spe++;
                        nb_car_a_copier++;
                    } 
                }
                if (charFound == 0) {
                    strncat(temp,smsTemp + j + pq,1);
                    strcat(temp,"\0");
                    j++;
                    nb_car_a_copier++;
                }
                /* lezem kol caractere men smsTemp nchoufou speciale wala le 
                donc lezemni kol caracter naamel parcours mteouu al carSpe */
                
            }
        
            printf("\n nb_car_a_copier = %d",nb_car_a_copier);
            pq += nb_car_a_copier + nb_car_spe;
            temp[strlen(temp)] = '\0';
            temp[strcspn(temp, "\n")] = 0;
            printf("\n\n|THIS IS A TEST temp = \"%s\"",temp);
            SMSelementLire(&sms,temp);
            SMSinserer(L,sms,pos);
            // p += typeSMS + somme;
        }
    
    }
    
    (*elt)->msg = L; 
    (*elt)->prix = 0.050 * c;
    dateLire(&(*elt)->date_envoi);
    heureLire(&(*elt)->heure_envoi);
}

void MSGelementAfficherMSGcomplet(ELEMENT_MSG elt) {
    printf("\n--------");
    printf("\nAffichage de conversation est en cours... :");
    printf("%s ",elt->recepteur);

    char ch[1225] = "";
    for (int i = 1; i <= SMSlisteTaille(elt->msg); i++) {
        strncat(ch,elt->msg->elements[i]->text,elt->msg->elements[i]->taille + 1 + type_de_SMS(elt->msg->elements[i]->text));
    }
    // ch[strlen(ch)+1] = '\0';
    printf("\nMessage : -%s-",ch);
    printf("\n");
    
    int somme = 0;
    for (int k = 1; k <= SMSlisteTaille(elt->msg); k++) {
        somme += elt->msg->elements[k]->taille;
    }

    int typeSMS = 0;
    int i = 1; 
    do {
        if (type_de_SMS(elt->msg->elements[i]->text) != 0) {
            typeSMS = 1;
        }
        i++;
    } while (typeSMS == 0 && i <= SMSlisteTaille(elt->msg));
    
    int nbrChar,nbrSMS = SMSlisteTaille(elt->msg);
    if (typeSMS == 0) {
        nbrChar = 153;
    } else {
        nbrChar = 67;
    }
    if (nbrSMS == 1) {
        if (nbrChar == 67) {
            nbrChar = 70;
        } else {
            nbrChar = 160;
        }
    }
    printf("(%d) - %d/%d ",nbrSMS,somme,nbrChar*nbrSMS);
    heureAffichage(elt->heure_envoi);
    printf(" | ");
    dateAffichage(elt->date_envoi);
    printf(" | Prix : %.3f",elt->prix);
    printf("\n--------");
}

void MSGelementAfficherParSMS(ELEMENT_MSG elt) {
    printf("\n--------");
    printf("\nAffichage de conversation est en cours... :");
    printf("%s ",elt->recepteur);
    
    SMSlisteAfficher(elt->msg);
    
    int somme = 0;
    for (int k = 1; k <= SMSlisteTaille(elt->msg); k++) {
        // somme += elt->msg->elements[k]->taille;
        somme += strlen(elt->msg->elements[k]->text);
    }
    printf("\nNombre de caracters : %d",somme);
    // char ch[somme + 1];
    char *ch = calloc(1,somme + 2); //+2 because I need another byte for space character unigrammes/bigrammes 
    for (int i = 1; i <= SMSlisteTaille(elt->msg); i++) {
        strncat(ch,elt->msg->elements[i]->text,elt->msg->elements[i]->taille + 1);
    }
    // ch[somme + 2] = '\0';

    int nbrChar,type_de_sms_var = 0;
    type_de_sms_var = type_de_SMS(ch);
    if(type_de_sms_var != 0) {
        nbrChar = 70;
        if (SMSlisteTaille(elt->msg) != 1) {
            nbrChar = 67;
        }
    } else {
        nbrChar = 160;
        if (SMSlisteTaille(elt->msg) != 1) {
            nbrChar = 153;
        }
    }
    printf("\n(%d), %d/%d ",SMSlisteTaille(elt->msg),somme,nbrChar * SMSlisteTaille(elt->msg));
    heureAffichage(elt->heure_envoi);
    printf(" | ");
    dateAffichage(elt->date_envoi);
    printf(" | Prix : %.3f",elt->prix);
    printf("\n--------");

    free(ch);
}

int MSGelementComparer(ELEMENT_MSG e1, ELEMENT_MSG e2) {
    return e1->prix - e2->prix;
}