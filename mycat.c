//
//  mycat.c
//  cat command
//
//  Created by Jonathon Nguyen on 4/10/18.
//  Copyright (c) 2018 Jonathon Nguyen. All rights reserved.
//

#include "shloop.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

//#define DELIM_I " <, > "
#define MAX_SIZE 100

void mycat(int argc, char **argv[]){
	FILE *fptr;
	int ch ;
	char *fname = NULL;
	char *fnameEdit = NULL;
	char *fname2 = NULL;
	char *c = '<';

	if(argc < 2){
		printf("Enter at least 1 argument\n");
		exit(1);
	}

	if(argc == 2){
		fnameEdit = argv[1];

		if(fnameEdit[0] == c){
			fname = strtok(fnameEdit, "<");
		}
		else{
			fname = fnameEdit;
		}

		if(!(fptr = fopen(fname, "r"))){
			printf("File failed to open!");
			return -1;
			}
			ch = fgetc(fptr);
			while(ch != EOF){
				printf("%c", ch);

				ch = fgetc(fptr);

		}

		if(!feof(fptr)){
			printf("Failed to read to end of file.");
		}
		fclose(fptr);
	}

}


/*
int main(int argc, char **argv[]){
	mycat(argc, argv);
	exit(0);
}
*/
