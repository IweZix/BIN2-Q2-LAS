#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

#include "utils_v2.h"

#define MAX_SZ 80

/**
 * @brief Child handler function
*/
void child_handler(void* pipe1, void* pipe2) {
    int *fatherToChild = (int*)pipe1;
    int *childToFather = (int*)pipe2;

    sclose(fatherToChild[1]);
    sclose(childToFather[0]);
    
    char line[MAX_SZ];
    int nb_line = 0;

    while(1) {
        int nb_char = sread(fatherToChild[0], &line, MAX_SZ);

        if (nb_char == 0) {
            swrite(childToFather[1], &nb_line, sizeof(int));
            break;
        } else {
            swrite(childToFather[1], &nb_char, sizeof(int));
        }
        nb_line++;
    }

    sclose(0);
    sclose(1);
}

/**
 * @brief Main function
*/
int main(int argc, char **argv) {

    int childToFather[2];
    int fatherToChild[2];
    char line[MAX_SZ + 1];
    int nb_line;
    int nb_char;

    spipe(fatherToChild);
    spipe(childToFather);

    /**
     * Fork and run child handler function
     * Give both pipes to the child handler
    */
    fork_and_run2(child_handler, fatherToChild, childToFather);

    /**
     * Ctrl+D break while loop 
    */
    while ((nb_char = sread(0, &line, MAX_SZ)) > 0) {
        line[nb_char-1] = '\0';

        swrite(fatherToChild[1], &line, strlen(line));

        sread(childToFather[0], &nb_line, sizeof(int));

        printf("%s : %d \n", line, nb_line);
    }

    // if you don't close fatherToChild[1] (write) child will never be able to return the number of lines
    sclose(fatherToChild[1]);

    sread(childToFather[0], &nb_line, sizeof(int));

    printf("Le programme à traité %d ligne(s)\n", nb_line);

    exit(0);
}