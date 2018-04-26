//
//  shFuncs.c
//  MyFirstShell
//
//  Created by LeanderDavis on 4/24/18.
//  Copyright (c) 2018 LeanderDavis. All rights reserved.
//

#include "shFuncs.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "shloop.h"

bool listener(char* cmd[]){//returns false if no commands are in there
    if((strcmp(cmd[0], "mypwd"))==0){
        mypwd();
        return true;
    }else if((strcmp(cmd[0], "myexit"))==0){
        myexit();
        return true;
    }else if((strcmp(cmd[0], "mycd"))==0){
        mycd(cmd[1]);
        return true;
    }
    
    return false;
}
void mypwd(){
    char cwd[50];
    
    getcwd(cwd, 50);//not working as intended
    //char* currentPath = getenv("CWD");
    perror("mypwd");
    printf("cwd: %s\n", cwd);
}
void myexit(){
    exit(0);
}

void mycd(const char* newDir){/*

    if(chdir(newDir) != 0){
        perror("error: cannot cd");
    }    

}
