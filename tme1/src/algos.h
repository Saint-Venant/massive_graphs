#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time

#include <stdbool.h>
#include <string.h>

#include "adjarray.h"
#include "tools.h"


unsigned long BFS_connected(adjlist* g, bool* mark, unsigned long startVertex);
unsigned int BFS_diameter(adjlist* g, int* mark, unsigned long* currentVertex);

unsigned int countTriangles(adjlist* g);
