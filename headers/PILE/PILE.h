#ifndef PILE_h
#define PILE_h

#define LongMax2 10000

//Liste pile contiguë
typedef struct {
    ELEMENT_PILE elements[LongMax2]; /* tableau automatique */
    int sommet; //indice de la sommet de la pile
}structurePile, *Pile;


#endif