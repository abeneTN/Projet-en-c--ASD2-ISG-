#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
// #include <sys/resource.h>

#include "headers/SDD.h"

//Beta (mot vides)
Pile unigrammesBeta(LISTE_MSG L, int M);
Pile bigrammesBeta(LISTE_MSG L, int M);
//Compte l'occurence de chanque mot
Pile unigrammes(LISTE_MSG L,int m);
Pile bigrammes(LISTE_MSG L, int M);
// Le contact plus contacté(e) dans la répertoire
CONTACT lePlusContacte (LISTE_MSG liste_message, LISTE_CONT liste_contact);
// Liste de contact qui contient les contact jamais messagés dans la répertoire
LISTE_CONT jamaisContactes(LISTE_MSG liste_message, LISTE_CONT liste_contact);
// Les messages entre deux dates
LISTE_MSG messages_D1_D2(LISTE_MSG liste_message, DATE D1, DATE D2);
// Le message le plus long dans tout les temps
ELEMENT_MSG messageLePlusLong(LISTE_MSG liste_message);
char * divideFile(char ch[]);

int motJamaisTraite(char mot[], TABLEAU_COMPARISON T, int n);



int main(void) {
    DATE D1 ,D2 ;
    int choix,m;
    LISTE_CONT repertoire = CONTlisteCreer(),contTemp;
    ELEMENT_CONT contact;
    LISTE_MSG bote_de_messagerie = MSGlisteCreer();
    ELEMENT_MSG message;
    ELEMENT_SMS sms;
    Pile p,pb;
    CONTACT cont;

    //Read from file
    FILE *fileContact, *fileMessage, *file;
    char lineContact[100];
    char line[1225];
    size_t plus = 0, size = 0;
    int i;
    char dj[3] = "";
    char dja[5] = "";
    char smsTemp[1225];
    
    do {
        printf("\n11 - Clear screen\n\n");
        printf("\n22 - Renvoie les M unigrammes les plus envoyés (mot vides - beta)");
        printf("\n33 - Renvoie les M bigrammes les plus envoyés (mot vides - beta)");
        printf("\n44 - (meme fichier) Ajouter des contacts et messages");
        printf("\n\n--REPERTOIRE--");
        printf("\n1 - Ajouter un contact au liste de répertoire");
        printf("\n2 - Afficher la répertoire");
        printf("\n3 - Le contact du répertoire auquel le plus grand nombre de messages a été envoyé");
        printf("\n4 - La liste des contacts auxquels aucun message n’a jamais été envoyé.");
        printf("\n\n--BOITE DE RECEPTION--");
        printf("\n5 - Envoyer un message");
        printf("\n6 - Consulter la boite de messagerie");
        printf("\n7 - Renvoyer tous les messages qui ont été envoyés entre les dates D1 et D2.");
        printf("\n8 - Retourne le message envoyé le plus long en terme de caractères.");
        printf("\n9 - Renvoie les M unigrammes les plus envoyés (dans tous les messages)");
        printf("\n 10 - Renvoie les M bigrammes les plus envoyés (dans tous les messages)");
        printf("\n\nChoisir une option svp : ");
        if (!scanf("%d",&choix)) {
            printf("\nErreur");
            exit(0);
        }
        
        switch (choix) {
        case 0:
            CONTlisteDetruire(repertoire);
            MSGlisteDetruire(bote_de_messagerie); /*inclus : SMSlisteDetruire(p->info->msg)*/
            break;
        case 1:
            contact = CONTelementCreer();
            CONTelementLire(&contact);
            CONTinserer(repertoire,contact);
            break;
        case 2:
            CONTlisteAfficher(repertoire);
            break;
        case 3:
            if (CONTlisteTaille(repertoire) == 0) {
                printf("\nAucun contact enrigistré touvé(e)");
            }
            if (MSGlisteTaille(bote_de_messagerie) == 0) {
                printf("\nAucun message n'a ete envoyer");
            } else {
                cont = lePlusContacte(bote_de_messagerie,repertoire) ;
                if (strlen(cont.nom) != 0) {
                    printf("\nLe plus contacté(e) : ");
                    printf("\nNom : %s",lePlusContacte(bote_de_messagerie,repertoire).nom);
                    printf("\nNumero : %s",lePlusContacte(bote_de_messagerie,repertoire).numero);
                    printf("\nEmail : %s",lePlusContacte(bote_de_messagerie,repertoire).email);
                } else {
                    printf("\nAucun message correspond a un contact enrigistré !");
                }
            }
            break;
        case 4: 
            printf("\nListe de contact jamais contactes : \n");
            if (CONTlisteTaille(repertoire) == 0) {
                printf("\nAucun contact enrigistré(e) dans le repertoire");
            } else {
                contTemp = jamaisContactes(bote_de_messagerie,repertoire);
                CONTlisteAfficher(contTemp);
            }
            break;
        case 5:
            message = MSGelementCreer();
            MSGelementLire(&message);
            MSGinserer(bote_de_messagerie,message,1);
            break;
        case 6:
            if (bote_de_messagerie->lg == 0) {
                printf("\nAucun message n'a jamais été envoyé");
            } else {
                printf("\n(--------Vous avez %d messages envoyés--------)",bote_de_messagerie->lg);
                MSGlisteAfficher(bote_de_messagerie);
            }
            break;
        case 7 :
            printf("\nSaisir l'année D1 : ");
            if(!scanf("%d",&D1.annee)) {
                printf("\nErreur");
                exit(0);
            }
            printf("\nSaisir le mois D1 : ");
            if(!scanf("%d",&D1.mois)) {
                printf("\nErreur");
                exit(0);
            }
            printf("\nSaisir le jour D1 : ");
            if(!scanf("%d",&D1.jour)) {
                printf("\nErreur");
                exit(0);
            }
            printf("\nSaisir l'année D2 : ");
            if(!scanf("%d",&D2.annee)) {
                printf("\nErreur");
                exit(0);
            }
            printf("\nSaisir le mois D2 : ");
            if(!scanf("%d",&D2.mois)) {
                printf("\nErreur");
                exit(0);
            }
            printf("\nSaisir le jour D2 : ");
            if(!scanf("%d",&D2.jour)){
                printf("\nErreur");
                exit(0);
            }
            if (bote_de_messagerie->lg == 0) {
                printf("\nAucun message n'a jamais été envoyé");
            } else {
                MSGlisteAfficher(messages_D1_D2(bote_de_messagerie,D1,D2));
            }
            break;
        case 8:
            if (bote_de_messagerie->lg == 0) {
                printf("\nAucun message n'a jamais été envoyé");
            } else {
                message = messageLePlusLong(bote_de_messagerie);
                int typeAff = 0;
                do {
                    printf("\nTaper 1 pour affichage par SMS, 2 pour affichage par message complet : ");
                    if (!scanf("%d",&typeAff)){
                        printf("\nRépeter SVP :)");
                    }
                } while(typeAff != 1 && typeAff != 2);
                if (typeAff == 1) {
                    MSGelementAfficherParSMS(message);
                } else {
                        MSGelementAfficherMSGcomplet(message);
                }
            }
            break;
        case 9: 
            printf("\nSasir m : ");
            scanf("%d",&m);
            p = unigrammes(bote_de_messagerie,m);
            PileAfficher(p);
            PileDetruire(p);
            break;
        case 10:
            printf("\nSasir m : ");
            scanf("%d",&m);
            pb = bigrammes(bote_de_messagerie,m);
            PileAfficher(pb);
            PileDetruire(pb);
            break;
        case 11 :
            // system("cls");
            if(system("clear")) {
                printf("\nErreur");
                exit(0);
            }
            break;
        case 22:
            printf("\nSasir m : ");
            scanf("%d",&m);
            pb = unigrammesBeta(bote_de_messagerie,m);
            PileAfficher(pb);
            PileDetruire(pb);
            break;
        case 44:
            strcpy(lineContact,"\0");
            file = fopen("files/together.txt", "r");
            printf("\nRemplissage de meme fichier en cours...");
            if (file == NULL) {
                printf("\nImpossible d'ouvrir le ficiher");
                break;
            } else {
                if(!fgets(line,100,file)) {
                    printf("\nErreur");
                    exit(0);
                }
                line[strcspn(line, "\n")] = 0;
                do {
                    plus = 0;
                    contact = CONTelementCreer();
                    strncpy(contact->nom,line,slashPos(line));
                    contact->nom[slashPos(line)] = '\0';
                    size = strlen(contact->nom);
                    plus += size + 1;
                    strncpy(contact->numero,line + plus,slashPos(line + plus));
                    contact->numero[slashPos(line)] = '\0';
                    size = 8;
                    plus += size + 1;
                    strcpy(contact->email,line + plus);
                    size = strlen(contact->email);
                    contact->email[strcspn(contact->email, "\n")] = 0;
                    contact->email[size] = '\0';
                    CONTinserer(repertoire,contact);
                    if(!fgets(line,100,file)) {
                        printf("\nErreur");
                        exit(0);
                    }
                    fflush(file);
                } while (strncmp(line,"#END#",4) != 0);
                printf("\n\nRéprtoire ready!\n\n");
                while (!feof(file)) {
                    message = MSGelementCreer();
                    if(!fgets(line,1224,file)) {
                        printf("\nErreur");
                        exit(0);
                    }
                    line[strcspn(line, "\n")] = 0;

                    size = strlen(line);
                    if(line[size-1] == '\n'){
                        line[size-1] = 0;
                    }
                    plus = 0;

                    strncpy(message->recepteur,line,slashPos(line));
                    message->recepteur[slashPos(line)] = '\0';
                    size = strlen(message->recepteur);
                    plus += size + 1;

                    strncpy(dj,line + plus,slashPos(line + plus));
                    message->date_envoi.jour = atoi(dj);
                    plus += 3;

                    strncpy(dj,line + plus,slashPos(line + plus));
                    message->date_envoi.mois = atoi(dj);
                    plus += 3;

                    strncpy(dja,line + plus,slashPos(line + plus));
                    message->date_envoi.annee = atoi(dja);
                    plus += 5;

                    strncpy(dj,line + plus,slashPos(line + plus));
                    message->heure_envoi.heure = atoi(dj);
                    plus += 3;

                    strncpy(dj,line + plus,slashPos(line + plus));
                    message->heure_envoi.minute = atoi(dj);
                    plus += 3;

                    strncpy(dj,line + plus,slashPos(line + plus));
                    message->heure_envoi.seconde = atoi(dj);
                    plus += 3;

                    strcpy(smsTemp,line + plus);
                    smsTemp[strlen(smsTemp)] = '\0';
                    smsTemp[strcspn(smsTemp, "\n")] = 0;

                    size = strlen(smsTemp);

                    //Insertion de message
                    LISTE_SMS L = SMSlisteCreer();

                    size_t typeSMS,length =  strlen(smsTemp) - type_de_SMS(smsTemp);
                    if (type_de_SMS(smsTemp) != 0) {
                        typeSMS = 67;
                    } else {
                        typeSMS = 153;
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
                    if (c == 1) {
                        if (typeSMS == 67) {
                            typeSMS = 70;
                        } else {
                            typeSMS = 160;
                        }
                    }
                    c = (int)(c);
                    
                    char temp[typeSMS + 10];
                    if(c == 1) {
                        sms = SMSelementCreer();
                        SMSelementLire(&sms,smsTemp);
                        SMSinserer(L,sms,1);
                    } else {
                        int c1,c2,k1,k2;
                        int j,charFound = 0;
                        int pq = 0;
                        char carSpe[50] = "çœàéèêù";
                        int nb_car_spe = 0,nb_car_a_copier = 0;
                        for (int pos = 1; pos <= c; pos++) {
                            memset(temp,0,strlen(temp));
                            sms = SMSelementCreer();
                            nb_car_spe = 0;
                            nb_car_a_copier = 0;
                            j = 0;
                            while(nb_car_a_copier < typeSMS && pq < strlen(smsTemp)) {
                                if (smsTemp[pq + j] == '\0'){
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
                        
                            pq += nb_car_a_copier + nb_car_spe;
                            temp[strlen(temp)] = '\0';
                            temp[strcspn(temp, "\n")] = 0;
                            SMSelementLire(&sms,temp);
                            SMSinserer(L,sms,pos);
                        }
                    }
                    message->msg = L;
                    message->prix = 0.050 * c;
                    plus = 0;
                    MSGinserer(bote_de_messagerie,message,1);
                }
                printf("\n\nBoite de messagerie ready!\n\n");
            }
            fclose(file);
            break;
        default:
            break;
        }
    } while (choix != 0);
    return 0;
}

CONTACT lePlusContacte (LISTE_MSG liste_message, LISTE_CONT liste_contact) {
    ELEMENT_CONT contact_element, plusContacte = CONTelementCreer();
    ELEMENT_MSG msg_element;
    int i = 1,j = 1,n = 0;
    int k = 0;
    
        while (i <= CONTlisteTaille(liste_contact)) {
            k = 0;
            contact_element = CONTrecuperer(liste_contact,i);
            char numero_repertoire[9] = "";
            strncpy(numero_repertoire,contact_element->numero,9);
            if (MSGlisteTaille(liste_message) == 0) {
                printf("\nAucun message n'a etais envoye\n");
            } else {
                j = 1;
                while (j <= MSGlisteTaille(liste_message)) {
                    msg_element = MSGrecuperer(liste_message,j);
                    char numero_messagerie[9];
                    strcpy(numero_messagerie,msg_element->recepteur);
                    if (strcmp(numero_messagerie,numero_repertoire) == 0) {
                        k+= SMSlisteTaille(msg_element->msg);
                    }
                    j++;
                }
                if (k > n) {
                    n = k;
                    plusContacte = contact_element;
                }
            }
            i++;
        } 
        return *plusContacte;
}

LISTE_CONT jamaisContactes(LISTE_MSG liste_message, LISTE_CONT liste_contact) {
    LISTE_CONT L = CONTlisteCreer();
    ELEMENT_CONT contact_element;
    ELEMENT_MSG msg_element;
    int j,trouve;
    if (CONTlisteTaille(liste_contact) == 0) {
        printf("\nAucun contact trouve.");
    } else {
        for(int i = 1; i <= CONTlisteTaille(liste_contact); i++) {
            contact_element = CONTelementCreer();
            CONTelementCopier(&contact_element,CONTrecuperer(liste_contact,i));
            char numero_repertoire[9];
            strncpy(numero_repertoire,contact_element->numero,9);
            j = 1; trouve = 0;
            do {
                msg_element = MSGrecuperer(liste_message,j);
                char numero_messagerie[9];
                strcpy(numero_messagerie,msg_element->recepteur);
                if(strncmp(numero_messagerie,numero_repertoire,9) == 0) {
                    trouve = 1;
                }
                j++;
            } while (j <= MSGlisteTaille(liste_message) && trouve == 0);
            if (trouve == 0) {
                CONTinserer(L,contact_element);
            }
        }
    }
   return L;
}

LISTE_MSG messages_D1_D2(LISTE_MSG liste_message, DATE D1, DATE D2) {
    LISTE_MSG L = MSGlisteCreer();
    ELEMENT_MSG e;
    for (int i = 1; i<= MSGlisteTaille(liste_message); i++) {
        e = MSGrecuperer(liste_message,i);
        if (D1.annee <= e->date_envoi.annee && D1.jour <= e->date_envoi.jour && D1.mois <= e->date_envoi.mois && D2.annee >= e->date_envoi.annee && D2.jour >= e->date_envoi.jour && D2.mois >= e->date_envoi.mois) {
            MSGinserer(L,e,1);
        }
    }   
    return L;
}
   
ELEMENT_MSG messageLePlusLong(LISTE_MSG liste_message) {
    ELEMENT_MSG e = MSGelementCreer();
    printf("\n");
    ELEMENT_MSG pluslong;
    printf("\n");
    int j,somme = 0; long n;
    n = 0;
    if (MSGlisteTaille(liste_message) == 0) {
        return e;
    } else {
        for (int i = 1; i <= MSGlisteTaille(liste_message); i++) {
            somme = 0;
            e = MSGrecuperer(liste_message,i);
            for (j = 1; j <= SMSlisteTaille(e->msg); j++) {
                somme += e->msg->elements[j]->taille; 
            } 
            if (somme > n) {
                n = somme;
                pluslong = e;
            }
        }
    }
    return pluslong;
}

int motJamaisTraite(char * mott, TABLEAU_COMPARISON T , int n) {
    if (n == 0) {
        return 1;
    }
    size_t length;
    for (int i = 1; i <= n; i++) {
        length = strlen(T->elements[i]->mot);
        if (strncmp(T->elements[i]->mot, mott, length) == 0) {
            return 0;
        }
    };
    return 1;
}


// BONUS
char tabMotVide[150][50] = {
    "alors", "au", "aucuns", "aussi", "autre", "avant", "avec", "avoir",
    "bon", "car", "ce", "cela", "ces", "ça", "a", "ceux", "chaque", "de",
    "si", "comme", "comment", "dans", "des", "du", "dedans", "dehors", "depuis", "devrait", "doit", 
    "donc", "dos", "début", "elles", "elle", "en", "encore", "essai", "est", "et", "eu",
    "fait", "faites", "fois", "font", "hors", "ici", "ils", "il", "je", "juste", "la", "le", "les", "leur"
    "là", "ma", "maintenant", "main", "mes", "mien", "moins", "mot", "même", "mon", "nommés", "ni", "notre", "nous", "ou",
    "où","par", "parce", "pas", "peut", "peu", "plupart", "pour", "pourquoi", "quand", "que", "quel", "quelle", "quelles",
    "quels", "qui", "sa", "sans", "ses", "seulement", "si", "sien", "son", "sont",
    "sous", "soyez", "sujet", "tandis", "sur", "ta", "tellement", "tels", "tes", "ton", "tous","tout" ,"trop", "voient", "très", 
    "vont", "votre", "vous", "étaient", "état", "étions", "été", "être"
};
int tabMotVideTaille = 107;
int motVide(char mot[]) {
    int i = 0,vide = 0;
        // printf("\n -----------------------MOT-%s-", mot);
    do {
        // printf("\n -%s-",tabMotVide[i]);
        if (strcmp(tabMotVide[i],mot) == 0) {
            vide = 1;
        } 
        i++;
    } while (vide == 0 && i <= tabMotVideTaille);
    return vide;
}
Pile unigrammesBeta(LISTE_MSG L, int M) {
    char * motToken;
    char * message;
    NOEUD_MSG p;
    //Tableau de comparaison
    TABLEAU_COMPARISON T = comparaisonTableauCreer();
    infoMot mmot;
    int iT = 0, trouveT; /* Indice utilisé pour le recherche d'un mot dans T*/
    p = L->tete;
    do {
        message = smsTogether(p->info->msg);
        strncat(message," ",2);
        message[strcspn(message, "\n")] = 0;
        motToken = strtok(message," ");
        while(motToken != NULL) {
            for(int b = 0; motToken[b]; b++) {
                motToken[b] = tolower(motToken[b]);
            }          
            motToken[strcspn(motToken, ".")] = 0;
            motToken[strcspn(motToken, ",")] = 0;
            if (motVide(motToken) != 1) {
                if (motJamaisTraite(motToken,T,T->lg) == 1) {
                    //Ajout dans la tableau de comparaison
                    mmot = infoMotCreer();
                    strcpy(mmot->mot,motToken);
                    mmot->occ = 1;
                    insererTableau(T,mmot);
                } else {
                    //Le mot est deja recontré donc on le cherche dans T et on ajout +1 à l'occurence
                    trouveT = 0; iT = 1;
                    do {
                        if (strcmp(T->elements[iT]->mot,motToken) == 0) {
                            T->elements[iT]->occ++;
                            trouveT = 1; // Mot trouvé
                        }
                        iT++;
                    } while(iT <= T->lg && trouveT == 0);
                } 
            } 
            motToken = strtok(NULL," "); 
        }     
        p = p->suivant;
        free(message);
    } while(p);

    trieeTableau(T,T->lg);
    // afficherTableau(T,T->lg);

    Pile v = PileCreer();
    ELEMENT_PILE e;
    for (int i = 1; i <= M; i++) {
        e = elementCreer_PILE();
        memmove(e->texte,T->elements[i]->mot,strlen(T->elements[i]->mot) + 1); 
        Empiler(v,e);
    }

    for (int i = 1; i<= T->lg; i++){
        free(T->elements[i]);
    }
    free(T);

    Pile pTemp = PileCreer();
    for (int j = 1; j <= M; j++) {
        e = Depiler(v);
        Empiler(pTemp,e);
    }

    PileDetruire(v);

    return pTemp;
}
Pile bigrammesBeta(LISTE_MSG L, int M) {
    char * motToken1; char * motToken2;
    char doubleToken[30] ;
    char * message;
    NOEUD_MSG h;
    //Tableau de comparaison
    TABLEAU_COMPARISON T2 = comparaisonTableauCreer();
    infoMot mmot2;
    int iT = 0, trouveT; /* Indice utilisé pour le recherche d'un mot dans T*/
    h = L->tete;

    size_t k,k_stop;
    do {
        message = smsTogether(h->info->msg);
        strncat(message," ",2);
        message[strcspn(message, "\n")] = 0;
        k_stop = strlen(message) - 1;
        motToken1 = strtok(message," ");
        strncpy(doubleToken,motToken1,strlen(motToken1)+1);

        motToken2 = strtok(NULL," ");
        
        strncat(doubleToken," \0",2);
        strncat(doubleToken,motToken2,strlen(motToken2)+1);
        

        k = 0;
        k += strlen(doubleToken);
        while(k <= k_stop) {
            for(int b = 0; doubleToken[b]; b++){
                doubleToken[b] = tolower(doubleToken[b]);
            }
            if (motVide(motToken1) != 1 && motVide(motToken2) !=1) {
                if (motJamaisTraite(doubleToken,T2,T2->lg) == 1) {
                    //Ajout dans la tableau de comparaison
                    mmot2 = infoMotCreer();
                    strcpy(mmot2->mot,doubleToken);
                    mmot2->occ = 1;
                    insererTableau(T2,mmot2);
                } else {
                    //Le mot est deja recontré donc on le cherche dans T et on ajout +1 à l'occurence
                    trouveT = 0; iT = 1;
                    do {
                        if (strcmp(T2->elements[iT]->mot,doubleToken) == 0) {
                            T2->elements[iT]->occ++;
                            trouveT = 1; // Mot trouvé
                        }
                        iT++;
                    } while(iT <= T2->lg && trouveT == 0);
                }
            }
            motToken1 = motToken2; 
            if(k == k_stop) {
                // printf("STOOP");
                break;
            } else {
                motToken2 = strtok(NULL," ");
                k += strlen(motToken2) + 1;
            }
            strncpy(doubleToken,motToken1,strlen(motToken1)+1);
            strncat(doubleToken," \0",2);
            strncat(doubleToken,motToken2,strlen(motToken2)+1);
        };
        h = h->suivant;
        free(message);
    } while(h);

    trieeTableau(T2,T2->lg);
    // afficherTableau(T2,T2->lg);

    Pile p = PileCreer();
    ELEMENT_PILE e;

    for (int i = 1; i <= M; i++) {
        e = elementCreer_PILE();
        memmove(e->texte,T2->elements[i]->mot,strlen(T2->elements[i]->mot) + 1); 
        Empiler(p,e);
    }

    for (int i = 1; i<= T2->lg; i++){
        free(T2->elements[i]);
    }
    free(T2);

    Pile pTemp = PileCreer();
    for (int j = 1; j <= M; j++) {
        e = Depiler(p);
        Empiler(pTemp,e);
    }

    PileDetruire(p);

    return pTemp;
}
// BONUS



Pile unigrammes(LISTE_MSG L,int M) {
    char * motToken;
    char * message;
    NOEUD_MSG p;
    //Tableau de comparaison
    TABLEAU_COMPARISON T = comparaisonTableauCreer();
    infoMot mmot;
    int iT = 0, trouveT; /* Indice utilisé pour le recherche d'un mot dans T*/
    p = L->tete;
    do {
        message = smsTogether(p->info->msg);
        strncat(message," ",2);
        message[strcspn(message, "\n")] = 0;
        motToken = strtok(message," ");
        while(motToken != NULL) {
            for(int b = 0; motToken[b]; b++) {
                motToken[b] = tolower(motToken[b]);
            }          
            if (motJamaisTraite(motToken,T,T->lg) == 1) {
                //Ajout dans la tableau de comparaison
                mmot = infoMotCreer();
                strcpy(mmot->mot,motToken);
                mmot->occ = 1;
                insererTableau(T,mmot);
            } else {
                //Le mot est deja recontré donc on le cherche dans T et on ajout +1 à l'occurence
                trouveT = 0; iT = 1;
                do {
                    if (strcmp(T->elements[iT]->mot,motToken) == 0) {
                        T->elements[iT]->occ++;
                        trouveT = 1; // Mot trouvé
                    }
                    iT++;
                } while(iT <= T->lg && trouveT == 0);
            }
            motToken = strtok(NULL," "); 
        }     
        p = p->suivant;
        free(message);
    } while(p);

    trieeTableau(T,T->lg);
    // afficherTableau(T,T->lg);

    if (M > T->lg) {
        printf("\nM est plus grand que les unigrammes disponibles veuiller repter");
        Pile pTemp = PileCreer();
        return pTemp;
    } else {
        Pile v = PileCreer();
        ELEMENT_PILE e;
        for (int i = 1; i <= M; i++) {
            e = elementCreer_PILE();
            memmove(e->texte,T->elements[i]->mot,strlen(T->elements[i]->mot) + 1); 
            Empiler(v,e);
        }

        for (int i = 1; i<= T->lg; i++){
            free(T->elements[i]);
        }
        free(T);

        Pile pTemp = PileCreer();
        for (int j = 1; j <= M; j++) {
            e = Depiler(v);
            Empiler(pTemp,e);
        }

        PileDetruire(v);

        return pTemp;
    }

    
}

Pile bigrammes(LISTE_MSG L, int M) {
    char * motToken1; char * motToken2;
    char doubleToken[30] ;
    char * message;
    NOEUD_MSG h;
    //Tableau de comparaison
    TABLEAU_COMPARISON T2 = comparaisonTableauCreer();
    infoMot mmot2;
    int iT = 0, trouveT; /* Indice utilisé pour le recherche d'un mot dans T*/
    h = L->tete;

    size_t k,k_stop;
    do {
        message = smsTogether(h->info->msg);
        strncat(message," ",2);
        message[strcspn(message, "\n")] = 0;
        k_stop = strlen(message) - 1;
        motToken1 = strtok(message," ");
        strncpy(doubleToken,motToken1,strlen(motToken1)+1);


        motToken2 = strtok(NULL," ");
        strncat(doubleToken," \0",2);
        strncat(doubleToken,motToken2,strlen(motToken2)+1);
        

        k = 0;
        k += strlen(doubleToken);
        while(k <= k_stop) {
            for(int b = 0; doubleToken[b]; b++){
                doubleToken[b] = tolower(doubleToken[b]);
            }
            if (motJamaisTraite(doubleToken,T2,T2->lg) == 1) {
                //Ajout dans la tableau de comparaison
                mmot2 = infoMotCreer();
                strcpy(mmot2->mot,doubleToken);
                mmot2->occ = 1;
                insererTableau(T2,mmot2);
            } else {
                //Le mot est deja recontré donc on le cherche dans T et on ajout +1 à l'occurence
                trouveT = 0; iT = 1;
                do {
                    if (strcmp(T2->elements[iT]->mot,doubleToken) == 0) {
                        T2->elements[iT]->occ++;
                        trouveT = 1; // Mot trouvé
                    }
                    iT++;
                } while(iT <= T2->lg && trouveT == 0);
            }
            
            
            motToken1 = motToken2; 
            if(k == k_stop) {
                // printf("STOOP");
                break;
            } else {
                motToken2 = strtok(NULL," ");
                k += strlen(motToken2) + 1;
            }
            strncpy(doubleToken,motToken1,strlen(motToken1)+1);
            strncat(doubleToken," \0",2);
            strncat(doubleToken,motToken2,strlen(motToken2)+1);
        };
        h = h->suivant;
        free(message);
    } while(h);

    trieeTableau(T2,T2->lg);
    // afficherTableau(T2,T2->lg);

    if(M > T2->lg) {
        printf("\nM est plus grans les bigrammes disponibles veuiller repeter");
        Pile pTemp = PileCreer();
        return pTemp;
    } else {
        Pile p = PileCreer();
        ELEMENT_PILE e;

        for (int i = 1; i <= M; i++) {
            e = elementCreer_PILE();
            memmove(e->texte,T2->elements[i]->mot,strlen(T2->elements[i]->mot) + 1); 
            Empiler(p,e);
        }

        for (int i = 1; i<= T2->lg; i++){
            free(T2->elements[i]);
        }
        free(T2);

        Pile pTemp = PileCreer();
        for (int j = 1; j <= M; j++) {
            e = Depiler(p);
            Empiler(pTemp,e);
        }

        PileDetruire(p);
        return pTemp;
    }

}