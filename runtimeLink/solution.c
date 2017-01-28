#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
int (*func)(int val);

bool init_library(const char * libName, const char * funcName){
	void *hdl = dlopen(libName, RTLD_LAZY);
	if (hdl == NULL){
		return false;
	}
	func =(int (*)(int))dlsym(hdl, funcName);
	if (func == NULL){
		return false;	
	}	
	return true;
	
}

int main(int argc, char *argv[]){
	if (argc < 4){
		return -1;
	}
	const char * libName = argv[1];
	const char * funcName = argv[2];
	int val = atoi(argv[3]);

//	printf("Libname = %s, funcName= %s, argument = %d\n", libName, funcName, val);
	if (init_library(libName, funcName)){
		printf("%d\n", func(val));		
	}else {
		printf("Error init library\n");
	}
	
	return 0;
}
