#include <stdbool.h>

#ifndef _BIBLIO_H_
#define _BIBLIO_H_

// Définition de constantes

#define MAX_TITRE         128
#define MAX_AUTEUR        80
#define MAX_EDITEUR       50
#define MAX_LIGNE_LIVRE   MAX_TITRE+MAX_AUTEUR+MAX_EDITEUR+50

// Définition de types

typedef enum {BD, PO, TH, RO, RH, LF, LE, SC, IN, SF, SA, HI, GENRES_NUM} Genre;

typedef struct {
   char  titre[MAX_TITRE+1];
   char  auteur[MAX_AUTEUR+1];
   long  isbn;
   char  editeur[MAX_EDITEUR+1];
   int   an;
   Genre genre;   // type 'enum Genre' peut être directement défini dans 'struct Livre'
} Livre;

// Déclaration de variable externe
extern char* lesGenres[];

// qsort - solution 2
// Une explicatoin sur la généricité en C est disponible sur 
//   https://youtu.be/xQBefPZw2jA
typedef int (*fctcmp)(const void *, const void*);


// Déclaration de fonctions

/* Lit les informations d'un livre à l'entrée standard
 * POST: l a été complété avec les informations lues sur stdin
 *       (à raison d'une information par ligne)
 * RES: renvoie vrai si l a été correctement saisi; faux sinon
 */
bool lireLivre (Livre* l);

/* Convertit un livre en chaîne de caractères
 * PRE: s: buffer de MAX_LIGNE_LIVRE caractères
 *      l: livre à convertir
 * RES: renvoie la chaîne s contenant les informations du livre l
 */
char* livre2str (char* s, Livre l);

/* Affiche le contenu d'un tableau de livres
 * PRE: bib: tableau de t livres
 * POST: affiche les informations des t livres de bib, 
 *       à raison d'un livre par ligne
 */
void afficherBib (const Livre* bib, int t);

/* Ajoute un livre à un tableau
 * PRE: bib: adresse d'un tableau de nbreL livres, de capacité physique taille
 *      l: livre à ajouter à bib
 * POST: le livre l a été ajouté à bib, nbreL incrémenté
 *       et taille (capacité physique) mise à jour
 * RES: renvoie vrai si bib, nbreL et taille ont bien été mis à jour;
 *      faux sinon
 */
bool ajouterLivre (Livre ** bib, Livre l, int* nbreL, int* taille);

/* Renvoie le genre littéraire correspondant à une chaîne de caractères
 * PRE: s: chaîne de caractères
 *      lesGenres: tableau de chaînes terminé par NULL 
 *                 [variable globale contenant les chaînes de caractères 
 *                  correspondant aux genres littéraires]
 * RES: renvoie le genre littéraire correspondant à s;
 *      -1 si aucun genre correspondant n'a été trouvé dans lesGenres
 */
Genre str2genre (char* s);

/* Renvoie la chaîne de caractères correspondant à un genre littéraire
 * PRE: g: genre littéraire
 *      lesGenres: tableau de chaînes terminé par NULL 
 *                 [variable globale contenant les chaînes de caractères 
 *                  correspondant aux genres littéraires]
 * RES: renvoie la chaîne de caractères définie dans lesGenres, 
 *      correspondant au genre g
 */
char* genre2str (Genre g);

/* Compare l'année d'édition de deux livres
 * PRE: a,b: livres à comparer
 * RES: renvoie 0 si les livres a et b ont la même année d'édition;
 *      une valeur positive si l'année d'édition de a est postérieure à celle de b;
 *      une valeur négative si l'année d'édition de a est antérieure à celle de b
 */
int comparerLivre (const Livre* a, const Livre* b);

/* Charge les livres d'un fichier
 * PRE: f: fichier binaire contenant des Livre, ouvert en lecture
 *      bib: tableau de livres
 *      nbreL: nombre de livres dans bib
 *      taille: capacité du tableau bib
 * POST: tous les livres de f ont été chargés dans bib et nbreL et taille 
 *      (capacité physique) mises à jour
 * RES: renvoie vrai si l'opération s'est réalisée avec succès, 
 *      faux sinon (erreur de lecture dans f ou d'ajout dans bib)
 */
bool lireFichier (FILE *f, Livre **bib, int *nbreL, int *taille);

/* Sauve des livres dans un fichier
 * PRE: f: fichier binaire ouvert en écriture
 *      bib: tableau de livres
 *      n: nombre de livres dans bib
 * POST: tous les livres de bib ont été sauvés dans f
 * RES: renvoie vrai si l'opération s'est réalisée avec succès, 
 *      faux sinon (erreur d'écriture)
 */
bool ecrireFichier (FILE *f, Livre *bib, int n);

#endif   // _BIBLIO_
