#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils_v1.h"

#define MAX 100

/**
 * Programme qui transforme les minuscules en majuscules.
*/
int main(int argc, char const *argv[]) {
    
    // 1 Création du pipe
    int pipefd[2];
    int ret = pipe(pipefd);
    checkNeg(ret, "pipe error");

    // 2 Création de l'enfant
    int childId = sfork();

    // PARENT
    if (childId > 0) {
        close(pipefd[0]);

        printf("Enter text (Ctrl-D to end): \n");
        char buffer[MAX];
        int bytesRead = 0;

        // 3 Lecture du texte
        while ((bytesRead = sread(0, buffer, MAX)) > 0) {
            // 4 Ecriture dans le pipe
            int nbChar = write(pipefd[1], buffer, bytesRead);
            checkCond(nbChar != bytesRead, "write error");
        }

        // 10 Fermeture du pipe
        ret = close(pipefd[1]);
        checkNeg(ret, "close error");
    }
    // FILS 
    else {

        char buffer[MAX];
        int bytesRead = 0;

        // 4 Lecture du pipe
        while ((bytesRead = sread(pipefd[0], buffer, MAX)) > 0) {
            // 5 parcourir le texte reçu
            for (int i = 0; i < bytesRead; i++) {
                // 6 Si c'est une minuscule (cf. table ASCII)
                if (buffer[i] >= 97 && buffer[i] <= 122) {
                    // 7 On la transforme en majuscule (cf. table ASCII)
                    buffer[i] = buffer[i] - 32;
                }
            }
            // 8 Ecriture dans la sortie standard
            int nbChar = write(0, buffer, bytesRead);
            checkCond(nbChar != bytesRead, "write error");
        }

        // 9 Fermeture du pipe
        close(pipefd[0]);
    }

    return 0;
}
