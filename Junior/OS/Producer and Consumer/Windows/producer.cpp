#include "buffer.h"

char *randomString() {
    static char string[10];

    for (int i=0; i<10; i++)
        string[i] = (char)('a' + rand() % 26);

    return string;
}

int main(){    
    DWORD pid = GetCurrentProcessId();
    srand(pid);

    HANDLE filemap = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, TEXT("FileMappingObject"));
    if (filemap == NULL) {
        printf("Failed to get file map: Producer %ld.\n", pid);
        return -1;
    }

    struct Buffer *buffer = (struct Buffer *)MapViewOfFile(filemap, FILE_MAP_ALL_ACCESS, 0, 0, BUFFER_SIZE);
    if (buffer == NULL) {
        printf("Failed to create buffer: Producer %ld.\n", pid);
        return -1;
    }

    HANDLE mutex = OpenMutex(MUTEX_ALL_ACCESS, TRUE, MUTEX_NAME);
    if (mutex == NULL) {
        printf("Failed to get mutex: Producer %ld.\n", pid);
        return -1;
    }
    
    HANDLE emptySemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, EMPTY_SEMAPHORE_NAME);
    if (emptySemaphore == NULL) {
        printf("Failed to get semaphore: Producer %ld.\n", pid);
        return -1;
    }

    HANDLE fullSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, FULL_SEMAPHORE_NAME);
    if (fullSemaphore == NULL) {
        printf("Failed to get semaphore: Producer %ld.\n", pid);
        return -1;
    }

    for (int i = 0; i < 12; i++) {
        SYSTEMTIME start, end;

        GetSystemTime(&start);

        Sleep(rand() % 2000);

        WaitForSingleObject(emptySemaphore, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        
        /* Add a string */
        char *dst = buffer->buf[buffer->tail];
        char *src = randomString();
        strcpy(dst, src);
        buffer->tail = (buffer->tail + 1) % 6;
        printf("String added by Producer %ld: %s\n", pid, src);

        /* Print buffer */
        printf("Buffer content:\n");
        for (int j = 0; j < 6; j++)
            printf("| %-10s ", buffer->buf[j]);
        printf("|\n");

        GetSystemTime(&end);
        int *span = getTimeSpan(start, end);

        printf("Runtime for producing: %dmin %d.%dsec\n\n", span[0], span[1], span[2]);
        buffer->ProduceCount++;
        
        ReleaseMutex(mutex);
        ReleaseSemaphore(fullSemaphore, 1, NULL);
    }
    
    CloseHandle(emptySemaphore);
    CloseHandle(fullSemaphore);
    CloseHandle(mutex);
    UnmapViewOfFile(buffer);
    CloseHandle(filemap);

    return 0;
}