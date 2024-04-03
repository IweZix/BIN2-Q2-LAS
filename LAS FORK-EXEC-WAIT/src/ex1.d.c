#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    
    char first[] = "Trois.. Deux.. Un.. ";
    char second[] = "Partez !";

    printf("%s", first);

    int childId = fork();

        if (childId == -1) {
        perror("fork");
        exit(1);
    }

    if (childId == 0) {
        // processus fils
        printf("%s", second);
    } else {
        // processus parent
        int status;
        waitpid(childId, &status, 0);
    }


    return 0;
}
