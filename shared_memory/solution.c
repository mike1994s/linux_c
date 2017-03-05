#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#define COUNT_NUM 100

const int SIZE_SEGMENT = 1000;
int main(int argc, char ** argv){
	if (argc < 3){
		printf("NOt enough parameter.\n use : ./solution {num1} {num2}\n");
		return 1;
	}

	int first = atoi(argv[1]);
	int second = atoi(argv[2]);
//	printf("first = %d, second = %d\n", first, second);
	key_t keymy = ftok(argv[0], 1);
	int first_shmid = shmget(first, SIZE_SEGMENT, 0666);
	int second_shmid = shmget(second, SIZE_SEGMENT, 0666);
	int third_shmid = shmget(keymy, SIZE_SEGMENT, IPC_CREAT |  0666);
	int *shm_first = shmat(first_shmid, NULL, 0);
	int *shm_sec = shmat(second_shmid, NULL, 0);
	int i = 0;	
	int *res =shmat(third_shmid, NULL, 0);
	i = 0;
	for (; i < COUNT_NUM; ++i){
		
		res[i] = shm_first[i] + shm_sec[i];
//		printf("(%d)\tfirst = %d\t second=%d\tres = %d\n",i,shm_first[i], shm_sec[i], res[i]);
	}
	printf("%d\n", keymy);

	return 0;
}

