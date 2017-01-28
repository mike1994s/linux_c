all: exe

exe: main.c hello.h lib
	emcc main.c  -L. -fPIC -lHello -o hello

lib: hello.c hello.h
	emcc hello.c -shared -fPIC -o libHello.bc

clean:
	-rm libHello.so hello 2>/dev/null
