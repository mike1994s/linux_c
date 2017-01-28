all: exe

exe: main.c hello.h lib
	gcc main.c  -L. -fPIC -lHello -o hello

lib: hello.c hello.h
	gcc hello.c -shared -fPIC -o libHello.so

clean:
	-rm libHello.so hello 2>/dev/null
