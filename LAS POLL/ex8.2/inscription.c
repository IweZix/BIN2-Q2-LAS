#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

#include "utils_v1.h"

#define MAX 10

/**
 * Processus enfant
*/
void child_handler(void *args) {

    // récupération des arguments
    int *pipefd = (int *)args;

    for (int i = 0; i < MAX; i++) {
        // endormissement (0 - 10000 ms)
        int random_number_time = randomIntBetween(0, 10);
        sleep(random_number_time);

        // création message d'inscription "Fils <pid> : inscirption <random_number_time>"
        char buffer[200] = "Fils ";
        pid_t pid = getpid();
        char pidStr[10];
        sprintf(pidStr, "%d", pid);
        strcat(buffer, pidStr);
        strcat(buffer, " : inscription ");
        random_number_time = randomIntBetween(0, 10000);
        char randomNumberTimeStr[10];
        sprintf(randomNumberTimeStr, "%d", random_number_time);
        strcat(buffer, randomNumberTimeStr);

        // envoi message au père
        int nbChar = write(pipefd[1], buffer, strlen(buffer));
        if (nbChar < 0) {
            printColor("%s\n", "ERROR: Write\n", 31);
            exit(EXIT_FAILURE);
        }
    }
}

/**
 * Gestionnaire de signal
*/
void sigint_handler(int sig) {
    printColor("\n%s\n", "Signal SIGUSR1 received\n", 33);
    exit(EXIT_SUCCESS);
}

/**
 * Simulation de traitement de demandes d'inscriptions.
 * Demandes d'instruction envoyées au père via des pipes aléattoirement pas 2 processus fils.
*/
int main(int argc, char const *argv[]) {
    // signal
    ssigaction(SIGINT, sigint_handler);

    if (argc != 2) {
        printColor("%s\n", "Usage: <number_of_child>\n", 31);
        exit(EXIT_FAILURE);
    }

    const int numberOfChild = atoi(argv[1]);

    if (numberOfChild < 2) {
        printColor("%s\n", "Number of child must be greater than 2\n", 31);
        exit(EXIT_FAILURE);
    }

    struct pollfd *fds = malloc(numberOfChild * sizeof(struct pollfd));

    // Création enfant
    int *childTab = malloc(numberOfChild * sizeof(int));
    if (childTab == NULL) {
        printColor("%s\n", "ERROR: Malloc\n", 31);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numberOfChild; i++) {
        int pipefd[2];
        int ret = pipe(pipefd);
        if (ret < 0) {
            printColor("%s\n", "ERROR: Pipe creation\n", 31);
            exit(EXIT_FAILURE);
        }
        pid_t childId = fork_and_run1(child_handler, pipefd);
        childTab[i] = childId;

        fds[i].fd = pipefd[0];
        fds[i].events = POLLIN;
    }

    /**
     * Processus parent
    */

    // Lecture des messages
    while (true) {

        int ret = poll(fds, numberOfChild, 0);
        if (ret < 0) {
            printColor("%s\n", "ERROR: Poll\n", 31);
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < numberOfChild; i++) {
            if (fds[i].revents & POLLIN) {
                char buffer[200];
                int nbChar = read(fds[i].fd, buffer, sizeof(buffer));
                if (nbChar < 0) {
                    printColor("%s\n", "ERROR: Read\n", 31);
                    exit(EXIT_FAILURE);
                }
                buffer[nbChar] = '\0';
                printColor("%s\n", buffer, 32);
            }
        }
    }
    
    free(childTab);
    return 0;
}
