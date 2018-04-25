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

int main(int argc, char *argv[]){
    DIR *dp;
    struct dirent *dirp;
    
    if (argc != 2) {
        fprintf(stderr, "usage: myls requires directory name");
        exit(0) ;
    }
    if ((dp = opendir(argv[1]))==NULL) {
        fprintf(stderr, "%s can't be opened", argv[1]);
        exit(0);
    }
    while ((dirp = readdir(dp)) != NULL) {
        printf("%s\n", dirp->d_name);
    }
    closedir(dp);
    exit(0);
}