#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "LSTSMSprimitives.h"

LISTE_SMS SMSlisteCreer(void) 
{
    LISTE_SMS L;
    L = (LISTE_SMS)malloc(sizeof(structureListeSMS));
    if(!L) {
        printf("\nProbleme de memoire") ;
        exit(0) ;
    } else {
        printf("\n(Une nouvelle conversation a ete cree)");
    }
  L->lg = 0;
  return(L);
}


void SMSlisteDetruire(LISTE_SMS L)
{
    int i; 
    for(i = 1;i <= L->lg; i++) 
    {
        SMSelementDetruire(L->elements[i]);
    } 
   free(L);   
}


int SMSinserer (LISTE_SMS L, ELEMENT_SMS e, int pos) 
{
    int i;
    int succee=1;
    if (SMSestSaturee(L))
    { 
        printf ("\nListe saturée"); 
        succee=0;
    }
    else 
    {
        if ((pos < 1) || (pos > L->lg + 1)) 
        {
            printf ("\nPosition invalide");
            succee=0;
        }
        else 
        {
            for(i = L->lg; i>= pos; i--)
            SMSelementAffecter(&L->elements[i+1], L->elements[i]);
            SMSelementAffecter(&L->elements[pos], e);
            (L->lg)++;
        }
    }
 return(succee);
}


int SMSsupprimer (LISTE_SMS L, int pos ) 
{
    int i;
    int succee=1;
    if (SMSestVide(L)) 
    { 
        printf ("\nListe vide"); 
        succee=0;
    }
    else 
    {
        if ((pos < 1) || (pos > L->lg)) 
        {
            printf ("\nPosition invalide");
            succee=0;}
       else 
        {
            SMSelementDetruire(L->elements[pos]);
            for(i=pos;i<=L->lg;i++)
            SMSelementAffecter(&L->elements[i], L->elements[i+1]);
            (L->lg)--;
        }
   }
  return(succee);
}


ELEMENT_SMS SMSrecuperer(LISTE_SMS L, int pos) 
{
    ELEMENT_SMS elt= SMSelementCreer();
    if (SMSestVide(L)) 
        printf ("\nListe vide"); 
    else 
    {
        if ((pos < 1) || (pos > L->lg))
            printf (" \nPosition invalide");
       else
            elt=(L->elements[pos]);
    }
  return(elt);
}


LISTE_SMS SMSlisteCopier(LISTE_SMS L)
{
    LISTE_SMS LR = SMSlisteCreer();
    int i;
    ELEMENT_SMS elt;
    for(i = 1;i <= L->lg; i++) 
    {
        elt=SMSelementCreer();
        SMSelementCopier(&elt, SMSrecuperer(L,i));
        SMSinserer(LR, elt, i);
    }
  return LR;
}



int SMSlisteComparer (LISTE_SMS L1,LISTE_SMS L2 )
{
    int test= 1;
    int i=1;
    if (SMSlisteTaille(L1) != SMSlisteTaille(L2)) 
        test= 0; 
   while ((i<=SMSlisteTaille(L1)) && (test)) 
   { 
        if (SMSelementComparer(SMSrecuperer(L1,i),SMSrecuperer(L2,i))!=0)
            test=0;
     i++; 
   } 
 return test;
} 


void SMSlisteAfficher(LISTE_SMS L) 
{
    int i;
    for(i = 1; i <= L->lg; i++) {
        printf("\nSMS numero %d :",i);
        SMSelementAfficher(L->elements[i]);
    }
}


int SMSestVide(LISTE_SMS L) 
{
    return (L->lg == 0);
}



int SMSestSaturee(LISTE_SMS L) 
{
    return (L->lg == LongMax);
}


int SMSlisteTaille(LISTE_SMS L) 
{
    return (L->lg);
}