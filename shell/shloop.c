//
//  shloop.c
//  MyFirstShell
//
//  Created by LeanderDavis on 4/10/18.
//  Copyright (c) 2018 LeanderDavis. All rights reserved.
//

#include "shloop.h"
#include "shFuncs.h"
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void shloop(){
    char *line = NULL;
    pid_t sentinal;
    size_t size;
    size_t status=0;
    char *arguments[100];//fix this
    //parsing variables
    char * pch;
    int i=0;
    int exStatus;

    printf("14sh>> ");//prints shell header to prompt user where to enter data
    status=getline(&line, &size, stdin);
    
    
    //parsing string
    
    //write something to put the string into othr string
    pch = strtok (line," \n");
    while (pch != NULL)
    {
        //printf ("%s\n",pch);
        arguments[i]=pch;//puts the rest of the string into an array of strings
        pch = strtok (NULL, " \n");
        //printf("%s\n",arguments[i]);
        arguments[i+1]=NULL;
        i++;
    }
    //implement buildin funcs
    if (!(listener(arguments))) {//moved loop here
        sentinal=fork();
        //printf("sentinal = %d", sentinal);
        
        if(sentinal==0){//makes child to run commands
            
            
            //end of parsing
            //printf("status = %zu\n", status);
            if (status==1) {// fix the ordering child should be made first then call get the command
                printf("\nno command given \n");
            }else {//put exec here
                exStatus=execvp(arguments[0], arguments);//("./", arguments);//maybe path needs to be better!!!!!!!!!
                perror(arguments[0]);
                //printf("%s exStatus %d\n", arguments[0], exStatus);
            }
        }else if (sentinal==-1){
            perror("fork");
            wait(&sentinal);//&status);//from last homework to get status #6
            
        }else{//parent waits for child to finish
            wait(&sentinal);//&status);//from last homework to get status #6
        }
    }
    /*
    sentinal=fork();
    //printf("sentinal = %d", sentinal);
    
    if(sentinal==0){//makes child to run commands


        //end of parsing
        //printf("status = %zu\n", status);
        if (status==1) {// fix the ordering child should be made first then call get the command
            printf("\nno command given \n");
        }else {//put exec here
            exStatus=execvp(arguments[0], arguments);//("./", arguments);//maybe path needs to be better!!!!!!!!!
	    perror("execvp"); 
            //printf("%s exStatus %d\n", arguments[0], exStatus);
        }
    }else if (sentinal==-1){
        perror("fork");
        wait(&sentinal);//&status);//from last homework to get status #6

    }else{//parent waits for child to finish
        wait(&sentinal);//&status);//from last homework to get status #6
    }
    */
}
