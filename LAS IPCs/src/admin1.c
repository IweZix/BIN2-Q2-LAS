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
#include "ex3.h"

/**
 * Programme admin1
 * -c : Créer et initialise les mémoires partagées et les sémaphores pour
 *  le programme ecran et le programme distributeur.
 * 
 * -d : détruit les mémoires partagées et les sémaphores.
*/
int main(int argc, char const *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s -c | -d\n", argv[0]);
        exit(1);
    }

    if (strcmp(argv[1], "-c") == 0) {
        // CREATE SEMAPHORE OR GET IT IF IT EXISTS
        sem_create(SEMKEY, 2, PERM, 1);
        
        // CREATE SHARED MEMORY OR GET IT IF IT EXISTS
        sshmget(KEY, 2*sizeof(int), IPC_CREAT | PERM);

    } else if (strcmp(argv[1], "-d") == 0) {
        // DELETE SEMAPHORE
        sem_delete(SEMKEY);
        // DELETE SHARED MEMORY
        sshmdelete(KEY);
    } else {
        fprintf(stderr, "Usage: %s -c | -d\n", argv[0]);
        exit(1);
    }
    
    return 0;
}
