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

// shared_memory[0] : nombre de tickets
// shared_memory[1] : dernier ticket imprimé
int main(int argc, char const *argv[]) {

    // CREATE SEMAPHORE OR GET IT IF IT EXISTS
    int sem_id = sem_create(SEMKEY, 2, PERM, 1);
    
    // CREATE SHARED MEMORY OR GET IT IF IT EXISTS
    int shm_id = sshmget(KEY, 2*sizeof(int), IPC_CREAT | PERM);
    // ATTACH SHARED MEMORY
    int* shared_memory = sshmat(shm_id);

    int tickets = *shared_memory;
    if (tickets == 0) {
        tickets = 1;
    }

    sem_down(sem_id, 1);
    tickets++;
    *shared_memory = tickets;
    sem_up(sem_id, 1);
    printf("Tickets suivant imprimé !\n");


    // DETACH SHARED MEMORY
    sshmdt(shared_memory);
    // DELETE SHARED MEMORY
    // sshmdelete(shm_id);
    

    return 0;
}
