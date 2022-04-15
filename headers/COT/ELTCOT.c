#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ELTCOTprimitives.h"

ELEMENT_CONT CONTelementCreer (void) {
    ELEMENT_CONT e;
    e = (ELEMENT_CONT)malloc(sizeof(CONTACT));
    strcpy(e->email, "\0");
    strcpy(e->nom, "\0");
    strcpy(e->numero, "\0");
    return e;
}

void CONTelementDetruire (ELEMENT_CONT elt) {
    free(elt);
}

void CONTelementAffecter(ELEMENT_CONT * e1, ELEMENT_CONT e2) {
    *e1 = e2 ;
}

void CONTelementCopier(ELEMENT_CONT * e1, ELEMENT_CONT e2) {
    *e1 = e2 ;
}

void CONTelementLire(ELEMENT_CONT * elt) {
    printf("\nEnregistrement d'un nouveau contact est en cours...");
    printf("\nSaisir le Nom : ");
    // while(getchar() != '\n'); //Better way to clear the buffer
    clearBuffer();
    if(!fgets((*elt)->nom,50,stdin)){
        printf("\nErreur");
        exit(0);
    }
    (*elt)->nom[strcspn((*elt)->nom, "\n")] = 0;
    char * formated = firstLetterUppercase((*elt)->nom);
    size_t size = strlen(formated);
    memmove((*elt)->nom,formated,( size + 1 ) * sizeof( char ) );
    int test = 0;
    do {
        clearBuffer();
        printf("\nSaisir le numero : ");
        
        if (!fgets((*elt)->numero,9,stdin)){
            printf("\nErreur");
            exit(0);
        }
        if ((*elt)->numero[0] == '5') {
            test = 1;
        } else if ((*elt)->numero[0] == '2') {
            test = 1;
        } else if ((*elt)->numero[0] == '9') {
            test = 1;
        } else {
            printf("\nLe numero de desitinataire doit commence avec 2,5 ou 9 et contient 8 chiffres");
        }
        size = strlen((*elt)->numero);
    } while (size != 8 || test == 0);
    (*elt)->numero[strcspn((*elt)->numero, "\n")] = 0;
    int i, flag = 0;
    do {
        clearBuffer();
        printf("\nSasisir l'email : ");
        if(!fgets((*elt)->email,30,stdin)) {
            printf("\nErreur");
            exit(0);
        }
        size = strlen((*elt)->email);
        for (i = 0; i <= size; i++) {
            if ((*elt)->email[i] == '@') {
                flag = i;
                break;
            }
        }
    } while (flag == 0);
    (*elt)->email[strcspn((*elt)->email, "\n")] = 0;
    printf("\nContact enrigistree!");
}

void CONTelementAfficher(ELEMENT_CONT elt) {
    printf("---------------------------------------");
    printf("\n|Nom : -%s- Numero : -%s-\n|Email : -%s-", elt->nom, elt->numero, elt->email);
    printf("\n+--------------------------------------");
}

int CONTelementComparer(ELEMENT_CONT e1, ELEMENT_CONT e2) {
    int diffNom = strcmp(e1->nom,e2->nom), diffNum = strcmp(e1->numero,e2->numero);  
    if (diffNom != 0) {
        return diffNom;
    } else {
        return diffNum;
    }
}