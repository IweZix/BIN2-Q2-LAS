#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "utils_v1.h"

void handler () {
    printf("signal SIGUSR1 reçu !\n");
    exit(0);
}

/**
 * Processus père qui engendre un fils exécutant une boucle semi-active
 * (une boucle infinie appellant sleep)
 * 
 * Parent envoie le signal SIGUSER1 à son fils et le fils doit afficher le message
 * "signal SIGUSR1 reçu !" à la récéption du signal et ensuite se stop
*/
int main(int argc, char const *argv[]) {
    ssigaction(SIGUSR1, handler);

    int pid = sfork();

    if (pid == 0) { // ENFANT
        while (1) {
            sleep(1);
        }
    } else { //PARENT
        skill(pid, SIGUSR1);
    }
    return 0;
}
