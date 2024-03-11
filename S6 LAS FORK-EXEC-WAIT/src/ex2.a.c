#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


/**
 * proc without wait
*/
int main(int argc, char const *argv[]) {
    
    char first[] = "1 2 3\n";
    char second[] = "4 5 6\n";

    int childId = fork();

    if (childId == -1) {
        perror("fork");
        exit(1);
    }

    if (childId == 0) {
        // processus fils
        write(1, first, strlen(first));
    } else {
        // processus parent
        write(1, second, strlen(second));
    }


    return 0;
}
