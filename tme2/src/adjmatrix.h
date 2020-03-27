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
	bool *mat;//adjacency matrix
} adjmatrix;

adjmatrix* read_toadjmatrix(char* input);
bool mkmatrix(adjmatrix* g);
void free_adjmatrix(adjmatrix *g);
