#include <iostream>
#include <tchar.h>
#include <synchapi.h>
#include <windows.h>

using namespace std;

void mytime(int argc, TCHAR *argv[]) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    si.cb = sizeof(si);
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));

    SYSTEMTIME StartTime, EndTime;
    GetSystemTime(&StartTime);

    if (!CreateProcess( NULL,   // No module name (use command line)
        argv[1],        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi )           // Pointer to PROCESS_INFORMATION structure
    )
    {
        printf( "CreateProcess failed (%d).\n", GetLastError() );
        return;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    GetSystemTime(&EndTime);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    printf("RunTime: %dh %dmin %d.%dsec\n", EndTime.wHour-StartTime.wHour, EndTime.wMinute-StartTime.wMinute, EndTime.wSecond-StartTime.wSecond, EndTime.wMilliseconds-StartTime.wMilliseconds);

    return;
}

int main(int argc, TCHAR *argv[]) {
    mytime(argc, argv);

    return 0;
}