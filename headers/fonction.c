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
    char khra[20] = "çœàéè";
    int i,z1,z2,y1,y2, flag = 0;
    size_t j,length2 = 0,length = 0;
    length = strlen(khra);
    length2 = strlen(ch);
    for (i = 0; i <= length; i+=2) {
        // printf("\n le caracter a tester de khra %c", khra[i]);
        z1 = (int)(khra[i]);
        z2 = (int)(khra[i+1]);
        for (j = 0; j <= length2 - 1; j++) {
            // printf("\n le caracter a tester de ch %c", ch[j]);
            y1 = (int)(ch[j]);
            y2 = (int)(ch[j+1]);
            if (y1 == z1 && y2 == z2) {
                /*special character found*/
                flag++;
                j++;
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
        somme += strlen(L->elements[k]->text);
    }
    printf("\nNombre de caracters : %d",somme);
    char * ch = calloc(L->lg,somme + 1);
    for (int i = 1; i <= SMSlisteTaille(L); i++) {
        strncat(ch,L->elements[i]->text,strlen(L->elements[i]->text));
    }
    return ch;
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
    m =(infoMot)malloc(sizeof(infoMotStruct)+1);
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
    // for(int i = 1; i<= max;i++) {
    //     infoMot T = (infoMot)malloc(sizeof(infoMotStruct));
    // }
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
    printf("\nT->lg = %d",T->lg);
    T->elements[T->lg] = m;
    printf("; Mot ajouté dans le tableau: -%s-\n\n",T->elements[T->lg]->mot);
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
    while (tri == 1) {
        tri = 0;
        for (j = 1; j <= n-1; j++) {
            if (T->elements[j]->occ < T->elements[j+1]->occ){
                elementTemp = T->elements[j];
                T->elements[j] = T->elements[j+1];
                T->elements[j+1] = elementTemp; 
                tri = 1;
            }
        }
    }
       
}

void infoMotDetruire(infoMot m) {
    free(m);
}

void tableauDetruire(TABLEAU_COMPARISON T, int n) {
    for (int i = 1; i <= n; i++) {
        infoMotDetruire(T->elements[i]);
    }
    free(T);
}