#ifndef ELTCOTprimitives_h
#define ELTCOTprimitives_h

#include "ELTCOT.h"

/*MSG Lecture d'un élément */
void CONTelementLire(ELEMENT_CONT *);

/*MSG Affichage d'un élément */
void CONTelementAfficher(ELEMENT_CONT);

/*MSG Affectation du 2eme argument dans le 1er qui est donc modifié et passé par
adresse */
void CONTelementAffecter(ELEMENT_CONT*, ELEMENT_CONT);

/*MSG Copie du contenu du deuxième argument dans le premier, les deux
arguments ont des adresses différentes (duplication)*/
void CONTelementCopier(ELEMENT_CONT *, ELEMENT_CONT) ;

/*MSG Comparaison des arguments retourne un entier 0, < 0 ou > 0 la "différence" (e1 e2) */
int CONTelementComparer(ELEMENT_CONT, ELEMENT_CONT);

/*MSG Création d'un élément */
ELEMENT_CONT CONTelementCreer(void);

/*MSG Libération de mémoire */
void CONTelementDetruire(ELEMENT_CONT);

#endif