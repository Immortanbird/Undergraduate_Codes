#include "buffer.h"

int main() {
    DWORD pid;
    pid = GetCurrentProcessId();

    HANDLE mem = CreateFileMapping(
        INVALID_HANDLE_VALUE,       // use paging file
        NULL,                       // default security
        PAGE_READWRITE,             // read/write access
        0,                          // maximum object size (high-order DWORD)
        sizeof(struct Buffer),      // maximum object size (low-order DWORD)
        TEXT("FileMappingObject")   // name of mapping object
    );
    if (mem == NULL) {
        printf("Control: Failed to create shared memory.\n");
        return -1;
    }

    HANDLE mutex = CreateMutex(NULL, FALSE, MUTEX_NAME);
    if (mutex == NULL) {
        printf("Control: Failed to create mutex.\n");
        return -1;
    }

    HANDLE emptySemaphore = CreateSemaphore(NULL, 6, 6, EMPTY_SEMAPHORE_NAME);
    if (emptySemaphore == NULL) {
        printf("Control: Failed to create semaphore \"Empty\".\n");
        return -1;
    }

    HANDLE fullSemaphore = CreateSemaphore(NULL, 0, 6, FULL_SEMAPHORE_NAME);
    if (fullSemaphore == NULL) {
        printf("Control: Failed to create semaphore \"Full\".\n");
        return 0;
    }

    struct Buffer *buffer = (struct Buffer *)MapViewOfFile(mem, FILE_MAP_ALL_ACCESS, 0, 0, BUFFER_SIZE);
    if (buffer == NULL) {
        printf("Control: Failed to create buffer.\n");
        return -1;
    }
    
    memset(buffer, 0, BUFFER_SIZE);

    PROCESS_INFORMATION pi[5];
    STARTUPINFO si[5];
    ZeroMemory(pi, sizeof(pi));
    ZeroMemory(si, sizeof(si));

    for(int i=0; i<5; i++)
        si[i].cb = sizeof(STARTUPINFO);
    
    /* Create producer process */
    for(int i=0; i<2; i++) {
        if (!CreateProcess(
            NULL,           // No module name (use command line)
            producer,       // Command line
            NULL,           // Process handle not inheritable
            NULL,           // Thread handle not inheritable
            TRUE,           // Set handle inheritance to FALSE
            NORMAL_PRIORITY_CLASS,              // No creation flags
            NULL,           // Use parent's environment block
            NULL,           // Use parent's starting directory 
            &si[i],         // Pointer to STARTUPINFO structure
            &pi[i]          // Pointer to PROCESS_INFORMATION structure
            )
        ){
            printf("Failed to create producer.\n");
            return -1;
        }
    }

    /* Create cosumer process */
    for(int i=2; i<5; i++) {
        if (!CreateProcess(
            NULL,
            consumer,
            NULL,
            NULL,
            TRUE,
            NORMAL_PRIORITY_CLASS,
            NULL,
            NULL,
            &si[i],
            &pi[i]
            )
        ){
            printf("Failed to create consumer.\n");
            return -1;
        }
    }
    
    HANDLE process[5];
    for(int i=0; i<5; i++)
        process[i] = pi[i].hProcess;
    
    WaitForMultipleObjects(5, process, TRUE, INFINITE);

    printf("All processes completed.\n");

    /* Close handle */
    for (int i = 0; i < 5; i++) {
        if (pi[i].hProcess == 0)
            continue;
        CloseHandle(pi[i].hThread);
        CloseHandle(pi[i].hProcess);
    }
    CloseHandle(emptySemaphore);
    CloseHandle(fullSemaphore);
    CloseHandle(mutex);
    
    printf("Produce: %d\nConsume: %d\n", buffer->ProduceCount, buffer->ConsumerCount);
    
    UnmapViewOfFile(buffer);
    CloseHandle(mem);
    
    Sleep(10000);

    return 0;
}