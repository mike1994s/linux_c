#include <stddef.h>
#include "solution.h"
#include <stdio.h>
#include <string.h>

int stringStat(const char *string, size_t multiplier, int *count){
	size_t size = strlen(string);
	size = size * multiplier;
	*count = *count + 1;
	return (int)size;
}
