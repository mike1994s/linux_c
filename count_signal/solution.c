#include<stdio.h>
#include<signal.h>
#include<unistd.h>

int count_usr1 = 0;
int count_usr2 = 0;

int wait = 1;
void sig_handler(int signo)
{
    if (signo == SIGUSR1){
//	printf("SIGUSR1\n");
        count_usr1++;
   } else if (signo == SIGUSR2){
//	printf("SIGUSR2\n");
        count_usr2++;
   } else if (signo == SIGTERM){
  //      printf("SIGTERM\n");
	wait = 0;
   }
}

int main(void)
{
  if (signal(SIGUSR1, sig_handler) == SIG_ERR)
  	printf("\ncan't catch SIGINT\n");
  if (signal(SIGUSR2, sig_handler) == SIG_ERR)
  	printf("\ncan't catch SIGINT\n");
  if (signal(SIGTERM, sig_handler) == SIG_ERR)
  	printf("\ncan't catch SIGINT\n");

  while(wait == 1) 
    sleep(1);
  printf("%d %d\n", count_usr1, count_usr2);
  return 0;
}
