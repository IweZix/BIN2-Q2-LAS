#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    
    char first[] = "4 5 6\n";
    char second[] = "1 2 3\n";

    int childId = fork();

    if (childId == -1) {
        perror("fork");
        exit(1);
    }

    if (childId == 0) {
        // processus fils
        write(1, first, strlen(first));
        exit(EXIT_SUCCESS);
    } else {
        // processus parent
        int status;
        waitpid(childId, &status, 0); // wait for the child to finish
        if (WIFEXITED(status)) {
            printf("Exit code enfant : %d\n", WEXITSTATUS(status));
        }

        write(1, second, strlen(second));
    }


    return 0;
}
