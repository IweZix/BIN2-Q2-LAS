#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "utils_v1.h"

/**
 * Programme qui simule le ofonctionnement d'un pipe (|) dans l'environnement bash
 * Usage ./ex2 ls grep -n  ".*\.c$"
*/
int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("ERROR: need more args\n");
        printf("USAGE EXEMPLE: ./ex2 ls grep -n \".*\\.c$\"\n");
        exit(1);
    }

    // 1 Création de pipe [in][out]
    int pipefd[2];
    int ret = pipe(pipefd);
    checkNeg(ret, "pipe error");

    // 2 Fork
    int childId1 = sfork();
    int childId2 = sfork();

    // 3 Redirection des flux
    if (childId1 == 0) { // ENFANT 1
        close(pipefd[0]);
        dup2(pipefd[1], 1);
        execlp(argv[1], argv[1], NULL);
        perror("exelp");
        exit(1);
    } else if (childId2 == 0) { // ENFANT 2
        close(pipefd[1]);
        dup2(pipefd[0], 0);

        char **args = malloc((argc + 2 - 1) * sizeof(char*));
        if (args == NULL) {
            printf("malloc");
            exit(1);
        }

        args[0] = argv[2];
        for (int i = 2; i < argc; i++) {
            args[i - 2] = argv[i];
        }
        args[argc - 2] = NULL;

        execvp(args[0], args);
        perror("exelp");
        exit(1);
    } else { // PARENT 1 & 2
        close(pipefd[0]);
        close(pipefd[1]);
        swaitpid(childId1, NULL, 0);
        swaitpid(childId2, NULL, 0);
    }

    return 0;
}


/**
 * DIFFICULTES
 * 
 * Double fork -> deux enfants & deux parents
 * 
 * Executer le premier argument seul
 * 
 * Executer le deuxième argument mais avec ces usages
 * Utilisation de execvp qui permet d'executer un tableau d'argument & usage
 *      -> Besoin de recopier le deuxième argument et ses usages dans un nouveau tableau
 *          -> ajouter NULL à la fin du tableau sinon execvp ne s'arretera pas
*/
