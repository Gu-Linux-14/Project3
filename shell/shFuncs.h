//
//  shFuncs.h
//  MyFirstShell
//
//  Created by LeanderDavis on 4/24/18.
//  Copyright (c) 2018 LeanderDavis. All rights reserved.
//

#ifndef __MyFirstShell__shFuncs__
#define __MyFirstShell__shFuncs__
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

bool listener(char* cmd[]);
void mypwd();
void myexit();

void mycd(const char* newDir);


#endif /* defined(__MyFirstShell__shFuncs__) */
