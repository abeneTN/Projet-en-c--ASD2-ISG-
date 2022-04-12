#ifndef LSTSMSprimitives_h
#define LSTSMSprimitives_h

#include "LSTSMS.h"

//Retourne 1 si la liste est vide 0 sinon
int SMSestVide(LISTE_SMS );

//Retourne 1 si la liste est saturée 0 sinon
int SMSestSaturee(LISTE_SMS );

//Retourne la taille de la liste
int SMSlisteTaille(LISTE_SMS );

//Insérer dans un liste, un élement dans une position
int SMSinserer (LISTE_SMS , ELEMENT_SMS , int );

//Supprimer un élement dans la liste à la position
int SMSsupprimer (LISTE_SMS , int );

//Recuperer un élement d'une liste d'un position
ELEMENT_SMS SMSrecuperer(LISTE_SMS , int );

// Creation d'une liste
LISTE_SMS SMSlisteCreer(void);

//Dertruire une liste
void SMSlisteDetruire(LISTE_SMS);

//Affichage d'une liste
void SMSlisteAfficher(LISTE_SMS );

//Copier une liste dans une autre liste
LISTE_SMS SMSlisteCopier(LISTE_SMS );

//Comparer deux listes
int SMSlisteComparer (LISTE_SMS ,LISTE_SMS  );

#endif