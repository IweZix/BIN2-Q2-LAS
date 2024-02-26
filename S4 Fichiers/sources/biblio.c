#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "biblio.h"
#include "utils_v1.h"

#define BUF_SIZE  MAX_TITRE+2
#define NB_LIVRES 10

// Définition de variable globale

char* lesGenres[] = {"Bande dessinée", "Poésie", "Théâtre",
                     "Roman", "Roman historique", "Littérature française",
                     "Littérature étrangère", "Sciences", "Informatique",
                     "Science-fiction", "Santé", "Histoire", NULL};

// Implémentation des fonctions

bool lireLivre (Livre *l) {
   char ligne[BUF_SIZE];

   if (readLimitedLine(ligne,MAX_TITRE+2) <= 0) return false;
   strcpy(l->titre, ligne);

   if (readLimitedLine(ligne,MAX_AUTEUR+2) <= 0) return false;
   strcpy(l->auteur, ligne);

   if (scanf("%ld\n",&l->isbn) != 1) return false;

   if (readLimitedLine(ligne,MAX_EDITEUR+2) <= 0) return false;
   strcpy(l->editeur, ligne);

   if (scanf("%d\n",&l->an) != 1) return false;

   if (readLimitedLine(ligne,BUF_SIZE) <= 0) return false;
   if ((l->genre = str2genre(ligne)) == -1) return false;

   //getchar();   // lecture de ligne vide effectuée dans le programme appelant

   return true;
}

Genre str2genre (char *s) {
   for (Genre g = 0; g < GENRES_NUM; g++){
      if (!strcmp(s, lesGenres[g])){
         return g;
      } 
   }

   return -1;
}

char* genre2str (Genre g) {
   int maxGenre = sizeof(lesGenres)/sizeof(char*) - 1;  // -1 pour ne pas compter NULL
   if (g < 0 || g >= maxGenre)
      return NULL;
   return lesGenres[g];
}

char* livre2str (char *s, const Livre l) {
   sprintf(s, "%-40s %-15s %15ld  %-20s %5d  %s", 
           l.titre, l.auteur, l.isbn, l.editeur, l.an, genre2str(l.genre));
   return s;
}

void afficherBib (const Livre* bib, int t) {
   char ligne[MAX_LIGNE_LIVRE];
   printf("Voici ma bib de %d livres:\n", t);
   for (int i=0; i<t; i++) {
      printf("\t%s\n", livre2str(ligne, bib[i]));
   }
   printf("---------------------------\n");
}

bool ajouterLivre (Livre **bib, Livre l, int *nbreL, int *taille) {
   if (*taille == 0){
      if ((*bib = (Livre*)malloc((*taille=3)*sizeof(Livre))) == NULL){
         perror("Malloc");
         return false;
      }
   } else if (*taille == *nbreL){
      if ((*bib = (Livre*)realloc(*bib, (*taille*=2)*sizeof(Livre))) == NULL){
         perror("Realloc");
         return false;
      }
   }
   (*bib)[(*nbreL)++] = l;  // copie bit à bit d'une structure Livre!
   return true;
}

// Cette signature provient de la compatibilité avec qsort.
// Une explication sur la généricité en C est disponible sur 
//    https://youtu.be/xQBefPZw2jA
int comparerLivre (const Livre *a, const Livre *b) {
   return a->an - b->an;
}

/// LECTURE DANS FICHIER BINAIRE

/*
// Lecture des livres de f, livre par livre
bool lireFichier (FILE *f, Livre **bib, int *nbreL, int *taille) {
  Livre l;
  while (fread(&l, sizeof(Livre), 1, f)) {
    if (!ajouterLivre(bib, l, nbreL, taille)) {
      return false;
    }
  }
  if (ferror(f)) {  // ou  if (!feof(f)) 
    return false;
  } 
  return true;
}
*/

/*
// Lecture par bloc de NB_LIVRES livres
bool lireFichier (FILE *f, Livre **bib, int *nbreL, int *taille) {
  Livre tmp[NB_LIVRES];
  size_t nread = NB_LIVRES;
  while (nread == NB_LIVRES) {
    nread = fread(tmp, sizeof(Livre), NB_LIVRES, f);
    for (int i=0; i<nread; i++) {
      if (!ajouterLivre(bib, tmp[i], nbreL, taille)) {
        return false;
      }
    }
  }
  if (ferror(f)) {  // ou  if (!feof(f)) 
    return false;
  }
  return true;
}
*/

// Lecture par bloc de NB_LIVRES livres (variante)
bool lireFichier (FILE *f, Livre **bib, int *nbreL, int *taille) {
  Livre tmp[NB_LIVRES];
  size_t nread;
  while ((nread = fread(tmp, sizeof(Livre), NB_LIVRES, f)) != 0) {
    for (int i=0; i<nread; i++) {
      if (!ajouterLivre(bib, tmp[i], nbreL, taille)) {
        return false;
      }
    }
  }
  if (ferror(f)) {  // ou  if (!feof(f)) 
    return false;
  }
  return true;
}

// BONUS:
// Lecture par bloc de NB_LIVRES livres, sans appel de ajouterLivre
// (copie directement dans bib, avec gestion de la mémoire dynamique)
/*
bool lireFichier (FILE *f, Livre **bib, int *nbreL, int *taille) {
  *nbreL = *taille = 0;
  size_t nread = NB_LIVRES;
  while (nread == NB_LIVRES) {
    // allocation de mémoire dynamique à bib
    if (*taille == 0) {
      *taille = NB_LIVRES;
      if ((*bib = (Livre*)malloc((*taille)*sizeof(Livre))) == NULL) {
        perror("Malloc");
        return false;
      }
    } else {
      *taille += NB_LIVRES;
      if ((*bib = (Livre*)realloc(*bib, (*taille)*sizeof(Livre))) == NULL) {
        perror("Realloc");
        return false;
      }
    }
    // lecture de NB_LIVRES livres dans f
    nread = fread(*bib+*nbreL, sizeof(Livre), NB_LIVRES, f);
    *nbreL += nread;
  }
  if (ferror(f)) {  // ou  if (!feof(f)) 
    return false;
  }
  return true;
}
*/

/// ECRITURE DANS FICHIER BINAIRE

/*
// Ecriture des livres de bib, livre par livre
bool ecrireFichier (FILE *f, Livre *bib, int n) {
  for (int i=0; i<n; i++) {
    if (fwrite(bib+i, sizeof(Livre), 1, f) != 1) {
      return false;
    }
  }
  return true;
}
*/

/*
// Ecriture par bloc de NB_LIVRES livres  --> sans intérêt
bool ecrireFichier (FILE *f, Livre *bib, int n) {
  int nwrite = NB_LIVRES;
  for (int i=0; i<n; i+=nwrite) {
    if (n-i < NB_LIVRES)
      nwrite = n-i;
    if (fwrite(bib+i, sizeof(Livre), nwrite, f) != nwrite) 
      return false;
  }
  return true;
}
*/

// Ecriture en un bloc de tous les livres de bib 
bool ecrireFichier (FILE *f, Livre *bib, int n) {
  return fwrite(bib, sizeof(Livre), n, f) == n; 
}
