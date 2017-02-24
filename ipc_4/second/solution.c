#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main(){
	int f1 = open("./in1", O_RDONLY);
	int f2 = open("./in2", O_RDONLY);
	if (!f1 || !f2) {
		printf("Error with opening pipes\n");
		return 0;
	}
	int sum = 0;
	fd_set read_set;
	int countClosed = 0;
	while(1){
		FD_ZERO(&read_set);
		FD_SET(f1, &read_set);
		FD_SET(f2, &read_set);
		int result = select(f2 + 1,  &read_set, NULL,
			 NULL, NULL);

		if(result){
			if (FD_ISSET(f1, &read_set)){

				char buff[100];
				int count = read(f1, buff, 99);
				buff[count] = 0; 
				if (count <= 0 || buff[0] == EOF){
					countClosed++;	
					close(f1);
					FD_CLR(f1, &read_set);
					
					if (countClosed == 2){
						break;
					}		
				}else {
					sum += atoi(buff);
				}
			}
			if (FD_ISSET(f2, &read_set)){

				char buff[100];
				int count = read(f2, buff, 99);
				buff[count] = 0;
				if (count <= 0 || buff[0] == EOF){	
					countClosed++;
					close(f2);
					FD_CLR(f2, &read_set);
					if (countClosed == 2){
						break;
					}
				}else {
					sum += atoi(buff);
				}
			}
		}

	}
	printf("%d\n", sum);
	return 0;
}
