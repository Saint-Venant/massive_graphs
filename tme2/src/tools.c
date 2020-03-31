#include "tools.h"


char* concat(char* a, char* b) {
	char* s = malloc((strlen(a) + strlen(b) + 1)*sizeof(char));
	strcpy(s, a);
	strcat(s, b);
	return s;
}

void computeDegree(DirectedAdjlist* g, unsigned long* degreeIN, unsigned long* degreeOUT) {
  unsigned long i, u, v;

  for (i=0; i<g->n; i++) {
    degreeIN[i] = 0;
    degreeOUT[i] = 0;
  }

  for (i=0; i<g->e; i++) {
    u = g->edges[i].s;
    v = g->edges[i].t;
    degreeIN[v] += 1;
    degreeOUT[u] += 1;
  }
}

void Exercise2_1_2(DirectedAdjlist* g, double* pagerank15, char* outputDir) {
  char* outputName = "exercise2_1_2.txt";
  char* outputPath = concat(outputDir, outputName);

  unsigned long* degreeIN = malloc(g->n*sizeof(unsigned long));
	unsigned long* degreeOUT = malloc(g->n*sizeof(unsigned long));
	printf("\nComputing degrees in and out\n");
	computeDegree(g, degreeIN, degreeOUT);

  FILE* file = fopen(outputPath, "w");
  fprintf(file, "#'Page ID' 'PageRank (alpha = 0.15)' 'Degree IN' 'Degree OUT'\n");
  for (unsigned long i=0; i<g->n; i++) {
    fprintf(file, "%lu %.15f %lu %lu\n", i, pagerank15[i], degreeIN[i], degreeOUT[i]);
  }
  fclose(file);

  free(degreeIN);
	free(degreeOUT);
}

void Exercise2_saveX(DirectedAdjlist* g, double* pagerankAlpha, float alpha, char* outputDir, char* outputName) {
	char* outputPath = concat(outputDir, outputName);

	FILE* file = fopen(outputPath, "w");
  fprintf(file, "#'Page ID' 'PageRank (alpha = %.2f)'\n", alpha);
  for (unsigned long i=0; i<g->n; i++) {
    fprintf(file, "%lu %.15f\n", i, pagerankAlpha[i]);
  }
  fclose(file);
}
