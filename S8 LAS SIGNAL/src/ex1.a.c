#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "utils_v1.h"


/**
 * Processus père qui engendre un fils exécutant une boucle semi-active
 * (une boucle infinie appellant sleep) et puis se termine.
 * 
 * ps -f
 * kill -SIGUSR1 "pid"
*/
int main(int argc, char const *argv[]) {
    int pid = sfork();
    if (pid == 0) {
        while (1) {
            printf("Fils\n");
            sleep(1);
        }
    } else {
        printf("Le processus père se termine\n");
    }
    return 0;
}
