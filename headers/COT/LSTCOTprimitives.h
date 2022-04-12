#ifndef LSTCOTprimitives_h
#define LSTCOTprimitives_h

#include "LSTCOT.h"

//Création d'un Noeud
NOEUD_CONT CONTnoeudCreer(ELEMENT_CONT );

//Détruire un Noeud
void CONTnoeudDetruire(NOEUD_CONT);

//Retourne 1 si la liste est vide 0 sinon
int CONTestVide(LISTE_CONT );

//Retourne 1 si la liste est saturée 0 sinon
int CONTestSaturee();

//Retourne la taille de la liste
int CONTlisteTaille(LISTE_CONT );

//Insérer dans un liste, un élement dans une position
int CONTinserer (LISTE_CONT , ELEMENT_CONT );

//Supprimer un élement dans la liste à la position
int CONTsupprimer (LISTE_CONT , int );

//Recuperer un élement d'une liste d'un position
ELEMENT_CONT CONTrecuperer(LISTE_CONT , int );

// Creation d'une liste
LISTE_CONT CONTlisteCreer(void);

//Dertruire une liste
void CONTlisteDetruire(LISTE_CONT);

//Affichage d'une liste
void CONTlisteAfficher(LISTE_CONT );

//Copier une liste dans une autre liste
LISTE_CONT CONTlisteCopier(LISTE_CONT );

//Comparer deux listes
int CONTlisteComparer (LISTE_CONT ,LISTE_CONT  );

#endif