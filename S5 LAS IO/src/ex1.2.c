#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX 10000000

int main(int argc, char const *argv[]) {
    
    // open
    int file = open(argv[1], O_RDWR | O_CREAT, 777);
    if (file == -1) {
        perror("Error opening file\n");
        exit(1);
    }

    clock_t start = clock();
    
    // write
    for (int i = 0; i < MAX; i++) {
        write(file, &i, sizeof(int));
    }

    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("Time: %f secondes\n", time);

    // close
    close(file);

    return 0;
}
