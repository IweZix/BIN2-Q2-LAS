#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10000000

int main(int argc, char const *argv[]) {
    
    FILE* file = fopen(argv[1], "a");
    if (file == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    clock_t start = clock();
    
    for (int i = 0; i < MAX; i++) {
        fwrite(&i, sizeof(int), 1, file);
    }

    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("Time: %f secondes\n", time);

    fclose(file);

    return 0;
}
