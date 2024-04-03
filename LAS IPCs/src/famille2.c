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

int main(int argc, char const *argv[]) {
    
    pid_t child_id1 = sfork();

    if (child_id1 == 0) { // ENFANT 1
        
        for (int i = 0; i < 3; i++) {
            printf("Je suis le fils %d\n", getpid());
            sleep(1);
        }
        

    } else {
        swaitpid(child_id1, NULL, 0);
        pid_t child_id2 = sfork();

        if (child_id2 == 0) { // ENFANT 2
            for (int i = 0; i < 3; i++) {
                printf("Je suis le fils %d\n", getpid());
                sleep(1);
            }
        } else {
            swaitpid(child_id2, NULL, 0);

        }

    }

    return 0;
}
