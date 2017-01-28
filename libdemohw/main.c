#include <stdio.h>
#include "solution.h"

int main(){
	
	int val = 10;
	int *count = &val;
	
	int size = stringStat("hello", 3, count);
	printf("size = %d, count = %d\n", size, *count);
	return 0;
}
