#include <netdb.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
// передаем параметр сайт типа ya.ru


int main(int argc, char **argv){
	if (argc != 2){
		return -1;
	}
	struct hostent *h;
	h = gethostbyname(argv[1]);
	if (h == NULL){
		printf("error\n");	
		return -1;
	}
//	printf("canonical name = %s\n",h->h_name);
//	printf("Type = %s len = %d\n ", (h->h_addrtype == AF_INET)?"IPV4" : "IPV6", h->h_length);
	int i = 0;
	while (h->h_addr_list[i] != NULL){
		struct in_addr * a = (struct in_addr *) h->h_addr_list[i];
		printf("%s\n", inet_ntoa(*a));
		++i;
	}
	return 0;
}
