#include <stdio.h>

int main(){
	char name[100];
	printf("What is your name?___");
	gets(name);
	return printf("hello %s\n", name);
}
