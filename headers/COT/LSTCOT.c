#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "LSTCOTprimitives.h"

NOEUD_CONT CONTnoeudCreer(ELEMENT_CONT e)
{
    NOEUD_CONT n;
    n = (NOEUD_CONT)malloc(sizeof(structNoeudCONT));
    if (!n)
    {
        printf("\nPlus d'espace");
    }
    else
    {
        CONTelementAffecter(&n->info, e);
        n->suivant = NULL;
    }
    return n;
}

void CONTnoeudDetruire(NOEUD_CONT n)
{
    CONTelementDetruire(n->info);
    free(n);
}

int CONTinserer(LISTE_CONT L, ELEMENT_CONT e)
{
    int i = 1,succee = 0;
    NOEUD_CONT n,q,p;
    p = L->tete;
    q = p;
    n = CONTnoeudCreer(e);
    if (CONTestVide(L)) {
        n->suivant = L->tete;
        L->tete = n;
        (L->lg)++;
        succee = 1;
    } else {
        do {
            if (CONTelementComparer(e,p->info) < 0) {
                if (i == 1) {
                    n->suivant = L->tete;
                    L->tete = n;
                    (L->lg)++;
                    succee = 1;
                } else if (p->suivant != NULL) {
                    q->suivant = n;
                    n->suivant = p;
                    (L->lg)++;
                    succee = 1;
                } else if (p->suivant == NULL){
                    q->suivant = n;
                    n->suivant = p;
                    (L->lg)++;
                    succee = 1;
                }
            }
            q = p;
            p = p->suivant;
            i++;
        } while(p && succee == 0);
        if (succee == 0) {
            q->suivant = n;
            (L->lg)++;
            succee = 1;
        }
    }
    return succee;
}

int CONTestVide(LISTE_CONT L)
{
    return (L->lg == 0);
}

int CONTestSaturee()
{
    NOEUD_CONT temp;
    int saturee = 1; /* on suppose mémoire saturée */
    temp = (NOEUD_CONT)malloc(sizeof(structNoeudCONT));
    if (temp != NULL)
    {
        saturee = 0; /* mémoire non saturée */
        free(temp);
    }
    return saturee;
}

int CONTlisteTaille(LISTE_CONT L)
{
    return (L->lg);
}

ELEMENT_CONT CONTrecuperer(LISTE_CONT L, int pos)
{
    /* s'il ya une erreur on affiche un message et on
    retourne un element vide */
    ELEMENT_CONT elt = CONTelementCreer();
    int i;
    NOEUD_CONT p;
    if (CONTestVide(L))
        printf("\nListe vide");
    else
    {
        if ((pos < 1) || (pos > L->lg))
            printf("\nPosition invalide");
        else
        {
            p = L->tete;
            for (i = 1; i < pos; i++)
                p = p->suivant;
            CONTelementAffecter(&elt, p->info);
        }
    }
    return (elt);
}

LISTE_CONT CONTlisteCreer(void)
{
    LISTE_CONT L;
    L = (LISTE_CONT)malloc(sizeof(structNoeudCONT));
    if (!L)
        printf("\nProblème de mémoire");
    else
    {
        L->lg = 0;
        L->tete = NULL; /* initialiser la tête */
    }
    return (L);
}

void CONTlisteDetruire(LISTE_CONT L)
{
    int i;
    NOEUD_CONT p, q;
    q = L->tete;
    for (i = 1; i <= L->lg; i++)
    {
        p = q;
        q = q->suivant;
        CONTnoeudDetruire(p);
    }
    free(L);
}

void CONTlisteAfficher(LISTE_CONT L)
{
    int i = 1;
    NOEUD_CONT p;
    p = L->tete;
    for (i = 1; i <= L->lg; i++)
    {
        CONTelementAfficher(p->info);
        p = p->suivant;
    }
    if (CONTlisteTaille(L) == 0)
    {
        printf("\nAucun contact trouve.\n");
    }
}

LISTE_CONT CONTlisteCopier(LISTE_CONT L)
{
    LISTE_CONT LR = CONTlisteCreer();
    int i;
    ELEMENT_CONT elt;
    for (i = 1; i <= L->lg; i++)
    {
        elt = CONTelementCreer();
        CONTelementCopier(&elt, CONTrecuperer(L, i));
        CONTinserer(LR, elt);
    }
    return LR;
}

int CONTlisteComparer(LISTE_CONT L1, LISTE_CONT L2)
{
    int test = 1;
    int i = 1;
    if (CONTlisteTaille(L1) != CONTlisteTaille(L2))
        test = 0;
    while ((i <= CONTlisteTaille(L1)) && (test))
    {
        if (CONTelementComparer(CONTrecuperer(L1, i), CONTrecuperer(L2, i)) != 0)
            test = 0;
        i++;
    }
    return test;
}
