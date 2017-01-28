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

int main(){
	char pidString[30] = {0};
	char fullPath[512] = {0};
	getPidInChars(pidString);
//	printf("current pid %s\n", pidString);
	getPathInChars(fullPath, pidString);
//	printf("full path is %s\n", fullPath);
	FILE * file = fopen(fullPath, "r");
	if (file == NULL){
		printf("error read file");
	}
	char *line = NULL;
	size_t  len = 0;
	ssize_t read;
	
    	while ((read = getline(&line, &len, file)) != -1) {
//       		 printf("Retrieved line of length %zu :\n", read);
  //     	 	printf("%s", line);
		if (startsWith("PPid", line) == 1){
//			printf("\n\n%s\n\n", line);
			char PPID[100] ={0};
			getppidFromString(PPID, line);
			printf("%s\n", PPID);
		}
    	}

    	fclose(file);
    	if (line)
        	free(line);
	return 0;

}
