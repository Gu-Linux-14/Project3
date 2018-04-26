//
//  mysh.c
//  MyFirstShell
//
//  Created by LeanderDavis on 4/24/18.
//  Copyright (c) 2018 LeanderDavis. All rights reserved.
//

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "shloop.h"
#define BUFFERSIZE 4096

int main(int argc, const char * argv[]) {
    //char buffer[BUFFERSIZE];//may not need this
    //changing path
    char* path = getenv("PATH");
    char cwd[50];
    char *colon=":";

    
    getcwd(cwd, 50);//not working as intended
    //fix this
    char* newpath = (char*)malloc((strlen("PATH=") + strlen(path) + strlen(cwd) + 1) * sizeof(char));//to put current path in path variable
    strncpy(newpath, "PATH=", strlen("PATH="));
    strncat(newpath, path, strlen(path));
    strncat(newpath, colon, strlen(colon));
    strncat(newpath, cwd, strlen(cwd));
    //putenv(newpath);
    //printf("current path %s\n", cwd);
    
    //printf("%s\n", newpath);
    setenv("PATH", newpath, 1);//using this one so i can delete free newpath
    free(newpath);
    //finished path
    //getcwd(newCwd, 50);//not working as intended
    char* currentPath = getenv("PATH");
    //printf("\nNew %s\n", currentPath);
    
    while (true) {//running in loop
        shloop();
    }
    return 0;
}
