/*
Maximilien Danisch
September 2017
http://bit.ly/danisch
maximilien.danisch@gmail.com

Info:
Feel free to use these lines as you wish. This program loads a graph in main memory as a list of edges.

To compile:
"gcc edgelist.c -O9 -o edgelist".

To execute:
"./edgelist edgelist.txt".
"edgelist.txt" should contain the graph: one edge on each line (two unsigned long (nodes' ID)) separated by a space.
The prograph loads the graph in main memory and then it terminates.

Note:
If the graph is directed (and weighted) with selfloops and you want to make it undirected unweighted without selfloops, use the following linux command line.
awk '{if ($1<$2) print $1" "$2;else if ($2<$1) print $2" "$1}' net.txt | sort -n -k1,2 -u > net2.txt

Performance:
Up to 500 million edges on my laptop with 8G of RAM:
Takes more or less 1.6G of RAM and 25 seconds (I have an SSD hardrive) for 100M edges.
*/

#include "edgelist.h"

#define NLINKS 100000000 //maximum number of edges for memory allocation, will increase if needed

//compute the maximum of three unsigned long
inline unsigned long max3(unsigned long a,unsigned long b,unsigned long c){
	a=(a>b) ? a : b;
	return (a>c) ? a : c;
}

FILE* readBeginningFile(char* input) {
	FILE* file=fopen(input,"r");

	// read the number of '#'
	int nbDash = 0;
	char line[255];
	char dash[1] = "#";
	char eol[1] = "\n";
	char* output;
	while (true) {
		output = fgets(line, 255, file);
		if (dash[0] == line[0]) {
			nbDash += 1;
		} else {
			break;
		}
		while (line[strlen(line) - 1] != eol[0]) {
			output = fgets(line, 255, file);
		}
	}
	fclose(file);

	file = fopen(input,"r");
	for (int k=0; k<nbDash; k++) {
		output = fgets(line, 255, file);
		while (line[strlen(line) - 1] != eol[0]) {
			output = fgets(line, 255, file);
		}
	}

	return file;
}

//reading the edgelist from file
edgelist* read_toedgelist(char* input){
	unsigned long e1=NLINKS;

	FILE* file = readBeginningFile(input);

	edgelist *g=malloc(sizeof(edgelist));
	g->n=0;
	g->e=0;
	g->edges=malloc(e1*sizeof(edge));//allocate some RAM to store edges

	while (fscanf(file,"%lu %lu", &(g->edges[g->e].s), &(g->edges[g->e].t))==2) {
		g->n=max3(g->n,g->edges[g->e].s,g->edges[g->e].t);
		if (++(g->e)==e1) {//increase allocated RAM if needed
			e1+=NLINKS;
			g->edges=realloc(g->edges,e1*sizeof(edge));
		}
	}
	fclose(file);

	g->n++;

	g->edges=realloc(g->edges,g->e*sizeof(edge));

	return g;
}

void free_edgelist(edgelist *g){
	free(g->edges);
	free(g);
}
