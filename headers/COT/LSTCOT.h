#ifndef LSTCOT_h
#define LSTCOT_h

#include "ELTCOTprimitives.h"

typedef struct structNoeudCONT{
    ELEMENT_CONT info;
    struct structNoeudCONT * suivant;
}structNoeudCONT, *NOEUD_CONT;

typedef struct {
    NOEUD_CONT tete;
    int lg;
}StrutureListeCONT, *LISTE_CONT;


#endif