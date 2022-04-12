#ifndef LSTSMS_h
#define LSTSMS_h

#include "ELTSMSprimitives.h"
#define LongMax 8 //Longueur maximale d'une liste de SMS

typedef struct {
    ELEMENT_SMS elements[LongMax]; //Liste des SMSs (tableau)
    int lg; //Taille logique de la liste
} structureListeSMS, *LISTE_SMS;


#endif 