#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "LSTMSGprimitives.h"
#include "../SMS/SDD_SMS.h"

NOEUD_MSG MSGnoeudCreer(ELEMENT_MSG e) {
    NOEUD_MSG n;
    n = (NOEUD_MSG)malloc(sizeof(structNoeudMSG));
    if (!n) {
        printf("\nPlus d'espace");
    } else {
        MSGelementAffecter(&n->info, e);
        n->suivant = NULL;
        n->precedent = NULL;
    }
    return n;
}

void MSGnoeudDetruire(NOEUD_MSG n) {
    MSGelementDetruire(n->info);
    free(n);
}

int MSGinserer(LISTE_MSG L, ELEMENT_MSG e, int pos) {
    int succee = 1;
    int i;
    NOEUD_MSG n, p, q; /* c’est des pointeurs sur des neouds c’est équivalent à: structNoeud * n */
    if (MSGestSaturee(L)) {
        printf("\nListe saturée");
        succee = 0;
    } else {
        if ((pos < 1) || (pos > L->lg + 1)) {
            printf("\nPosition invalide");
            succee = 0;
        } else {
            n = MSGnoeudCreer(e); /*on est sûr que la  réservation va se faire car la mémoire n'est pas saturée*/
            if (L->lg == 0) { 
                /* la liste est vide */
                L->tete = n;
                L->queue = n;
            } else {
                if (pos == 1) {
                    /*insertion en tête de liste*/
                    L->tete->precedent = n;
                    n->suivant = L->tete;
                    L->tete = n;
                } else {
                    if (pos == (L->lg + 1)) {
                        /* ajout à la fin */
                        L->queue->suivant = n;
                        n->precedent = L->queue;
                        L->queue = n;
                    } else {
                        q = L->tete;
                        for (i = 1; i < pos; i++) {
                            p = q;
                            q = q->suivant;
                        }
                        /* q désigne l’élément de rang pos et p son prédécesseur*/
                        p->suivant = n;
                        n->precedent = p;
                        n->suivant = q;
                        q->precedent = n;
                    }
                }
            }
            (L->lg)++;
        }
    }
    return succee;
}

int MSGsupprimer(LISTE_MSG L, int pos)
{
    int i;
    int succee = 1;
    NOEUD_MSG p, q;
    if (MSGestVide(L))
    {
        printf("\nListe vide");
        succee = 0;
    }
    else
    {
        if ((pos < 1) || (pos > L->lg))
        {
            printf("\nPosition invalide");
            succee = 0;
        }
        else
        {
            if (L->lg == 1) /* un seul element donc pos == 1*/
            {
                q = L->tete;
                L->tete = NULL;
                L->queue = NULL;
            }
            else
            {
                if (pos == 1) /*suppression en tête de liste*/
                {
                    q = L->tete;
                    L->tete = L->tete->suivant;
                    L->tete->precedent = NULL;
                }
                else
                {
                    if (pos == L->lg)
                    {
                        q = L->queue;
                        L->queue = L->queue->precedent;
                        L->queue->suivant = NULL;
                    }
                    else
                    {
                        q = L->tete;
                        for (i = 1; i < pos; i++)
                        {
                            p = q;
                            q = q->suivant;
                        }
                        /*q désigne l’élément de rang pos et p son prédécesseur*/
                        q->suivant->precedent = p;
                        p->suivant = q->suivant;
                    }
                }
            }
            MSGnoeudDetruire(q);
            (L->lg)--;
        }
    }
    return succee;
}

int MSGestVide(LISTE_MSG L)
{
    return (L->lg == 0);
}

int MSGestSaturee()
{
    NOEUD_MSG temp;
    int saturee = 1; /* on suppose mémoire saturée */
    temp = (NOEUD_MSG)malloc(sizeof(structNoeudMSG));
    if (temp != NULL)
    {
        saturee = 0; /* mémoire non saturée */
        free(temp);
    }
    return saturee;
}

int MSGlisteTaille(LISTE_MSG L)
{
    return (L->lg);
}

ELEMENT_MSG MSGrecuperer(LISTE_MSG L, int pos)
{
    /* s'il ya une erreur on affiche un message et on
    retourne un element vide */
    ELEMENT_MSG elt = MSGelementCreer();
    int i;
    NOEUD_MSG p;
    if (MSGestVide(L))
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
            MSGelementAffecter(&elt, p->info);
        }
    }
    return (elt);
}

LISTE_MSG MSGlisteCreer(void)
{
    LISTE_MSG L;
    L = (LISTE_MSG)malloc(sizeof(structNoeudMSG));
    if (!L)
        printf("\nProblème de mémoire");
    else
    {
        L->lg = 0;
        L->tete = NULL; /* initialiser la tête */
    }
    return (L);
}

void MSGlisteDetruire(LISTE_MSG L)
{
    int i;
    NOEUD_MSG p, q;
    q = L->tete;
    for (i = 1; i <= L->lg; i++)
    {
        p = q;
        q = q->suivant;
        MSGnoeudDetruire(p);
    }
    free(L);
}

void MSGlisteAfficher(LISTE_MSG L)
{
    int i = 1;
    NOEUD_MSG p;
    p = L->tete;
    if (L->lg == 0) {
        printf("\nAucun message trouvé");
    } else {
        int typeAff = 0;
        do {
            printf("\nTaper 1 pour affichage par SMS, 2 pour affichage par message complet : ");
            if (!scanf("%d",&typeAff)){
                printf("\nRépeter SVP :)");
            }
        } while(typeAff != 1 && typeAff != 2);
        if (typeAff == 1) {
            for (i = 1; i <= L->lg; i++)
            {
                MSGelementAfficherParSMS(p->info);
                p = p->suivant;
            }
        } else {
            for (i = 1; i <= L->lg; i++)
            {
                MSGelementAfficherMSGcomplet(p->info);
                p = p->suivant;
            }
        }
    }
}

LISTE_MSG MSGlisteCopier(LISTE_MSG L)
{
    LISTE_MSG LR = MSGlisteCreer();
    int i;
    ELEMENT_MSG elt;
    for (i = 1; i <= L->lg; i++)
    {
        elt = MSGelementCreer();
        MSGelementCopier(&elt, MSGrecuperer(L, i));
        MSGinserer(LR, elt, i);
    }
    return LR;
}

int MSGlisteComparer(LISTE_MSG L1, LISTE_MSG L2)
{
    int test = 1;
    int i = 1;
    if (MSGlisteTaille(L1) != MSGlisteTaille(L2))
        test = 0;
    while ((i <= MSGlisteTaille(L1)) && (test))
    {
        if (MSGelementComparer(MSGrecuperer(L1, i), MSGrecuperer(L2, i)) != 0)
            test = 0;
        i++;
    }
    return test;
}
