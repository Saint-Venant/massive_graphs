#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time

#include <string.h>

#include "../../struct/edgelist.h"
#include "../../struct/adjarray.h"
#include "../../struct/adjmatrix.h"
#include "../../struct/directedAdjArray.h"

#include "algos.h"


char* concat(char* a, char* b) {
	char* s = malloc((strlen(a) + strlen(b) + 1)*sizeof(char));
	strcpy(s, a);
	strcat(s, b);
	return s;
}

void Exercise1(char* graphPath) {
	time_t t1,t2;
	t1=time(NULL);

	printf("Reading DirectedAdjlist from file %s\n", graphPath);
	DirectedAdjlist* g=read_toDirectedAdjlist(graphPath);

	printf("\nNumber of nodes: %lu\n",g->n);
	printf("Number of edges: %lu\n\n",g->e);

	mkDirectedAdjlist(g);

	float alpha = 0.15;
	double* p = powerIterationPR(g, alpha);

	free(p);
	free_DirectedAdjlist(g);

	t2=time(NULL);
	printf("- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));
}

int main(int argc, char** argv) {
	char* instancesDir = "../../instances_tme2/";
	char* graph = argv[1];
	char* graphPath = concat(instancesDir, graph);
	int exercise = atoi(argv[2]);
	printf("Instances dir : %s\n", instancesDir);
	printf("Graph : %s\n", graph);
	printf("Graph path : %s\n", graphPath);
	printf("Exercise %u\n\n", exercise);

	if (exercise == 1) {
		Exercise1(graphPath);
	}
}
