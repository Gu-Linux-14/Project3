//#include <mycp.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

char cwd[1024];


int isDirectory(const char *path) {
	struct stat buff;
	if(stat(path, &buff) != 0)
		return 0;
	return S_ISDIR(buff.st_mode);
}

int mycp(int argc, char**argv[]) {
	getcwd(cwd, sizeof(cwd));	
	if(argc == 3){
		return mycpFile(argv[1], argv[2]);
	}
	else if(argc == 4) {
		return mycpRecurr(argv[2], argv[3], 0);
	}
	else {
		return -1;
	}
}
//cp source dest
int mycpFile(char *file1, char *file2) {
	FILE *fip;
	if(!(fip = fopen(file1, "r"))){
		return -1;
	}
	FILE *fop = fopen(file2, "w+");
	int c;
	while((c = fgetc(fip)) != EOF) {
		fputc(c, fop);
	}
	fclose(fip);
	fclose(fop);
	return 0;
}

int mycpRecurr(char* dir1, char* dir2, int subDir) {
	DIR *dir;
	struct dirent *dirent;

	char *dest = malloc(sizeof(char) * 1024);
	char *source = malloc(sizeof(char) * 1024);
	if(subDir == 0){
		strcpy(dest, cwd);
		strcat(dest, "/");
		strcat(dest, dir2);
		
		strcpy(source, cwd);
		strcat(source, "/");
		strcat(source, dir1);
	}
	else{
		strcpy(dest, dir2);
		strcpy(source, dir1);
	}
	
	if ((dir = opendir( dir1 )) == NULL) {
		printf("Cannot open directory %s\n", dir1);		
		memset(source, 0, sizeof(source));
		memset(dest, 0, sizeof(dest));
		exit(0);
	}
	
	else {
		if(isDirectory(source)){
			if(!isDirectory(dest)){
				mkdir(dest, 0777); 		
			}
		}
		while ((dirent = readdir(dir)) != NULL) {
			char tempd[1024];
			strcpy(tempd, dest);
			strcat(tempd, "/");
			strcat(tempd, dirent->d_name);
			char temps[1024];
			strcpy(temps, source);
			strcat(temps, "/");
			strcat(temps, dirent->d_name);
			if(strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0) {
				memset(temps, 0, sizeof(temps));
				memset(tempd, 0, sizeof(tempd));
				continue;
			}	
			else if(isDirectory(temps)){
				mycpRecurr(temps, tempd, 1);	
				memset(temps, 0, sizeof(temps));
				memset(tempd, 0, sizeof(tempd));

			}
			
			mycpFile(temps, tempd);	
			memset(temps, 0, sizeof(temps));
			memset(tempd, 0, sizeof(tempd));
							
		}	

			memset(source, 0, sizeof(source));
			memset(dest, 0, sizeof(dest));
	}
	return 0;
}



int main(int argc, char **argv[]) {
	mycp(argc, argv);
}

