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

#include "utils_v2.h"
#include "ex1.h"

int main(int argc, char const *argv[]) {

    // CREATE SHARED MEMORY
    int shm_id = sshmget(KEY, sizeof(int), IPC_CREAT | PERM);
    int* shared_memory = sshmat(shm_id);

    for (int i = 0; i < 20; i++) {
        int radar = randomIntBetween(0, 100);
        *shared_memory = radar;
        sleep(3);
    }

    // DETACH SHARED MEMORY
    sshmdt(shared_memory);
    // DELETE SHARED MEMORY
    sshmdelete(shm_id);
    
    return 0;
}
