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

int main(int argc, char const *argv[]) {
    
    // CREATE SEMAPHORE OR GET IT IF IT EXISTS
    int sem_id = sem_create(SEMKEY, 2, PERM, 1);

    // CREATE SHARED MEMORY OR GET IT IF IT EXISTS
    int shm_id = sshmget(KEY, 2*sizeof(int), IPC_CREAT | PERM);
    // ATTACH SHARED MEMORY
    int* shared_memory = sshmat(shm_id);

    int nbr = 0;
    int last = 0;

    while (true) {
        sem_down0(sem_id);
        nbr = shared_memory[0];
        last = shared_memory[1];

        if (last == nbr) {
            printf("No new ticket printed\n");
            sem_up0(sem_id);
            exit(0);
        }

        printf("New ticket printed: %d\n", last);
        last++;
        shared_memory[1] = last;
        
        
        sem_up0(sem_id);
        sleep(3);
    }
    
    // DETACH SHARED MEMORY
    sshmdt(shared_memory);
    // DELETE SHARED MEMORY
    sshmdelete(shm_id);

    return 0;
}
