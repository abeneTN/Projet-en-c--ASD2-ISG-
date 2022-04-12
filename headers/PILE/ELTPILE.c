#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ELTPILEprimitives.h"

ELEMENT_PILE elementCreer_PILE (void) {
    ELEMENT_PILE L;
    L = (ELEMENT_PILE) malloc(sizeof(elementPile)); 
    return L;
}

void elementDetruire_PILE (ELEMENT_PILE L) {
    free (L);
}


void elementLire_PILE(ELEMENT_PILE* elt) {
    scanf("%s",(*elt)->texte);
}



void elementAfficher_PILE(ELEMENT_PILE elt) { 
    printf("\n%s",elt->texte);
}



void elementAffecter_PILE(ELEMENT_PILE* e1, ELEMENT_PILE e2) {
   *e1 = e2 ; 
}


void elementCopier_PILE(ELEMENT_PILE *e1, ELEMENT_PILE e2) {
   strcpy((*e1)->texte,e2->texte);
}


int elementComparer_PILE(ELEMENT_PILE e1, ELEMENT_PILE e2) {
    return strcmp(e1->texte,e2->texte);
}