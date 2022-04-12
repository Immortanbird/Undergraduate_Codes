#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

void mytime(int argc, char* argv[]) {
    pid_t pid = fork();
    struct timeval StartTime, EndTime;
    int status;
    
    if (pid < 0) {
        printf("Fork failed.\n");
        return;
    }
    
    if (pid == 0) {
        printf("Child process:%s\n", argv[1]);
        execv(argv[1], &argv[1]);
        return;
    }
    
    gettimeofday(&StartTime, NULL);
    
    wait(&status);

    gettimeofday(&EndTime, NULL);

    printf("RunTime: %d.%d sec\n", EndTime.tv_sec-StartTime.tv_sec, EndTime.tv_usec-StartTime.tv_usec);
    return;
}

int main(int argc, char* argv[]) {
    mytime(argc, argv);

    return 0;
}