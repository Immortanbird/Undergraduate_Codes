#include <iostream>
#include <string>
#include <tchar.h>
#include <windows.h>

using namespace std;

void copyFile(TCHAR *srcpath, DWORD size, TCHAR *destpath) {
    HANDLE hsrc = CreateFile(srcpath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hsrc == INVALID_HANDLE_VALUE) {
        printf("CreateFile error: 0x%08x.\n", GetLastError());
        printf("Failed to open source file: %s\n", srcpath);
        exit(0);
    }

    HANDLE hdest = CreateFile(destpath, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hdest == INVALID_HANDLE_VALUE) {
        printf("CreateFile error: Failed to create dest file for errno 0x%08x.\n", GetLastError());
        exit(0);
    }

    char *buf = new char[MAX_PATH];
    if(!ReadFile(hsrc, buf, size, NULL, NULL)) {
        printf("ReadFile error: 0x%08x.\n", GetLastError());
        exit(0);
    }
    if(!WriteFile(hdest, buf, size, NULL, NULL)) {
        printf("WriteFile error: 0x%08x.\n", GetLastError());
        exit(0);
    }

    FILETIME creationTime, lastAccessTime, lastWriteTime;
    GetFileTime(hsrc, &creationTime, &lastAccessTime, &lastWriteTime);
    SetFileTime(hdest, &creationTime, &lastAccessTime, &lastWriteTime);

    SetFileAttributes((TCHAR *)destpath, GetFileAttributes((TCHAR* )srcpath));

    CloseHandle(hsrc);
    CloseHandle(hdest);

    return;
}

void copyDir(TCHAR *src, TCHAR *dest) {
    WIN32_FIND_DATA ffd;
    char srcpath[MAX_PATH];
    char destpath[MAX_PATH];

    strcpy(srcpath, (char *)src);
    strcat(srcpath, "\\*");

    HANDLE hfind = FindFirstFile((TCHAR *)srcpath, &ffd);
    if (hfind == INVALID_HANDLE_VALUE) {
        printf("FindFirstFile error: 0x%08x.\n", GetLastError());
        exit(0);
    }

    do {
        memset(srcpath, 0, sizeof(srcpath));
        memset(destpath, 0, sizeof(destpath));

        strcpy(srcpath, (char *)src);
        strcat(srcpath, "\\");
        strcat(srcpath, (char *)ffd.cFileName);

        strcpy(destpath, (char *)dest);
        strcat(destpath, "\\");
        strcat(destpath, (char *)ffd.cFileName);

        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (strcmp((char *)ffd.cFileName, ".") != 0 && strcmp((char *)ffd.cFileName, "..") != 0) {
                if (!CreateDirectory((TCHAR *)destpath, NULL)) {
                    printf("CreateDirectory error: 0x%08x.\n", GetLastError());
                    exit(0);
                }

                copyDir((TCHAR *)srcpath, (TCHAR *)destpath);
            }

            HANDLE hsrc = CreateFile((TCHAR *)srcpath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
            HANDLE hdest = CreateFile((TCHAR *)destpath, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);

            FILETIME creationTime, lastAccessTime, lastWriteTime;
            GetFileTime(hsrc, &creationTime, &lastAccessTime, &lastWriteTime);
            SetFileTime(hdest, &creationTime, &lastAccessTime, &lastWriteTime);

            SetFileAttributes((TCHAR *)destpath, GetFileAttributes((TCHAR *)srcpath));

            CloseHandle(hsrc);
            CloseHandle(hdest);
        }
        else
            copyFile((TCHAR *)srcpath, ffd.nFileSizeLow - ffd.nFileSizeHigh, (TCHAR *)destpath);
    } while (FindNextFile(hfind, &ffd) != 0);

    FindClose(hfind);

    return;
}

int main(int argc, TCHAR *argv[]) {
    if(argc != 3) {
        printf("Invalid command.\n");
        return -1;
    }
    
    copyDir(argv[1], argv[2]);

    HANDLE hsrc = CreateFile(argv[1], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
    HANDLE hdest = CreateFile(argv[2], GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);

    FILETIME creationTime, lastAccessTime, lastWriteTime;
    GetFileTime(hsrc, &creationTime, &lastAccessTime, &lastWriteTime);
    SetFileTime(hdest, &creationTime, &lastAccessTime, &lastWriteTime);

    SetFileAttributes(argv[2], GetFileAttributes(argv[1]));

    CloseHandle(hsrc);
    CloseHandle(hdest);

    return 0;
}