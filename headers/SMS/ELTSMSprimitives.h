#ifndef ELTSMSprimitives_h
#define ELTSMSprimitives_h

#include "ELTSMS.h"
#include "LSTSMSprimitives.h"

/* Lecture d'un élément*/
void SMSelementLire(ELEMENT_SMS *, char *);

/* Affichage d'un élément */
void SMSelementAfficher(ELEMENT_SMS);

/* Affectation du 2eme argument dans le 1er qui est donc modifié et passé par
adresse */
void SMSelementAffecter(ELEMENT_SMS*, ELEMENT_SMS);

/* Copie du contenu du deuxième argument dans le premier, les deux
arguments ont des adresses différentes (duplication)*/
void SMSelementCopier(ELEMENT_SMS *, ELEMENT_SMS) ;

/* Comparaison des arguments retourne un entier 0, < 0 ou > 0 la "différence" (e1 e2) */
int SMSelementComparer(ELEMENT_SMS, ELEMENT_SMS);

/* Création d'un élément */
ELEMENT_SMS SMSelementCreer(void);

/* Libération de mémoire */
void SMSelementDetruire(ELEMENT_SMS);

#endif