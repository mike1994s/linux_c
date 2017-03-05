
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

struct sockaddr_in local;

int server(){
	int s = socket(AF_INET, SOCK_STREAM, 0);
	
	int cs;
	inet_aton("127.0.0.1",&local.sin_addr );
	local.sin_port = htons(1234);
	local.sin_family = AF_INET;

	bind(s, (struct sockaddr * ) &local, sizeof(local));
	
	listen(s, 5);
	cs =accept(s, NULL, NULL);
	
	char buf[BUFSIZ];
	read(cs, buf, BUFSIZ);
	printf("%s\n", buf);
	close(cs);
	return 0;
}

int client(){
	int s = socket(AF_INET, SOCK_STREAM, 0);
	inet_aton("127.0.0.1",&local.sin_addr );
	local.sin_port = htons(1234);
	local.sin_family = AF_INET;
	connect(s, (struct sockaddr*)&local, sizeof(local));
	
	char buf[BUFSIZ]="Hello!\n";
	write(s, buf, strlen(buf) + 1);
	close(s);
	return 0;
}

int main(int c, char **v){

	if (c != 2){
		printf("Use: %s, [s|c]\n", v[0]);
		return 1;
	}
	if (v[1][0] == 's'){
		server();
	}
	if (v[1][0] == 'c'){
		client();
	}
	return 0;
}
