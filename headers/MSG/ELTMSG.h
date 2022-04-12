#ifndef ELTMSG_h
#define ELTMSG_h

#include "../SMS/SDD_SMS.h"

typedef struct {
    int jour;
    int mois;
    int annee;
}DATE;

typedef struct {
    int heure;
    int minute;
    int seconde;
}HEURE;

typedef struct {
    char recepteur[9];
    LISTE_SMS msg;
    float prix;
    DATE date_envoi;
    HEURE heure_envoi;
}MESSAGE, *ELEMENT_MSG;



#endif