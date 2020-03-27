#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time

#include <stdbool.h>
#include <string.h>

#include "adjarray.h"

typedef struct {
  unsigned long index; // index of the vertex
  unsigned int degree; // degree (non oriented)
} Vertex;

adjlist* createTriangleAdjlist(adjlist* g);
bool isArc(adjlist* g, unsigned long origin, unsigned int destination);
