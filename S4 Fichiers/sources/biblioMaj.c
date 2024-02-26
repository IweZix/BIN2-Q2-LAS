#include <stdlib.h>
#include <stdio.h>
#include "biblio.h"

int cmp (const void *l1, const void *l2) {
   return comparerLivre((Livre*) l1, (Livre*) l2);
}

int main (int argc, char **argv) {
   Livre *maBib= NULL;
   int nbreLivre = 0;
   int tailleP = 0;
   Livre unLivre = {0};
   char **files = argv + 1;

    printf("Les genres: \n");
   for (char** ptr = lesGenres; *ptr != NULL; ptr++)
      printf("- %s\n",*ptr);

   FILE *fin = NULL;
   FILE *fout = NULL;

   switch (argc) {
      default : 
         fprintf(stderr, "Usage : %s [fin] fout \n", *argv);
         exit(1); 
      case 3 : 
         printf("Ouverture du fichier '%s' en lecture\n",*files);
         if ((fin = fopen(*files, "rb")) == NULL) {
            perror("Erreur d'ouverture de fichier en lecture\n");
            exit(10);
         } 
         printf("Chargement des livres du fichier '%s'\n",*files);
         if (!lireFichier(fin, &maBib, &nbreLivre, &tailleP)) {
            if (ferror(fin)) {
               perror("Erreur de lecture");
               exit(12);
            }
            else {
               perror("Erreur d'ajout de livre (allocation de mémoire)");  
               exit(20);
            }
         }
         if (fclose(fin)) {
            perror("Erreur lors de la fermeture du fichier ouvert en lecture\n");
            exit(13);
         }
         files++;
      case 2 : 
         printf("Ouverture du fichier '%s' en écriture\n",*files);
         if ((fout = fopen(*files, "wb")) == NULL) {
            perror("Erreur d'ouverture du fichier en écriture\n");
            exit(11); 
         }
         break;
   }   

   printf("Lecture de livres au clavier\n");
   while (lireLivre(&unLivre)) {
      if (!ajouterLivre(&maBib, unLivre, &nbreLivre, &tailleP)) {
         perror("Erreur d'ajout de livre (allocation de mémoire)");  
         exit(20);
      }
		
      getchar();
   }
   afficherBib(maBib, nbreLivre);
	
   printf("Tri de la bibliothèque\n");   

   qsort(maBib, nbreLivre, sizeof(Livre), cmp);

   printf("Après tri: ");
   afficherBib(maBib, nbreLivre);

   printf("Ecriture des livres dans le fichier '%s'\n",*(files));
   if (!ecrireFichier(fout, maBib, nbreLivre)) {
      perror("Erreur d'écriture dans le fichier");
      exit(13);
   }

   if (fclose(fout)) {
      perror("Erreur lors de la fermeture du fichier ouvert en écriture\n");
      exit(13);
   }
   free(maBib);
}
