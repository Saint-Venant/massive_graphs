#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time

#include <stdbool.h>
#include <string.h>

typedef struct {
	unsigned long s;
	unsigned long t;
} edge;

//edge list structure:
typedef struct {
	unsigned long n;//number of nodes
	unsigned long e;//number of edges
	edge *edges;//list of edges
} edgelist;

edgelist* read_toedgelist(char* input);
void free_edgelist(edgelist *g);

FILE* readBeginningFile(char* input);
