#ifndef _PILE_H
#define _PILE_H

typedef struct Noeud {
    int element;
    struct Noeud* suivant;
} Noeud;

typedef Noeud* Pile;

/**
 * POST:
 * PRE:
 * RES: 
 */
Pile initPile();

/**
 * POST:
 * PRE:
 * RES: 
 */
bool pileVide(Pile p);

/**
 * POST:
 * PRE:
 * RES: 
 */
bool push (Pile *p, int e);

/**
 * POST:
 * PRE: p non vide
 * RES: 
 */
int pop(Pile* p);

/**
 * POST:
 * PRE:
 * RES: 
 */
void viderPile(Pile *p);

/**
 * POST:
 * PRE:
 * RES: 
 */
void afficherPile(Pile p);

#endif   // _PILE_H_