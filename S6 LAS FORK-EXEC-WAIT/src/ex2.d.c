#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#include "utils_v1.h"

void childProcess() {
    char first[] = "4 5 6\n";
    write(1, first, strlen(first));
    exit(EXIT_SUCCESS);
}

int main(int argc, char const *argv[]) {

    char second[] = "1 2 3\n";

    int childId = fork_and_run0(childProcess);

    // processus parent
    int status;
    swaitpid(childId, &status, 0); // wait for the child to finish
    if (WIFEXITED(status)) {
        printf("Exit code enfant : %d\n", WEXITSTATUS(status));
    }

    write(1, second, strlen(second));


    return 0;
}
