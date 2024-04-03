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
 * Programme serveur
 * 
 * Récupre la chaine de caractères en mémoire partagée, la met en majuscules et la renvoie.
*/
int main(int argc, char const *argv[]) {

    // GET IT IF IT EXISTS
    int sem_id1 = sem_get(SEMKEY1, 1);
    int sem_id2 = sem_get(SEMKEY2, 1);

    // GET SHARED MEMORY
    int shm_id = sshmget(KEY, 10*sizeof(char), 0);
    // ATTACH SHARED MEMORY
    char* shared_memory = sshmat(shm_id);

    sem_down0(sem_id1);

    // WRITE IN SHARED MEMORY
    for (int i = 0; i < 10; i++) {
        shared_memory[i] = toupper(shared_memory[i]);
    }

    sem_up0(sem_id2);
    
    return 0;
}
