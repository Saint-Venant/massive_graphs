#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time

#include <string.h>

#include "edgelist.h"
#include "adjarray.h"
#include "adjmatrix.h"


char* concat(char* a, char* b) {
	char* s = malloc((strlen(a) + strlen(b) + 1)*sizeof(char));
	strcpy(s, a);
	strcat(s, b);
	return s;
}

void Exercise2(char* graphPath) {
	time_t t1,t2;
	t1=time(NULL);

	printf("Reading edgelist from file %s\n", graphPath);
	adjlist* g=read_toadjlist(graphPath);

	printf("\nNumber of nodes: %lu\n",g->n);
	printf("Number of edges: %lu\n\n",g->e);

	free(g->edges);
	free(g);

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

	if (exercise == 2) {
		Exercise2(graphPath);
	} else if (exercise == 3) {
		Exercise3(instancesDir, graph);
	} else if (exercise == 4) {
		printf("> Please choose between exercises : 4.1 ('41'); 4.2 ('42'); 4.3 ('4.3')\n");
	} else if (exercise == 41) {
		Exercise4_1(instancesDir, graph);
	} else if (exercise == 42) {
		Exercise4_2(instancesDir, graph);
	} else if (exercise == 43) {
		Exercise4_3(instancesDir, graph);
	} else if (exercise == 5) {
		Exercise5(instancesDir, graph);
	} else if (exercise == 6) {
		Exercise6(instancesDir, graph);
	}
}
