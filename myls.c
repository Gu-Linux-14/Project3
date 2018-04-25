#include "myls.h"
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sysexits.h>

static char *global_dir = ".";

void printPermissions(mode_t mode){
    putchar((mode & S_IRUSR) ? 'r' : '-');
    putchar((mode & S_IWUSR) ? 'w' : '-');
    putchar((mode & S_IXUSR) ? 'x' : '-');
    putchar((mode & S_IRGRP) ? 'r' : '-');
    putchar((mode & S_IWGRP) ? 'w' : '-');
    putchar((mode & S_IXGRP) ? 'x' : '-');
    putchar((mode & S_IROTH) ? 'r' : '-');
    putchar((mode & S_IWOTH) ? 'w' : '-');
    putchar((mode & S_IXOTH) ? 'x' : '-');
}

void printFiletype(mode_t mode){
    switch(mode & S_IFMT){
        case S_IFREG: putchar('-');
            break;
        case S_IFDIR: putchar('d');
            break;
        case S_IFLNK: putchar('l');
            break;
        case S_IFCHR: putchar('c');
            break;
        case S_IFBLK: putchar('b');
            break;
        case S_IFSOCK: putchar('s');
            break;
        case S_IFIFO: putchar('f');
            break;
    }
}

void printTime(time_t mod_time){
    // get current time with year
    time_t curr_time;
    time(&curr_time);
    struct tm* t = localtime(&curr_time);
    const int curr_mon = t->tm_mon;
    const int curr_yr = 1970 + t->tm_year;

    // get mod time and year
    t = localtime(&mod_time);
    const int mod_mon = t->tm_mon;
    const int mod_yr = 1970 + t->tm_year;

    // determine format based on years
    const char* format = ((mod_yr == curr_yr)
                       && (mod_mon >= (curr_mon - 6)))
                           ? "%b %e %H:%M"
                           : "%b %e  %Y";

    char time_buf[128];
    strftime(time_buf, sizeof(time_buf), format, t);
    printf("%s", time_buf);
}

struct stat getStats(const char *filename){
    char path[1024];
    sprintf(path, "%s/%s", global_dir, filename);
    struct stat mystat;

    if(lstat(path, &mystat) < 0){   
        perror(path);
        exit(EX_IOERR);
    }

    return mystat;
}

void printNameOrLink(const char *filename, mode_t mode){
    if(mode & S_IFLNK){
        char link_buf[512];
        int count = readlink(filename, link_buf, sizeof(link_buf));

        if(count >= 0){
            link_buf[count] = '\0';
            printf(" %s -> %s \n", filename, link_buf);
            return;
        }
    }

    printf(" %s", filename);
    putchar('\n');
}

void mylsL(char *filename){
    struct stat mystat;
    mystat = getStats(filename);
    
    printFiletype(mystat.st_mode);
    printPermissions(mystat.st_mode);
    printf(" %d ", mystat.st_nlink);
    printf("%8s ", getpwuid(mystat.st_uid)->pw_name);
    printf("%8s", getgrgid(mystat.st_gid)->gr_name);
    printf("%5ld ", (long)mystat.st_size);
    printTime(mystat.st_mtime);
    printNameOrLink(filename, mystat.st_mode);
}

int main(int argc, char *argv[]){
    DIR *dp;
    struct dirent *dirp;
    char *filename;
    char buf[512];
    int equal = 0;
    
    if(argc < 2){
        //err_quit("usage: ls directory_name");
        fprintf(stderr, "usage: myls requires directory name");
        exit(0) ;
    }

    if(argv[2] == NULL){
        if((dp = opendir(argv[1]))==NULL){
            fprintf(stderr, "%s can't be opened\n", argv[1]);
            exit(0);
        }
    }

    if(argc == 2){
        while((dirp = readdir(dp)) != NULL){
            printf("%s ", dirp->d_name);
        }
        putchar('\n');
    }
    else if(argc == 3){
        equal = strcmp(argv[1], "|");
        //if not pipe
        if(equal!=0){
            filename = argv[2];
            mylsL(filename);
            printf("\n");
        }
        //if pipe
        else {
            while((dirp = readdir(dp)) != NULL){
                printf("%s\n", dirp->d_name);
            }
        }
    }
    
    closedir(dp);
    exit(0);
}
