all: solution

solution: solution.c
	gcc solution.c -fPIC -ldl -Wl,-rpath=. -o solution
lib: shared.c
	gcc shared.c -shared -fPIC -o libShared.so 
