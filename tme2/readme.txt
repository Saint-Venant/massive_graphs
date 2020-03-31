--- Structure of the folder ---

bin/					// will contain the executable
src/
	main.c
	
	algos.h
	algos.c
	pages.h
	pages.c
	tools.h
	tools.c
outputEx2/				// will contain the output files of exercise 2
tme2.pdf


--- To compile ---

In folder /src/, execute command
	"gcc main.c
		../../struct/adjarray.c
		../../struct/adjmatrix.c
		../../struct/edgelist.c
		../../struct/directedAdjArray.c
		../../struct/minHeap.c
		algos.c
		pages.c
		tools.c
	-O9 -o ../bin/main"
where "main" will be the name of the executable.

--- To execute ---
In folder bin, execute command "./main grapheInstance.txt exerciseNumber" where :
* "grapheInstance.txt" is a given instance
* "exerciseNumber" is the number of the desired exercise to execute
