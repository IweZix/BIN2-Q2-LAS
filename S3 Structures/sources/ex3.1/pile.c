#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "pile.h"
#include "utils_v1.h"

Pile initPile() {
    return NULL;
}


bool pileVide(Pile p) {
    return p == NULL;
}

bool push (Pile *p, int e) {
    Noeud *n = (Noeud*)malloc(sizeof(Noeud));
    if (n == NULL) {
        perror("Impossible de malloc");
        return false;
    }
    n -> element = e;
    n -> suivant = *p;
    *p = n;
    return true;
}

int pop(Pile *p) {
    Noeud *ptr = (*p);
    int returned = ptr->element;
    (*p) = (*p) -> suivant;
    free(ptr);

    return returned;
}

void viderPile(Pile *p) {
    while (!pileVide(*p)) {
        pop(p);
    }
}

void afficherPile(Pile p) {
    Noeud *ptr = p;
    while (ptr != NULL) {
        printf("%d ", ptr->element);
        ptr = ptr->suivant;
    }
    printf("\n");
}