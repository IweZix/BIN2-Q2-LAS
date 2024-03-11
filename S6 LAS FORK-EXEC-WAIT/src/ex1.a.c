#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    
    int a = 5;

    int childId = fork();

    if (childId == -1) {
        perror("fork");
        exit(1);
    }

    if (childId == 0) {
        // processus fils
        int b = 2*a;
        printf("a = %d\n", a); // 5
        printf("b = %d\n", b); // 10
    } else {
        // processus parent
        int b = 5*a;
        printf("a = %d\n", a); // 5
        printf("b = %d\n", b); // 25
    }


    return 0;
}
