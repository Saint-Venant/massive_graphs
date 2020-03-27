--- Structure of the folder ---

bin					// will contain the executable
src
	main.c
	adjarray.h
	adjarray.c
	adjmatrix.h
	adjmatrix.c
	edgelist.h
	edgelist.c


--- To compile ---

In folder /src/, execute command "gcc main.c adjarray.c adjmatrix.c edgelist.c -O9 -o ../bin/main" where "main" will be the name of the executable.

--- To execute ---
In folder bin, execute command "./main grapheInstance.txt exerciseNumber" where :
* "grapheInstance.txt" is a given instance
* "exerciseNumber" is the number of the desired exercise to execute
