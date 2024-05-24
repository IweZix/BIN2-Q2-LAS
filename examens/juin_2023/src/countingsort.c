#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "utils_v2.h"

#define TABSIZE 1000
#define KEY_SHM 324
#define KEY_SEM 865
#define PERM 0666

int pipefd[2];

void childHandler() {
    // 5
    int sem_id = sem_create(KEY_SEM, 1, PERM, 1);
    int shm_id = sshmget(KEY_SHM, TABSIZE*sizeof(int), IPC_CREAT | PERM);
    int* shared_memory_tab = sshmat(shm_id);

    sclose(pipefd[1]);

    int value;
    int res = sread(pipefd[0], &value, sizeof(int));
    while (res == sizeof(int)) {
        sem_down0(sem_id);
        shared_memory_tab[value] += 1;
        sem_up0(sem_id);
        res = sread(pipefd[0], &value, sizeof(int));
    }

    sclose(pipefd[0]);
    sshmdt(shared_memory_tab);
}

int main(int argc, char *argv[]) {

    if (argc < 4) {
        printf("ERROR\n");
        printf("Usage : ./countingsort [int nb child] 2 5 6 8 4 2 5 8 9 5 2 3 6\n");
    }
    
    // 1
    int sem_id = sem_create(KEY_SEM, 1, PERM, 1);
    int shm_id = sshmget(KEY_SHM, TABSIZE*sizeof(int), IPC_CREAT | PERM);
    int* shared_memory_tab = sshmat(shm_id);

    // 2
    spipe(pipefd);

    // 3
    int nb_child = atoi(argv[2]);

    for (int i = 0; i < nb_child; i++) {
        fork_and_run0(childHandler);
    }

    // 4
    sclose(pipefd[0]);
    for (int i = 2; i < argc; i++) {
        int number = atoi(argv[i]);
        swrite(pipefd[1], &number, sizeof(int));
    }
    sclose(pipefd[1]);
    
    // 6
    for (int i = 0; i < nb_child; i++) {
        swaitpid(-1, NULL, 0);
    }

    // 7
    sem_down0(sem_id);
    for (int i = 0; i < TABSIZE; i++) {
        for (int j = 0; j < shared_memory_tab[i]; j++) {
            printf("%d ", i);
        }
    }
    sem_up0(sem_id);
    

    

    // 8
    sshmdt(shared_memory_tab);
    sshmdelete(shm_id);
    sem_delete(sem_id);
}