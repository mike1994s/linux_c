#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<signal.h>

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
int isNeedRun = 1;
void inLoop(){
	while(isNeedRun){
	 ;
	}
}
void sig_handler(int signo)
{
    if (signo == SIGURG){
        isNeedRun = 0;
   } 
}

void createSignalHandler(){
     if (signal(SIGURG, sig_handler) == SIG_ERR)
  	printf("\ncan't catch SIGINT\n");
}
int main(){
	int proccess = fork();
	if (proccess == 0){
		goToTheRoot();	
		printPid();
		setNewSessionId();
		closeStandart();
		createSignalHandler();
		inLoop();
	}else {

	}
	return 0;
}
