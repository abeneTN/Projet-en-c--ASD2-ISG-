#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "PILEprimitives.h"

Pile PileCreer(void)
{
    Pile P;

    P = (Pile)malloc(sizeof(structurePile));
    if (!P)
    {
        printf(" \nProblème de mémoire");
    }
    else
        P->sommet = 0; // puisque l’indice le plus faible est 1
    return (P);
}

void PileDetruire(Pile P)
{
    int i;
    for (i = 1; i <= P->sommet; i++)
        elementDetruire_PILE(P->elements[i]);
    free(P);
}

void PileAfficher(Pile P)
{
    int i;
    printf("\nAfficahge de la Pile");
    for (i = P->sommet; i >= 1; i--)
        elementAfficher_PILE(P->elements[i]);
}

int EstVide_PILE(Pile P)
{
    return (P->sommet == 0);
}

int EstSaturee_PILE(Pile P)
{
    return (P->sommet == LongMax);
}

int PileTaille(Pile P)
{
    return (P->sommet);
}

int Empiler(Pile P, ELEMENT_PILE e)
{
    int succes = 1;
    if (EstSaturee_PILE(P))
    {
        printf("\n Pile saturée");
        succes = 0;
    }
    else
    {
        (P->sommet)++;
        elementAffecter_PILE(&P->elements[P->sommet], e);
    }
    return (succes);
}

ELEMENT_PILE Depiler(Pile P)
{
    ELEMENT_PILE elt = elementCreer_PILE();
    if (EstVide_PILE(P))
    {
        printf("\n Pile vide");
    }
    else
    {
        elementCopier_PILE(&elt, (P->elements)[P->sommet]);
        elementDetruire_PILE(P->elements[P->sommet]);
        (P->sommet)--;
    }
    return (elt);
}

ELEMENT_PILE sommet(Pile P)
{
    ELEMENT_PILE elt = elementCreer_PILE();
    if (EstVide_PILE(P))
        printf(" \n Pile vide");
    else
        elt = (P->elements[P->sommet]);
    return (elt);
}
