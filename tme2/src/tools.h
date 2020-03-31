#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time

#include <string.h>

#include "../../struct/directedAdjArray.h"


char* concat(char* a, char* b);

void Exercise2_1_2(DirectedAdjlist* g, double* pagerank15, char* outputDir);
void Exercise2_saveX(DirectedAdjlist* g, double* pagerankAlpha, float alpha, char* outputDir, char* outputName);
