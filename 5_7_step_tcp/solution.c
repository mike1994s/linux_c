#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

struct sockaddr_in local;

int comp (const void * elem1, const void * elem2) 
{
    char f = *((char*)elem1);
    char s = *((char*)elem2);
    if (f < s) return 1;
    if (f > s) return -1;
    return 0;
}



int server(int num){
	int s = socket(AF_INET, SOCK_STREAM, 0);
	
	int cs;
	inet_aton("127.0.0.1",&local.sin_addr );
	local.sin_port = htons(num);
	local.sin_family = AF_INET;

	bind(s, (struct sockaddr * ) &local, sizeof(local));
	char buf[BUFSIZ];
	
	listen(s, 5);
	cs = accept(s, NULL, NULL);	
	while (1){
		read(cs, buf, BUFSIZ);
		if (strcmp("OFF", buf) == 0){
			break;
		}
		qsort(buf, strlen(buf), sizeof(char), comp);
	//	printf("%s\n", buf);
		write(cs, buf, strlen(buf) + 1);
		memset(buf, 0, BUFSIZ);
	}
	close(cs);

	return 0;
}

int client(int port){
	int s = socket(AF_INET, SOCK_STREAM, 0);
	inet_aton("127.0.0.1",&local.sin_addr );
	local.sin_port = htons(port);
	local.sin_family = AF_INET;
	connect(s, (struct sockaddr*)&local, sizeof(local));
	
	char buf[BUFSIZ]="ZXYACBGFWQ!";
	write(s, buf, strlen(buf) + 1);
	memset(buf, 0, BUFSIZ);
	
	read(s, buf, BUFSIZ);
	printf("%s\n", buf);
	close(s);
	return 0;
}

int main(int c, char **v){

	
	if (c < 2){
		return 1;
	}
	int port = atoi(v[1]);
	if (c == 2){
		server(port);
	}
	if (c == 3){
		printf("client\n");
		client(port);
	}

	return 0;
}
