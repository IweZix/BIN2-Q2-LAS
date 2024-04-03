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

    // GET SHARED MEMORY
    int shm_id = sshmget(KEY, sizeof(int), 0);
    int* shared_memory = NULL;

    for (int i = 0; i < 12; i++) {
        shared_memory = sshmat(shm_id);
        printf("Radar: %d\n", *shared_memory);
        sleep(5);
    }

    // DETACH SHARED MEMORY
    sshmdt(shared_memory);
    
    return 0;
}
