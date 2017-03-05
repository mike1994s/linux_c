#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

struct sockaddr_in local;

#define COUNT_BYTE 5000
int main(int c, char **v){

	if (c != 2){
		return -1;
	}
	int port = atoi(v[1]);	
	int s = socket(AF_INET, SOCK_DGRAM, 0);
//	printf("socket = %d\n", s);
	inet_aton("127.0.0.1", &local.sin_addr);
	local.sin_port = htons(port);
	local.sin_family = AF_INET;
	
	int result = bind(s, (struct sockaddr*) &local, sizeof(local));
	//printf("%d\n", result);
	char buf[COUNT_BYTE];
	while(1){
		read(s, buf, COUNT_BYTE);
		if (strcmp("OFF\n", buf) == 0){
			break;
		}
		printf("%s\n", buf);
		memset(buf, 0, COUNT_BYTE);
	}
	close(s);
	return 0;
}
