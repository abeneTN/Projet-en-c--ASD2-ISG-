#ifndef LSTMSGprimitives_h
#define LSTMSGprimitives_h

#include "LSTMSG.h"

//Création d'un Noeud
NOEUD_MSG MSGnoeudCreer(ELEMENT_MSG );

//Détruire un Noeud
void MSGnoeudDetruire(NOEUD_MSG);

//Retourne 1 si la liste est vide 0 sinon
int MSGestVide(LISTE_MSG );

//Retourne 1 si la liste est saturée 0 sinon
int MSGestSaturee();

//Retourne la taille de la liste
int MSGlisteTaille(LISTE_MSG );

//Insérer dans un liste, un élement dans une position
int MSGinserer (LISTE_MSG , ELEMENT_MSG , int );

//Supprimer un élement dans la liste à la position
int MSGsupprimer (LISTE_MSG , int );

//Recuperer un élement d'une liste d'un position
ELEMENT_MSG MSGrecuperer(LISTE_MSG , int );

// Creation d'une liste
LISTE_MSG MSGlisteCreer(void);

//Dertruire une liste
void MSGlisteDetruire(LISTE_MSG);

//Affichage d'une liste
void MSGlisteAfficher(LISTE_MSG );

//Copier une liste dans une autre liste
LISTE_MSG MSGlisteCopier(LISTE_MSG );

//Comparer deux listes
int MSGlisteComparer (LISTE_MSG ,LISTE_MSG  );


#endif