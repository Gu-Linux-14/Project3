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
	FILE *fptr, *fptr2;
	int ch ;
	char *fname = NULL;
	char *fnameEdit = NULL;
	char *fnameEdit2 = NULL;
	char *fname2 = NULL;
	char c = '<';
	char c2 = '>';

	if(argc == 3){
		fnameEdit = argv[1];
		fnameEdit2 = argv[2];

		//editing first argument to remove redirection
		if(fnameEdit[0] == c){
			fname = strtok(fnameEdit, "<");
		}
		else{
			fname = fnameEdit;
		}

		//editing second argument to remove redirection
		if(fnameEdit2[0] == c2){
			fname2 = strtok(fnameEdit2, ">");
		}
		else{
			fname2 = fnameEdit2;
		}

		//file validation
		if(!(fptr = fopen(fname, "r"))){
			printf("File failed to open!");
			return -1;
		}

		//file2 validation
		if(!(fptr2 = fopen(fname2, "w+"))){
			printf("File failed to be created!");
			return -2;
		}

		ch = fgetc(fptr);
		// redirecting contents of fptr to fptr2
		while(ch != EOF){
			fputc(ch, fptr2);
			ch = fgetc(fptr);
		}

		//checking for end of file
		if(!feof(fptr)){
			printf("Failed to read to end of file.");
		}
			fclose(fptr2);

	}
	else if(argc == 2){
		fnameEdit = argv[1];

		//editing first argument to remove redirection
		if(fnameEdit[0] == c){
			fname = strtok(fnameEdit, "<");
		}
		else{
			fname = fnameEdit;
		}

		//file validation
		if(!(fptr = fopen(fname, "r"))){
			printf("File failed to open!");
			return -1;
		}

		ch = fgetc(fptr);
		// print to terminal
		while(ch != EOF){
			printf("%c", ch);
			ch = fgetc(fptr);
		}

		//checking for end of file
		if(!feof(fptr)){
			printf("Failed to read to end of file.");
		}

	}else{
		printf("Enter at least 1 argument\n");
		exit(1);
	}


	//close file
	fclose(fptr);
}


int main(int argc, char **argv[]){
	mycat(argc, argv);
	exit(0);
}


