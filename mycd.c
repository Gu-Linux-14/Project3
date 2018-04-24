#include "myls.h"
//#include "apue.h"
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    
}

int cd(char **args){
	if (args[1] == NULL){
	fprintf(stderr, "usage: expected argument to \"cd\"\n");
	}
	else if (chdir(args[1]) != 0)
		perror("error: cannot cd");

	return 1;
}
