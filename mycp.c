//#include <mycp.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>


int mycp(int argc, char**argv[]) {
	if(argc == 3){
		return mycpFile(argv[1], argv[2]);
	}
	else if(argc == 4) {
		return mycpRecurr(argv[2], argv[3]);
	}
	else {
		return -1;
	}
}
//cp source dest
int mycpFile(char *file1, char *file2) {
	FILE *fip;// = fopen(file1, "r");
	if(!(fip = fopen(file1, "r"))){
		printf("failed to openfile\n");
		return -1;
	}
	FILE *fop = fopen(file2, "w+");
	int c;
	while((c = fgetc(fip)) != EOF) {
		fputc(c, fop);
	}
	return 0;
}

int mycpRecurr(char* dir1, char* dir2) {
	return 0;
}



int main(int argc, char **argv[]) {
	mycp(argc, argv);
}

