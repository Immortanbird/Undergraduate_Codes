#include "buffer.h"

int main (){
    DWORD pid = GetCurrentProcessId();
    srand(pid);

    HANDLE filemap = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, TEXT("FileMappingObject"));
    if (filemap == NULL) {
        printf("Failed to get file map: Consumer %ld.\n", pid);
        return -1;
    }

    struct Buffer *buffer = (struct Buffer *)MapViewOfFile(filemap, FILE_MAP_ALL_ACCESS, 0, 0, BUFFER_SIZE);
    if (buffer == NULL) {
        printf("Failed to create buffer: Consumer %ld.\n", pid);
        return -1;
    }
    
    HANDLE mutex = OpenMutex(MUTEX_ALL_ACCESS, TRUE, MUTEX_NAME);
    if (mutex == NULL) {
        printf("Failed to get mutex: Consumer %ld.\n", pid);
        return -1;
    }
    
    HANDLE emptySemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, EMPTY_SEMAPHORE_NAME);
    if (emptySemaphore == NULL) {
        printf("Failed to get semaphore: Consumer %ld.\n", pid);
        return -1;
    }

    HANDLE fullSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, FULL_SEMAPHORE_NAME);
    if (fullSemaphore == NULL) {
        printf("Failed to get semaphore: Consumer %ld.\n", pid);
        return -1;
    }

    for (int i=0; i<8; i++) {
        SYSTEMTIME start, end;

        GetSystemTime(&start);

        Sleep(rand() % 2000);

        WaitForSingleObject(fullSemaphore, INFINITE);
        WaitForSingleObject(mutex, INFINITE);

        /* Extract a string */
        printf("String extracted by Consumer %ld: %s\n", pid, buffer->buf[buffer->head]);
        strcpy(buffer->buf[buffer->head], "");
        buffer->head = (buffer->head + 1) % 6;
        
        /* Print buffer */
        printf("Buffer content:\n");
        for (int j = 0; j < 6; j++)
            printf("| %-10s ", buffer->buf[j]);
        printf("|\n");

        GetSystemTime(&end);
        int *span = getTimeSpan(start, end);

        printf("Runtime for producing: %dmin %d.%dsec\n\n", span[0], span[1], span[2]);
        buffer->ConsumerCount++;

        ReleaseMutex(mutex);
        ReleaseSemaphore(emptySemaphore, 1, NULL);
    }
    
    CloseHandle(emptySemaphore);
    CloseHandle(fullSemaphore);
    CloseHandle(mutex);
    UnmapViewOfFile(buffer);
    CloseHandle(filemap);

    return 0;
}