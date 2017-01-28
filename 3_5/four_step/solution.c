#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


typedef struct Notes{
	char pid[100];
	char ppid[100];
}Note;
int startsWith(const char *pre, const char *str)
{
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? 0 : strncmp(pre, str, lenpre) == 0;
}
void getPathInChars(char *str, const char *pidStr){
	strcat(str, "/proc/");
	strcat(str, pidStr);
	strcat(str, "/status");
}
void getppidFromString(char * res, char *source){
	int i = 0;
	int len = strlen(source);
	int j = 0;
	while(source[i] != ' ' && i < len){
		if (isdigit(source[i])){
			res[j] = source[i];
			++j;
		}
		++i;
	}
}	
void getPPid(char * res, const char * pidString){
	char fullPath[512] = {0};
	getPathInChars(fullPath, pidString);
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

int isAppropriate(const char * name){
	int len = strlen(name);
	int i = 0;
	for (; i < len; ++i){
		if (!isdigit(name[i])){
			return 0;
		}
	}
	return 1;
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
void fillNotes(const char * dirName, Note * notes){
	DIR *dfd;
	struct dirent *dp;
	dfd = opendir(dirName);

	int i = 0;
	while((dp=readdir(dfd)) != NULL){
		if (isAppropriate(dp->d_name)){
			memset(notes[i].pid, 0, 100);
			memset(notes[i].ppid,0, 100);
			strncpy(notes[i].pid, dp->d_name, 100);
			getPPid(notes[i].ppid, notes[i].pid);
			i++;
		}
	}
	closedir(dfd);

} 

int getCountChildren(char *parent, Note * notes, int len){
	int number = 0;
	int i = 0;
	for (; i < len; ++i){
		if (strcmp(parent, notes[i].ppid) == 0){
			number = number + 1 + getCountChildren(notes[i].pid, notes, len);	
		}
	}
	return number;
}

int main(int argc, char **argv)
{
    int count = getCountNameFolderOnlyDigit("/proc/");
   // printf("%d\n", count);
    Note * notes = (Note *) malloc(sizeof(Note)*count);

    fillNotes("/proc/", notes);

/*    for (; i < count; ++i){
        printf("pid is %s, ppid is = %s\n",notes[i].pid,
		notes[i].ppid);
    }*/
    if (argc < 2){
   	printf("needd usage:\r\n ./solution {number}\n");
	free(notes);
	return 1;
    }	
    int countNum = 1 + getCountChildren(argv[1], notes, count);
    printf("%d\n", countNum);
    free(notes);
    return 0;
}
