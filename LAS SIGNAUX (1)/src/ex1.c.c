#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "utils_v1.h"

static const char *const STRING = "Signal SIGUSR1 reçu !\n";

volatile sig_atomic_t cpt = 0;

/**
 * increment cpt à chaque SIGUSR1 reçu par le fils
 * de la part du père
*/
void sigusr_handler (int sig) {
    cpt++;
    write(1, STRING, strlen(STRING));
    if (cpt == 7) {
        _exit(0);
    }
}

volatile sig_atomic_t child_exit = 0;

/**
 * Change la valeur de child_exit si SIGCHLD 
 * reçu par le père de la part du fils
*/
void child_handler () {
    child_exit = 1;
}

/**
 * Processus père qui engendre un fils exécutant une boucle semi-active
 * (une boucle infinie appellant sleep)
 * 
 * Le parent envoie le signal SIGUSER1 à son fils toutes les secondes.
 * Le fils doit se terminer lorsqu'il à reçu 7 signaux SIGUSR1.
*/
int main(int argc, char const *argv[]) {
    ssigaction(SIGUSR1, sigusr_handler);
    ssigaction(SIGCHLD, child_handler);

    int pid = sfork();

    if (pid == 0) { // ENFANT
        while (1) {
            sleep(1);
        }
    } else { //PARENT
        while (!child_exit) {
            skill(pid, SIGUSR1);
        }
        printf("Fin du père\n");
    }
    return 0;
}
