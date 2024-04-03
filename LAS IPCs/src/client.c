#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

#include "utils_v2.h"
#include "ex4.h"

/**
 * Programme client
 * 
 * Prend en paramètre une chaine de 10 caractères minuscules et l'écrit en mémoire partagée.
 * Attend le retour de la chaîne en majuscules pour l'afficher.
*/
int main(int argc, char const *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <chaine>\n", argv[0]);
        exit(1);
    }

    if (strlen(argv[1]) > 10) {
        fprintf(stderr, "Size of string must be 10 or minus\n");
        exit(1);
    }

    // GET IT IF IT EXISTS
    int sem_id2 = sem_get(SEMKEY2, 1);
    int sem_id1 = sem_get(SEMKEY1, 1);

    // GET SHARED MEMORY
    int shm_id = sshmget(KEY, 10*sizeof(char), 0);
    // ATTACH SHARED MEMORY
    char* shared_memory = sshmat(shm_id);

    sem_up(sem_id1, 0);

    // WRITE IN SHARED MEMORY
    for (int i = 0; i < 10; i++) {
        shared_memory[i] = argv[1][i];
    }

    sem_down0(sem_id2);

    printf("Client: %s\n", shared_memory);

    return 0;
}
