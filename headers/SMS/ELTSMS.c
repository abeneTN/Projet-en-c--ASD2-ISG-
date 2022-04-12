#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ELTSMSprimitives.h"
#include "LSTSMSprimitives.h"

ELEMENT_SMS SMSelementCreer (void) {
    ELEMENT_SMS e;
    e = (ELEMENT_SMS)malloc(sizeof(SMS));
    return e;
}

void SMSelementDetruire (ELEMENT_SMS elt) {
    free(elt->text);
    free(elt);
}

void SMSelementAffecter(ELEMENT_SMS * e1, ELEMENT_SMS e2) {
    *e1 = e2 ;
}

void SMSelementCopier(ELEMENT_SMS * e1, ELEMENT_SMS e2) {
    *e1 = e2 ;
}

void SMSelementLire(ELEMENT_SMS * elt, char * smsTemp) {
    size_t len = strlen(smsTemp);
    (*elt)->text = (char *)malloc(len + 1);
    strncpy((*elt)->text,smsTemp,len + 1);
    (*elt)->taille = strlen(smsTemp) - 1;
}

void SMSelementAfficher(ELEMENT_SMS elt) {
    printf("\n");
    printf("Texte : %s \nTaille : %d", elt->text, elt->taille);
    printf("\n");
}

int SMSelementComparer(ELEMENT_SMS e1, ELEMENT_SMS e2) {
    return (e1->taille - e2->taille);
}