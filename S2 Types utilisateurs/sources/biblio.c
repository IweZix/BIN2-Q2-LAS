#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "biblio.h"
#include "utils_v1.h"

static char* lesGenres[] = {"Bande dessinée", "Poésie", "Théâtre",
                            "Roman", "Roman historique", "Littérature française",
                            "Littérature étrangère", "Sciences", "Informatique",
                            "Science-fiction", "Santé", "Histoire", NULL};

bool lireLivre(struct Livre* l) {
    char ligne[SZ_TITRE + 2];

    // lecture du titre
    if (readLimitedLine(ligne, SZ_TITRE + 2) <= 0) return false;
    strcpy(l -> titre, ligne);

    // lecture de l'auteur
    if (readLimitedLine(ligne, SZ_AUTEUR + 2) <= 0) return false;
    strcpy(l -> auteur, ligne);

    // lecture de l'isbn
    if (scanf("%ld\n",&l->isbn) != 1) return false;

    // lecture de l'éditeur
    if (readLimitedLine(ligne,SZ_EDITEUR+2) <= 0) return false;
    strcpy(l->editeur, ligne);

    // lecture de l'année
    if (scanf("%d\n",&l->annee) != 1) return false;

    // lecture du genre
    if (readLimitedLine(ligne,SZ_TITRE+2) <= 0) return false;
    if ((l->genre = str2genre(ligne)) == -1) return false;
    return true;
}

enum Genre str2genre (char *s) {
   for (enum Genre g = 0; g < 12; g++){
      if (!strcmp(s, lesGenres[g])){
         return g;
      } 
   }
   return -1;
}

char* genre2str (enum Genre g) {
   int maxGenre = sizeof(lesGenres)/sizeof(char*) - 1;
   if (g < 0 || g >= maxGenre)
      return NULL;
   return lesGenres[g];
}

char* livre2str(char* s, struct Livre l) {
    sprintf(s, "%-40s %-20s %10ld %-20s %5d %d", 
        l.titre, l.auteur, l.isbn, l.editeur, l.annee, l.genre);
        return s;
}

void afficherBib(const struct Livre* bib, int t) {
    if (t <= 0) {
        printf("Cette bibliothèqe ne possède aucun livre.");
        return;
    }
    printf("Voici la bibliothèque : \n");
    for (int i = 0; i < t; i++) {
        char livre[SZ_MAX];
        printf("%s\n", livre2str(livre, bib[i]));
    }
}

bool ajouterLivre(struct Livre** bib, struct Livre livre, int* nbreL, int* taille) {
    if (*taille == 0){
      if ((*bib = (struct Livre*)malloc((*taille=3)*sizeof(struct Livre))) == NULL){
         perror("Malloc");
         return false;
      }
   } else if (*taille == *nbreL){
      if ((*bib = (struct Livre*)realloc(*bib, (*taille*=2)*sizeof(struct Livre))) == NULL){
         perror("Realloc");
         return false;
      }
   }
   (*bib)[*nbreL] = livre;
   (*nbreL)++;
   return true;
}