--- Structure of the folder ---

bin					// will contain the executable
src
	main.c
	
	algos.h
	algos.c
	tools.h
	tools.c
readme.txt
tme1.pdf


--- To compile ---

In folder src/, execute command:
	"gcc main.c
		../../struct/adjarray.c
		../../struct/adjmatrix.c
		../../struct/edgelist.c
		algos.c
		tools.c
	-O9 -o ../bin/main"
where "main" will be the name of the executable.

--- To execute ---

In folder bin, execute command "./main grapheInstance.txt exerciseNumber" where :
	* "grapheInstance.txt" is a given instance (for example "email.txt")
	* "exerciseNumber" is the number of the desired exercise to execute (see the list of all possible entries in the main function in main.c)
