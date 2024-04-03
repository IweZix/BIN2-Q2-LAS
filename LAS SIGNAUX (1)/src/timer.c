#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>

#include "utils_v1.h"

static const char *const HELLO = "HELLO, I am Timer ! ;)\n";
static const char *const DOT = ".";

void sig_handler (int sig) {
    write(1, strsignal(sig), strlen(strsignal(sig)));
}

int main(int argc, char const *argv[]) {
    write(1, HELLO, strlen(HELLO));

    for (int i = 1; i < 32; i++) {
        if (i == 9 || i == 19) {
            continue;
        }
        ssigaction(i, sig_handler);
    }

    int pid = sfork();

    if (pid == 0) {
        while (true) {
            write(1, DOT, strlen(DOT));
            sleep(1);
        }
    } else {
        while (true) {
            
        }
        write(1, "Fin du père\n", strlen("Fin du père\n"));
    }

    return 0;
}
