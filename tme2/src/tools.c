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

void computeCoreDecomposition(adjlist* g, unsigned long* coreValue, unsigned long* coreValues, unsigned long* coreOrdering) {
	unsigned long i, j, k;
	Vertex* v;

	printf("Creating vertices\n");
	Vertex** vertices = malloc(g->n*sizeof(Vertex*));
	for (i=0; i<g->n; i++) {
		vertices[i] = malloc(sizeof(Vertex));
		vertices[i]->index = i;
		vertices[i]->degree = g->cd[i+1] - g->cd[i];
		vertices[i]->inserted = 0;
	}

	printf("\nBuilding MinHeap\n");
	MinHeap* h = createMinHeap(g->n);
	for (i=0; i<g->n; i++) {
		insert(h, vertices[i]);
	}

	printf("\nComputing core value\n");
	k = g->n;
	*coreValue = 0;
	while (h->count > 0) {
		v = popMin(h);
		*coreValue = (v->degree > *coreValue) ? v->degree : *coreValue;
		coreValues[v->index] = *coreValue;
		for (i=g->cd[v->index]; i<g->cd[v->index + 1]; i++) {
			j = g->adj[i];
			if (vertices[j]->inserted) {
				decrementAndUpdate(h, vertices[j]);
			}
		}
		coreOrdering[v->index] = k;
		k--;
	}

	free_MinHeap(h);
	free_vertices(vertices, g->n);
}

void saveResultEx4(adjlist* g, unsigned long* coreValues, char* outputPath) {
	FILE* file = fopen(outputPath, "w");
	fprintf(file, "# 'Author ID' 'Core value' 'Degree'\n");
	for (unsigned long i=0; i<g->n; i++) {
		fprintf(file, "%lu %lu %lu\n", i, coreValues[i], g->cd[i+1] - g->cd[i]);
	}
	fclose(file);
}
