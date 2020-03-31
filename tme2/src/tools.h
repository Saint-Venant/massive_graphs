#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time

#include <string.h>

#include "../../struct/adjarray.h"
#include "../../struct/directedAdjArray.h"
#include "../../struct/minHeap.h"


char* concat(char* a, char* b);

void Exercise2_1_2(DirectedAdjlist* g, double* pagerank15, char* outputDir);
void Exercise2_saveX(DirectedAdjlist* g, double* pagerankAlpha, float alpha, char* outputDir, char* outputName);

void computeCoreDecomposition(adjlist* g, unsigned long* coreValue, unsigned long* coreValues, unsigned long* coreOrdering);
void saveResultEx4(adjlist* g, unsigned long* coreValues, char* outputPath);
