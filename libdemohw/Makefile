all: lib

lib: solution.h solution.c
	gcc -o libsolution.so -shared -fPIC solution.c

clean:
	-rm libsolution.so 2> /dev/null
