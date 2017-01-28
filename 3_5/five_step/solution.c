#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void goToTheRoot(){
	chdir("/");
}

void setNewSessionId(){
	setsid();
}
void printPid(){
    pid_t pid = getpid();
    long pidLong = (long)pid;
    printf("%ld\n", pidLong);
}
void closeStandart(){
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
        close(STDERR_FILENO);
}
void inLoop(){
	while(1){
	 ;
	}
}
int main(){
	int proccess = fork();
	if (proccess == 0){
		goToTheRoot();	
		printPid();
		setNewSessionId();
		closeStandart();
		inLoop();
	}else {

	}
	return 0;
}
