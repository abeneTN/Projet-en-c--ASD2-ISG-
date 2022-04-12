#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>

#include "SDD.h"

void clearBuffer() {
    int ch;
    while ((ch=getchar()) != '\n' && ch!=EOF);
}

int type_de_SMS(char ch[] ) {
    char khra[10] = "çœ";
    int i,z,y, flag = -1, length;
    length = strlen(khra)-1;
    for (i = 0; i <= length; i++) {
        // printf("\n le caracter a tester de khra %c", khra[i]);
        z = (int)(khra[i]);
        for (size_t j = 0; j <= strlen(ch)-1; j++) {
            // printf("\n le caracter a tester de ch %c", ch[j]);
            y = (int)(ch[j]);
            if (y == z) {
                flag = i;
                // printf("\n\n\n\n\n\nWELEYE\n\n\n\n\n\n");
                break;
            }
        }
        
        // printf("\n le numero est : %d",z);
        // printf("\n le numero est : %d\n",y);  
    }
    return flag;
}

char * firstLetterUppercase(char ch[]) {
    int length = strlen(ch) - 1;
    ch[0] = toupper(ch[0]);
    for (int k = 1; k <= length; k++) {
        if (ch[k] != ' ') {
            ch[k] = tolower(ch[k]);
        }
    }
    for (int i = 1; i <= length; i++) {
        if (ch[i] == ' ') {
            ch[i+1] = toupper(ch[i+1]);
            i++; 
        }
    }
    return ch;
}

char * smsTogether(LISTE_SMS L) {
    int somme = 0;
    for (int k = 1; k <= SMSlisteTaille(L); k++) {
        somme += L->elements[k]->taille;
    }
    char * ch = calloc(1,somme + 1);
    for (int i = 1; i <= SMSlisteTaille(L); i++) {
        strcat(ch,L->elements[i]->text);
    }
    ch[somme + 1] = '\0';
    return (char * ) ch;
}


int slashPos(char ch[]) {
    int flag = -1;
    size_t i =0;
    while (i <= strlen(ch)-1 && flag == -1) {
        if (ch[i] == '/') {
            flag = i;
            break;
        }
        i++;
    }
    return flag;
}

int espacePos(char ch[]) {
    int flag = -1;
    size_t i = 0;
    while (i <= strlen(ch)-1 && flag == -1) {
        if (ch[i] == ' ') {
            flag = i;
            printf("\nEspace trouvé");
            break;
        }
        i++;
    }
    return flag;
    
}

/* Pour la strucutre infoMot */



infoMot infoMotCreer(void) {
    printf("\nCreation d'une nouvelle case : ");
    infoMot m;
    m = malloc(sizeof(infoMotStruct));
    if (!m) {
        printf("\nErreur de memoire");
    } else {
        printf("succce");
    }
    return m;
}

TABLEAU_COMPARISON comparaisonTableauCreer(void) {
    TABLEAU_COMPARISON T;
    T = (TABLEAU_COMPARISON)malloc(sizeof(structureListeComp));
    for(int i = 0; i<= max;i++) {
        infoMot T = (infoMot)malloc(sizeof(infoMotStruct));
    }
    if (!T) {
        printf("\nProbleme de memoire") ;
        exit(0) ;
    } else {
        printf("\n(Tableau crée)");
    }
    T->lg = 0;
    printf("\nTaille initialisé : %d",T->lg);
    return T;
}

void insererTableau(TABLEAU_COMPARISON T, infoMot m) {
    printf("\n\n\nAjout dans le tableau est en cours..");
    T->lg++;
    T->elements[T->lg] = m;

    printf("\nMot ajouté dans le tableau: %s",T->elements[0]->mot);
}

void afficherTableau(TABLEAU_COMPARISON T, int n) {
    printf("\n\n\nAffichage du tableau");          
    for (int i = 1; i <= n; i++) {
        printf("\n case n°:%d ",i);
        printf("Mot : %s; Occurence : %d",T->elements[i]->mot,T->elements[i]->occ);
    }
}

void swap(infoMot m1,infoMot m2) {
    infoMot mTemp = m1;
    m1 = m2;
    m2 = mTemp;
}

void trieeTableau(TABLEAU_COMPARISON T, int n) {
    int tri = 1, j;
    infoMot elementTemp;
    do {
        tri = 1;
        for (j = 1; j <= n-1; j++) {
            if (T->elements[j]->occ < T->elements[j+1]->occ){
                elementTemp = T->elements[j];
                T->elements[j] = T->elements[j+1];
                T->elements[j+1] = elementTemp; 
                tri = 0;
            }
        }
    } while (tri == 0);
       
}