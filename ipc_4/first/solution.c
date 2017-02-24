/**
 работаю  с popen
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
int main(int argc, char *argv[]){
	if (argc < 3){
		printf("please use : './main program param'\n");
		return 0;
	}
	char commands[100]={0};
	strcpy(commands, argv[1]);
	strcat(commands, " ");
	strcat(commands, argv[2]);

	FILE *fp = popen(commands, "r");
	if (fp == NULL){
		printf("error open commands = %s\n", commands);
		return 0;
	}
	char buf;
	buf = fgetc(fp);
	int count = 0;
	while (buf != EOF){
		if (buf == '0'){
			count++;	
		}
		buf = fgetc(fp);
	}
	pclose(fp);
	printf("%d\n", count);
	return 0;	
	
}
