#ifndef ELTPILEpirmitives_h
#define ELTPILEpirmitives_h

#include "ELTPILE.h"

//Creation d'un element Pile
ELEMENT_PILE elementCreer_PILE (void);

//Détruire d'un element Pile
void elementDetruire_PILE (ELEMENT_PILE );

//Affecher dans un element pile un autre element pile
void elementAffecter_PILE(ELEMENT_PILE * , ELEMENT_PILE );

//Copier un element pile un autre element pile
void elementCopier_PILE(ELEMENT_PILE * , ELEMENT_PILE );

//Lire un element pile
void elementLire_PILE(ELEMENT_PILE * );

//Afficher un element pile
void elementAfficher_PILE(ELEMENT_PILE );

//Comparer deux elements piles
int elementComparer_PILE(ELEMENT_PILE , ELEMENT_PILE );

#endif