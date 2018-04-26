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
//#define MAX_SIZE 100

void mycat(int argc, char **argv[]){
	FILE *fptr;
	int ch ;
	char *fname = NULL;
	char *fname2 = NULL;
	char *c = '<';

	if(argc < 2){
		printf("Enter at least 1 argument\n");
		exit(1);
	}

	if(argc == 2){
		fname = argv[1];

		if(!(fptr = fopen(fname, "r"))){
			printf("File failed to open!");
			exit(-1);
		}
		ch = fgetc(fptr);
		while(ch != EOF){
			printf("%c", ch);

			ch = fgetc(fptr);

		}
		fclose(fptr);
	}


/*
	if(argv[1]){
		//fname = strtok(argv[1], DELIM_I);
		fname = argv[1];
		if(strchr(fname, c) == '<')
		{
			printf("redirecting");
		}

		if(argv[2]){
			fname2 = strtok(argv[2], DELIM_I);
			printf(fname2);
		}
		printf(fname);
	}

	*/
	

}



/*
int main(int argc, char **argv[]){
	mycat(argc, argv);
	exit(0);
}
*/
