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
	unsigned long *cd;//cumulative degree cd[0]=0 length=n+1 # degree out !!#
	unsigned long *adj;//concatenated lists of neighbors of all nodes
} DirectedAdjlist;

DirectedAdjlist* read_toDirectedAdjlist(char* input);
void mkDirectedAdjlist(DirectedAdjlist* g);
void free_DirectedAdjlist(DirectedAdjlist *g);
