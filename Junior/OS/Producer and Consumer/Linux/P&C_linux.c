#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/wait.h>

#define SHM_KEY 1000
#define SEM_KEY 2000

#define MUTEX 0
#define EMP_SEM 1
#define FUL_SEM 2

struct Buffer{
    char str[6][11];
    int head;
    int tail;
};

#define BUFFER_SIZE (sizeof(struct Buffer))

char *randomString() {
    static char string[10];

    for (int i=0; i < rand() % 10; i++)
        string[i] = (char)('a' + rand() % 26);

    return string;
}

void P(int semaphoreID, int semaphoreIndex) {
    struct sembuf temp = {semaphoreIndex, -1, 0};

    semop(semaphoreID, &temp, 1);

    return;
}

void V(int semaphoreID, int semaphoreIndex) {
    struct sembuf temp = {semaphoreIndex, 1, 0};

    semop(semaphoreID, &temp, 1);

    return;
}

int main() {
    int sharedMemoryID = shmget(SHM_KEY, BUFFER_SIZE, IPC_CREAT | 0600);
    if (sharedMemoryID < 0) {
        printf("Failed to apply for shared memory: %s.\n", strerror(errno));
        exit(-1);
    }

    struct Buffer *sharedMemoryAddr = shmat(sharedMemoryID, 0, 0);
    if (sharedMemoryAddr == (void *)-1) {
        printf("Failed to attach shared memory to process: %s.\n", strerror(errno));
        exit(-1);
    }

    memset(sharedMemoryAddr, 0, BUFFER_SIZE);

    shmdt(sharedMemoryAddr);
    
    int semaphoreID = semget(SEM_KEY, 3, IPC_CREAT | 0600);
    if (semaphoreID < 0) {
        printf("Failed to create semaphore: %s.\n", strerror(errno));
        exit(-1);
    }

    semctl(semaphoreID, MUTEX,   SETVAL, 1);
    semctl(semaphoreID, EMP_SEM, SETVAL, 6);
    semctl(semaphoreID, FUL_SEM, SETVAL, 0);

    for (int i=0; i<2; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            printf("Failed to fork producer.\n");
            exit(-1);
        }

        /* Producer */
        if (pid == 0) {
            srand((unsigned)getpid());

            sharedMemoryAddr = shmat(sharedMemoryID, 0, 0);
            if (sharedMemoryAddr == (void *)-1) {
                printf("Failed to attach shared memory to producer.\n");
                exit(-1);
            }

            for (int j=0; j<12; j++) {
                struct timeval start, end;
                gettimeofday(&start, NULL);

                sleep(rand() % 5);

                P(semaphoreID, EMP_SEM);
                P(semaphoreID, MUTEX);

                /* Add a string */
                char *src = randomString();
                strcpy(sharedMemoryAddr->str[sharedMemoryAddr->tail], src);
                sharedMemoryAddr->tail = (sharedMemoryAddr->tail + 1) % 6;
                printf("String added: %s\n", src);

                /* Print buffer */
                printf("Buffer content:\n");
                for (int k = 0; k < 6; k++)
                    printf("| %-10s ", sharedMemoryAddr->str[k]);
                printf("|\n");

                fflush(stdout);

                V(semaphoreID, FUL_SEM);
                V(semaphoreID, MUTEX);

                gettimeofday(&end, NULL);
                printf("Runtime for producing: %ld.%ldsec\n\n", end.tv_sec - start.tv_sec, end.tv_usec - start.tv_usec);
            }
            shmdt(sharedMemoryAddr);
            exit(0);
        }
    }

    /* Consumer */
    for (int i=0; i<3; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            printf("Failed to fork consumer.\n");
            exit(-1);
        }

        /* Consumer */
        if (pid == 0) {
            srand((unsigned)getpid());

            sharedMemoryAddr = shmat(sharedMemoryID, 0, 0);
            if (sharedMemoryAddr == (void *)-1) {
                printf("Failed to attach shared memory to consumer.\n");
                exit(-1);
            }

            for (int j=0; j<8; j++) {
                struct timeval start, end;
                gettimeofday(&start, NULL);

                sleep(rand() % 5);

                P(semaphoreID, FUL_SEM);
                P(semaphoreID, MUTEX);

                /* Extract a string */
                printf("String extracted: %s\n", sharedMemoryAddr->str[sharedMemoryAddr->head]);
                strcpy(sharedMemoryAddr->str[sharedMemoryAddr->head], "");
                sharedMemoryAddr->head = (sharedMemoryAddr->head + 1) % 6;

                /* Print buffer */
                printf("Buffer content:\n");
                for (int k = 0; k < 6; k++)
                    printf("| %-10s ", sharedMemoryAddr->str[k]);
                printf("|\n");

                fflush(stdout);

                V(semaphoreID, EMP_SEM);
                V(semaphoreID, MUTEX);

                gettimeofday(&end, NULL);
                printf("Runtime for consuming: %ld.%ldsec\n\n", end.tv_sec - start.tv_sec, end.tv_usec - start.tv_usec);
            }
            shmdt(sharedMemoryAddr);
            exit(0);
        }
    }

    for (int i = 0; i < 5; i++)
        wait(NULL);

    printf("All processes completed.\n");
    semctl(semaphoreID, 0, IPC_RMID);
    shmctl(sharedMemoryID, IPC_RMID, NULL);

    exit(0);
}