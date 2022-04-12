#ifndef PILEpirmitives_h
#define PILEpirmitives_h

#include "PILE.h"
#include "ELTPILEprimitives.h"

//Création d'une pile
Pile PileCreer(void);

//Détruire une pile
void PileDetruire(Pile);

//Retourne 1 si la pile est vide sinon 0
int EstVide(Pile);

//Retourne 1 si la pile est satuée sinon 0
int EstSaturee(Pile);

//Rtourne la taille de la pile
int PileTaille(Pile);

//Retourne l'element du sommet
ELEMENT_PILE Sommet(Pile);

//Inserer un element dans le sommet d'une pile
int Empiler(Pile, ELEMENT_PILE);

//Suprrimer et retourne l'element du sommet
ELEMENT_PILE Depiler(Pile);

//Afficher une pile
void PileAfficher(Pile);

//Copier une pile dans une autre
Pile PileCopier(Pile);

//Comparer deux piles
int PileComparer(Pile, Pile);

#endif