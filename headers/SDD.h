#ifndef SDD_h
#define SDD_h
#define max 100
/* Déclaration de infoMot une structure pour suivre l'occurences des mots */

typedef struct infoMotStruct{
    char mot[50];
    int occ;
}infoMotStruct, *infoMot;

typedef struct {
    infoMot elements[max]; // (tableau)
    int lg; //Taille logique de la liste
} structureListeComp, *TABLEAU_COMPARISON;

//Creation de infoMot
infoMot infoMotCreer(void);
//Creation de tableau comparaison
TABLEAU_COMPARISON comparaisonTableauCreer();
//Insertion dans la tableai
void insererTableau(TABLEAU_COMPARISON , infoMot );
//Affichage du tableau
void afficherTableau(TABLEAU_COMPARISON T, int n);
//Trier le tableau
void trieeTableau(TABLEAU_COMPARISON T, int n);
//Use it before fgets();
void clearBuffer();
//Look for a special character return 0 if standard
int type_de_SMS(char []);
//Make every first letter uppdercase
char * firstLetterUppercase(char []);
//Postion de slash/
int slashPos(char ch[]);
//Postion d'esapce
int espacePos(char ch[]);
//Detruire une strucutre mot
void infoMotDetruire(infoMot m);
//Detruire le tableau
void tableauDetruire(TABLEAU_COMPARISON T, int n);

#include "SMS/SDD_SMS.h"
#include "MSG/SDD_MSG.h"
#include "COT/SDD_COT.h"
#include "PILE/SDD_PILE.h"

//Retourne tous les sms concatené
char * smsTogether(LISTE_SMS L);

#include "fonction.c"

#endif