#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

const char * NEED_NAME = "genenv";

int checkName(const char *pid){
	char fullPath[512]={0};
	sprintf(fullPath, "/proc/%s/comm", pid);
//	printf("full path is %s\n", fullPath);
	FILE *file = fopen(fullPath, "r");
	if (file == NULL){
		return 0;	
	}
	char buff[255]={0};
	fscanf(file, "%s", buff);
//	printf("line is = %s", buff);
	int res = 0;
	if (strstr(buff, NEED_NAME) != NULL){
		res = 1;
	}
	fclose(file);
	return res;
}
int isAppropriate(const char * name){
	int len = strlen(name);
	int i = 0;
	for (; i < len; ++i){
		if (!isdigit(name[i])){
			return 0;
		}
	}
	if (checkName(name) == 1){
		return 1;
	}
	return 0;
}

int getCountNameFolderOnlyDigit(const char * dirName){
	DIR *dfd;
	struct dirent *dp;
	dfd = opendir(dirName);
	int c = 0;
	while((dp=readdir(dfd)) != NULL){
		if (isAppropriate(dp->d_name)){
			c++;
		}
	}
	closedir(dfd);
	return c;
} 

int main(int argc, char **argv)
{
    int count = getCountNameFolderOnlyDigit("/proc/");
    printf("%d\n", count);
    return 0;
}
