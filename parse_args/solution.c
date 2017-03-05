#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int c, char **v){
	struct option opts[]={
		{"query", required_argument, 0, 'q'},
		{"longinformationrequest", no_argument, 0, 'i'},
		{"version", no_argument, 0, 'v'},
		{0,0,0,0},
	};
	int opchar = 0;
	int op_index= 0;
	int isOk = 1;
	while( -1 != (opchar = getopt_long(c, v, "q:iv",opts, &op_index)) ){
		switch(opchar){
			case 'q':
				break;
			case 'i':
				break;
			case 'v':
				break;
			default:
				isOk = 0;
				break;
				
		}
	}
	if (isOk == 1){
		printf("+");
	}else {
		printf("-");
	}	
	return 0;
}
