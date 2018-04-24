#include "myls.h"
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
    DIR *dp;
    struct dirent *dirp;
    struct stat mystat;
    char buf[512];
    
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

    if(argv[2] != NULL){
        if((dp = opendir(argv[2]))==NULL){
            fprintf(stderr, "%s can't be opened\n", argv[1]);
            exit(0);
        }
    }

    printf("%d\n", argc);
    if(argc == 2){
        while((dirp = readdir(dp)) != NULL){
            printf("%s\n", dirp->d_name);
        }
    }
    else if(argc == 3){
        while((dirp = readdir(dp)) != NULL){
            printf("%s\n", dirp->d_name);
            stat(buf, &mystat);
            printf("%zu", mystat.st_size);
            printf(" %s", dirp->d_name);
        }
        printf("\n");
    }
    
    closedir(dp);
    exit(0); 
}
