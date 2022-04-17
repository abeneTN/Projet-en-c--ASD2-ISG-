#ifndef ELTMSGprimitives_h
#define ELTMSGprimitives_h

#include "ELTMSG.h"
#include "../SMS/SDD_SMS.h"

/*MSG Lecture d'un élément */
void MSGelementLire(ELEMENT_MSG *);

/*MSG Affichage d'un élément par SMS*/
void MSGelementAfficherParSMS(ELEMENT_MSG);

/*MSG Affichage d'un élément complet*/
void MSGelementAfficherMSGcomplet(ELEMENT_MSG elt);

/*MSG Affectation du 2eme argument dans le 1er qui est donc modifié et passé par
adresse */
void MSGelementAffecter(ELEMENT_MSG*, ELEMENT_MSG);

/*MSG Copie du contenu du deuxième argument dans le premier, les deux
arguments ont des adresses différentes (duplication)*/
void MSGelementCopier(ELEMENT_MSG *, ELEMENT_MSG) ;

/*MSG Comparaison des arguments retourne un entier 0, < 0 ou > 0 la "différence" (e1 e2) */
int MSGelementComparer(ELEMENT_MSG, ELEMENT_MSG);

/*MSG Création d'un élément */
ELEMENT_MSG MSGelementCreer(void);

/*MSG Libération de mémoire */
void MSGelementDetruire(ELEMENT_MSG);

/*MSG - Lecture de DATE */
void dateLire(DATE *);

/*MSG - Lecture de HEURE */
void heureLire(HEURE *);

/* MSG - Affichage de la date */
void dateAffichage(DATE d);

/*MSG - Affichage de l'heure */
void heureAffichage(HEURE h);

#endif