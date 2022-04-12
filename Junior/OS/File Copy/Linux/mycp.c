#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <utime.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>

#define MAX 1024

void copySoftLink(char *src, char *dest) {
    char buffer[2 * MAX];
    memset(buffer, 0, sizeof(buffer));
    
    readlink(src, buffer, 2 * MAX);
    symlink(buffer, dest);

    struct stat status;
    struct timeval ftime[2];

    ftime[0].tv_usec = 0;
    ftime[0].tv_sec = status.st_atime;
    ftime[1].tv_usec = 0;
    ftime[1].tv_sec = status.st_mtime;
    lutimes(dest, ftime);

    return;
}

void copyFile(char *src, char *dest) {
    int fp_src = open(src, 0);
    
    char BUFFER[MAX];
    int len = read(fp_src, BUFFER, MAX);

    struct stat status;
    stat(src, &status);
    
    int fp_dest = creat(dest, status.st_mode);

    do {
        if (write(fp_dest, BUFFER, len) != len) {
            printf("Write Error!\n");
            exit(-1);
        }
        len = read(fp_src, BUFFER, MAX);
    } while (len > 0);

    struct utimbuf time;
    time.actime = status.st_atime;
    time.modtime = status.st_mtime;
    utime(dest, &time);

    close(fp_src);
    close(fp_dest);

    return;
}

void copy(char *src, char *dest) {
    DIR *dir = opendir(src);
    if (dir == NULL) {
        printf("Failed to open directory.\n");
        exit(-1);
    }
    
    char srcpath[MAX];
    char destpath[MAX];
   
    struct dirent *entry = readdir(dir);

    do {
        memset(srcpath, 0, sizeof(srcpath));
        memset(destpath, 0, sizeof(destpath));
        strcpy(srcpath, src);
        strcpy(destpath, dest);
        strcat(srcpath, "/");
        strcat(destpath, "/");
        strcat(srcpath, entry->d_name);
        strcat(destpath, entry->d_name);

        if (entry->d_type == 4) {
            struct stat status;
            stat(srcpath, &status);
            
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                mkdir(destpath, status.st_mode);

                copy(srcpath, destpath);
            }
            
            struct utimbuf time;
            time.actime = status.st_atime;
            time.modtime = status.st_mtime;
            utime(destpath, &time);
        }
        else if (entry->d_type == 10)
            copySoftLink(srcpath, destpath);
        else
            copyFile(srcpath, destpath);

        entry = readdir(dir);
    } while (entry != NULL);

    closedir(dir);

    return;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Invalid Command.\n");
        return -1;
    }

    copy(argv[1], argv[2]);

    struct stat status;
    stat(argv[1], &status);
    
    struct utimbuf time;
    time.actime = status.st_atime;
    time.modtime = status.st_mtime;
    utime(argv[2], &time);

    return 0;
}