#include <stdio.h>
#include <stdlib.h>

#include "biblio.h"

int main (int argc, char **argv) {
   struct Livre *bib = NULL;
   int nLivre = 0;
   int tailleP = 0;
   struct Livre livre;

   while (lireLivre(&livre)) {
      if (!ajouterLivre(&bib, livre, &nLivre, &tailleP)) {
         printf("Erreur ajout de livre");
         exit(1);
      }
		
      getchar();
   }
   afficherBib(bib, nLivre);
}