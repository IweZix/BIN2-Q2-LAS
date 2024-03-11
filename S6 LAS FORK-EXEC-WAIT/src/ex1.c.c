#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    
    char first[] = "Trois.. Deux.. Un.. \n";
    char second[] = "Partez !\n";


    write(1, first, strlen(first));

    int childId = fork();

    if (childId == -1) {
        perror("fork");
        exit(1);
    }

    if (childId == 0) {
        // processus fils
        write(1, second, strlen(second));
    } else {
        // processus parent
    }


    return 0;
}
