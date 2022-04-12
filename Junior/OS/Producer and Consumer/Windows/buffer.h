#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

struct Buffer{
    char buf[6][11];
    int head;
    int tail;
    int ProduceCount;
    int ConsumerCount;
};

#define BUFFER_SIZE (sizeof(struct Buffer))

const TCHAR MUTEX_NAME[] = TEXT("Mutex");
const TCHAR EMPTY_SEMAPHORE_NAME[] = TEXT("EmptySemaphore");
const TCHAR FULL_SEMAPHORE_NAME[] = TEXT("FullSemaphore");

TCHAR producer[13] = TEXT("producer.exe");
TCHAR consumer[13] = TEXT("consumer.exe");

int *getTimeSpan(SYSTEMTIME start, SYSTEMTIME end) {
    static int span[] = {end.wMinute - start.wMinute, end.wSecond - start.wSecond, end.wMilliseconds - start.wMilliseconds};

    if (span[2] < 0) {
        span[2] += 1000;
        span[1] --;
    }

    if (span[1] < 0) {
        span[1] += 60;
        span[0] --;
    }

    return span;
}