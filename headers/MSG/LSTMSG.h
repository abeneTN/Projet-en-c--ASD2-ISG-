#ifndef LSTMSG_h
#define LSTMSG_h

#include "ELTMSGprimitives.h"

typedef struct structNoeudMSG {
    ELEMENT_MSG info;
    struct structNoeudMSG * suivant;
    struct structNoeudMSG * precedent;
}structNoeudMSG, *NOEUD_MSG;

typedef struct {
    NOEUD_MSG tete;
    NOEUD_MSG queue;
    int lg;
}structureListeMSG, *LISTE_MSG;

#endif