#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
void getPidInChars(char * arr){
	pid_t currentPid = getpid();
	sprintf(arr, "%s%ld", arr,(long) currentPid);
}

void getPathInChars(char *str, const char *pidStr){
	strcat(str, "/proc/");
	strcat(str, pidStr);
	strcat(str, "/status");
}
int startsWith(const char *pre, const char *str)
{
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? 0 : strncmp(pre, str, lenpre) == 0;
}
void getppidFromString(char * res, char *source){
	int i = 0;
	int len = strlen(source);
	int j = 0;
	while(source[i] != ' ' && i < len){
		if (isdigit(source[i])){
			res[j] = source[i];
			++j;
		//	putchar(source[i]);
		}
		++i;
	}
}
void printAllPath(char * res, const char * pidString){
	char fullPath[512] = {0};
	getPathInChars(fullPath, pidString);
//	printf("full path is = %s\n", fullPath);
	FILE * file = fopen(fullPath, "r");
	if (file == NULL){
		printf("error read file");
	}
	char *line = NULL;
	size_t  len = 0;
	ssize_t read;
    	while ((read = getline(&line, &len, file)) != -1) {
		if (startsWith("PPid", line) == 1){
			getppidFromString(res, line);
		
		}
    	}

    	fclose(file);
    	if (line)
        	free(line);
}

int main(int argc, char*argv[]){
	if (argc < 2){
		printf("need use:\r\n ./solution {pid}\n");
		return 1;
	}
	char ppid[100] = {0};
	char pid[100] = {0};
 	strncpy(pid, argv[1], 100);
	if (strcmp(pid, "1") == 0){
		printf("1\n");
		return 0;
	}
	printf("%s\n", pid);
	printAllPath(ppid, pid);
	
	while (strcmp(ppid, "1") != 0){
		printf("%s\n", ppid);	
		strncpy(pid, ppid,100);
		memset(&ppid[0], 0, sizeof(ppid));
		printAllPath(ppid, pid);
	}
	printf("%s\n", ppid);	
	return 0;
}
