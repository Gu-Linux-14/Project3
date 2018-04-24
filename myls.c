//
//  myls.c
//  MyFirstShell
//
//  Created by LeanderDavis on 4/10/18.
//  Copyright (c) 2018 LeanderDavis. All rights reserved.
//

#include "myls.h"
//#include "apue.h"
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
    
}

int mylsNoOp(int argc, char *argv[]){
    DIR *dp;
    struct dirent *dirp;
    
    if (argc != 2) {
        //err_quit("usage: ls directory_name");
        fprintf(stderr, "usage: myls requires directory name");
        exit(0) ;
    }
    if ((dp = opendir(argv[1]))==NULL) {
        //err_sys("can't open %s", argv[1]);
        fprintf(stderr, "%s can't be opened", argv[1]);
        exit(0);
    }
    while ((dirp = readdir(dp)) != NULL) {
        printf("%s\n", dirp->d_name);
    }
    closedir(dp);
    exit(0);
}

int mylsL(int argc, char *argv[]){
    DIR *dp;
    struct dirent *dirp;
    struct stat mystat;
    char buf[512];
    
    if (argc != 2) {
        //err_quit("usage: ls directory_name");
        fprintf(stderr, "usage: myls requires directory name");
        exit(0) ;
    }
    if ((dp = opendir(argv[1]))==NULL) {
        //err_sys("can't open %s", argv[1]);
        fprintf(stderr, "%s can't be opened", argv[1]);
        exit(0);
    }
    while ((dirp = readdir(dp)) != NULL) {
        printf("%s\n", dirp->d_name);
        stat(buf, &mystat);
        printf("%zu", mystat.st_size);
        printf(" %s\n", dirp->d_name);
    }
    closedir(dp);
    exit(0);
}
