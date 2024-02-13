#ifndef _BIBLIO_H_
#define _BIBLIO_H_

#include <stdbool.h>

#define SZ_TITRE 128
#define SZ_AUTEUR 80
#define SZ_EDITEUR 50
#define SZ_MAX SZ_TITRE+SZ_AUTEUR+SZ_EDITEUR+100

enum Genre {
    BD, // Bande dessinéee
    P,  // Poésie
    T,  // Théâtre
    R,  // Roman
    RH, // Roman historique
    LF, // Littérature française
    LE, // Littérature étrangère 
    SC, // Science
    I,  // Informatique
    SF, // Science fiction
    S,  //
    H   //    
};

struct Livre {
    char titre[SZ_TITRE+1];
    char auteur[SZ_AUTEUR+1];
    long isbn;
    char editeur[SZ_EDITEUR+1];
    int annee;
    enum Genre genre;
};

/**
 * POST:
 */
bool lireLivre(struct Livre* l);

/**
 * POST: renvoie le genre littéraire correspondant à une chaine de caractères
 */
enum Genre str2genre(char* genre);

/**
 * POST: renvoie la chaine de caractères correspondant à un genre littéraire
 */
char* genre2str(enum Genre genre);

/**
 * POST: converti un livre en chaine de caractères
 */
char* livre2str(char* s, struct Livre l);

/**
 * POST: affiche le contenu d'une table de livre
 */
void afficherBib(const struct Livre* bib, int t);

/**
 * POST: ajoute un livre à une table de Livre
 */
bool ajouterLivre(struct Livre** bib, struct Livre livre, int* nbreL, int* taille);

#endif   // _BIBLIO_H_