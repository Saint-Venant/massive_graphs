#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time

#include <stdbool.h>
#include <string.h>

#include "edgelist.h"

//edge list structure:
typedef struct {
	unsigned long n;//number of nodes
	unsigned long e;//number of edges
	edge *edges;//list of edges
	unsigned long *cd;//cumulative degree cd[0]=0 length=n+1
	unsigned long *adj;//concatenated lists of neighbors of all nodes
} adjlist;

adjlist* read_toadjlist(char* input);
void mkadjlist(adjlist* g);
void free_adjlist(adjlist *g);
//inline unsigned long max3(unsigned long a,unsigned long b,unsigned long c);

adjlist* read_toadjlist_clean(char* input, unsigned long* selfLoops);
void sortadjlist(adjlist* g);
void cleanadjlist(adjlist* g, unsigned long* duplicateEdges);
void saveAdjlist(adjlist* g, char* savePath);
