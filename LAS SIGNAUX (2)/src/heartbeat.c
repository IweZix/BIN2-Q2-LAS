#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils_v1.h"

static const char *const MESSAGE_DOWN = "mon fils est down\n";
static const char *const MESSAGE_ALIVE = "mon fils est toujours en vie \n";

volatile sig_atomic_t end = true;

void alarm_handler() {
    kill(getppid(), SIGUSR1);
    alarm(3);
}

void sigusr1_handler() {
    write(1, MESSAGE_ALIVE, strlen(MESSAGE_ALIVE));
    alarm(8);
}

void sigalarm_handler() {
    if (!end) {
        write(1, MESSAGE_DOWN, strlen(MESSAGE_DOWN));
        exit(5);
    }
    end = false;
    alarm(8);
}

int main(int argc, char const *argv[]) {
    
    int pid = sfork();

    if (pid > 0) { // PERE
        ssigaction(SIGUSR1, sigusr1_handler);
        ssigaction(SIGALRM, sigalarm_handler);
        alarm(8);

        while (true) {
            sleep(8);
        }

    } else { // FILS
        ssigaction(SIGALRM, alarm_handler);
        alarm(3);

        while (true) {
            sleep(3);
        }

    }

    return 0;
}