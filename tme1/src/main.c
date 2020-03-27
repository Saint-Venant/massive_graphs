#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time

#include <string.h>

#include "edgelist.h"
#include "adjarray.h"
#include "adjmatrix.h"
#include "algos.h"



int main_adjarray(int argc,char** argv){
	adjlist* g;
	time_t t1,t2;

	t1=time(NULL);

	printf("Reading edgelist from file %s\n",argv[1]);
	g=read_toadjlist(argv[1]);

	printf("Number of nodes: %lu\n",g->n);
	printf("Number of edges: %lu\n",g->e);

	printf("Building the adjacency list\n");
	mkadjlist(g);

	free_adjlist(g);

	t2=time(NULL);

	printf("- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));

	return 0;
}

int main_edgelist(int argc,char** argv){
	edgelist* g;
	time_t t1,t2;

	t1=time(NULL);

	printf("Reading edgelist from file %s\n",argv[1]);
	g=read_toedgelist(argv[1]);

	printf("Number of nodes: %lu\n",g->n);
	printf("Number of edges: %lu\n",g->e);

	free_edgelist(g);

	t2=time(NULL);

	printf("- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));

	return 0;
}

int main_adjmatrix(int argc,char** argv){
	adjmatrix* g;
	time_t t1,t2;

	t1=time(NULL);

	printf("Reading edgelist from file %s\n",argv[1]);
	g=read_toadjmatrix(argv[1]);

	printf("Number of nodes: %lu\n",g->n);
	printf("Number of edges: %lu\n",g->e);

	printf("Building the adjacency matrix\n");
	bool ok = mkmatrix(g);

	free_adjmatrix(g);

	t2=time(NULL);

	printf("- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));

	return 0;
}

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

void Exercise3(char* instancesDir, char* graph) {
	time_t t1,t2;
	t1=time(NULL);

	char* graphPath = concat(instancesDir, graph);
	printf("Reading edgelist from file %s\n", graphPath);
	adjlist* g = read_toadjlist_clean(graphPath);
	// At this stage, g:
	// - does not contain any edge of the form (u, u)
	// - only contains edges of the form (u, v) where u<v
	printf("\nNumber of nodes: %lu\n",g->n);
	printf("Number of edges: %lu\n\n",g->e);

	printf("Building the adjacency list\n");
	mkadjlist(g);

	printf("Sorting the adjacency list\n");
	sortadjlist(g);

	printf("Cleaning the adjacency list\n");
	cleanadjlist(g);

	printf("\nNumber of nodes: %lu\n",g->n);
	printf("Number of edges: %lu\n\n",g->e);

	char* pref = "clean_";
	char* cleanGraph = concat(pref, graph);
	char* cleanGraphPath = concat(instancesDir, cleanGraph);
	printf("clean graph path : %s\n", cleanGraphPath);
	saveAdjlist(g, cleanGraphPath);

	free_adjlist(g);

	t2=time(NULL);
	printf("- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));
}

void Exercise4_1(char* instancesDir, char* graph) {
	time_t t1,t2;
	t1=time(NULL);

	char* graphPath = concat(instancesDir, graph);

	printf("Load the list of edges\n");
	edgelist* g = read_toedgelist(graphPath);

	printf("Number of nodes: %lu\n",g->n);
	printf("Number of edges: %lu\n",g->e);

	free_edgelist(g);

	t2=time(NULL);

	printf("- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));
}

void Exercise4_2(char* instancesDir, char* graph) {
	time_t t1,t2;
	t1=time(NULL);

	char* graphPath = concat(instancesDir, graph);

	printf("Load the adjacency matrix\n");
	adjmatrix* g = read_toadjmatrix(graphPath);

	printf("Number of nodes: %lu\n",g->n);
	printf("Number of edges: %lu\n",g->e);

	printf("Building the adjacency matrix\n");
	bool ok = mkmatrix(g);

	free_adjmatrix(g);

	if (ok) {
		t2=time(NULL);
		printf("- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));
	}
}

void Exercise4_3(char* instancesDir, char* graph) {
	adjlist* g;
	time_t t1,t2;

	t1=time(NULL);
	char* graphPath = concat(instancesDir, graph);

	printf("Reading adjlist from file %s\n",graphPath);
	g=read_toadjlist(graphPath);

	printf("Number of nodes: %lu\n",g->n);
	printf("Number of edges: %lu\n",g->e);

	printf("Building the adjacency list\n");
	mkadjlist(g);

	free_adjlist(g);

	t2=time(NULL);

	printf("- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));
}

void Exercise5(char* instancesDir, char* graph) {
	adjlist* g;
	time_t t1,t2;

	t1=time(NULL);
	char* graphPath = concat(instancesDir, graph);

	printf("Reading adjlist from file %s\n",graphPath);
	g=read_toadjlist(graphPath);
	mkadjlist(g);

	bool* mark = calloc(g->n, sizeof(bool));
	unsigned long startVertex = 0;
	unsigned long size;
	unsigned long sizeMax = 0;
	printf("Running BFS to detect connected components (print only components of size > 1)\n");
	while (startVertex < g->n) {
		//printf("Running BFS from starting vertex : %lu\n", startVertex);
		size = BFS_connected(g, mark, startVertex);
		if (size > 1) {
			printf("  > component of size %lu\n", size);
		}
		if (size > sizeMax) {
			sizeMax = size;
		}
		while ((startVertex < g->n) && (mark[startVertex] == 1)) {
			startVertex += 1;
		}
	}

	double frac = (double)sizeMax / (double)g->n;
	printf("\nFraction of nodes in the largest connected component : %f\n\n", frac);
	free(mark);

	// ### diameter ###

	int* markDist = calloc(g->n, sizeof(int));
	bool* start = calloc(g->n, sizeof(unsigned long));
	unsigned long currentVertex = 0;
	unsigned int dist;
	unsigned int maxDist = 0;
	unsigned int k;
	unsigned int kMax = (100 < g->n) ? 100 : g->n;
	unsigned int notImproved = 0;

	for (k=0; k<kMax; k++) {
		while (start[currentVertex] == 1) {
			currentVertex = (currentVertex + 1)%g->n;
		}
		start[currentVertex] = 1;
		dist = BFS_diameter(g, markDist, &currentVertex);
		if (dist > maxDist) {
			maxDist = dist;
			notImproved = 0;
		} else {
			notImproved += 1;
		}
		if (notImproved > 10) {
			break;
		}
		for (unsigned long i=0; i<g->n; i++) {
			markDist[i] = 0;
		}
	}

	printf("Lower bound of diameter : %u (found in %u iterations of BFS)\n", maxDist, k);

	free(markDist);
	free(start);
	free_adjlist(g);

	t2=time(NULL);

	printf("- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));
}

void Exercise6(char* instancesDir, char* graph) {
	adjlist* g;
	time_t t1,t2;

	t1=time(NULL);
	char* graphPath = concat(instancesDir, graph);

	printf("Reading adjlist from file %s\n",graphPath);
	g=read_toadjlist(graphPath);
	mkadjlist(g);

	unsigned int nbTriangles = countTriangles(g);
	printf("Found %u triangles \n", nbTriangles);

	free_adjlist(g);

	t2=time(NULL);

	printf("- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));
}

int main(int argc, char** argv) {
	char* instancesDir = "../../instances_tme1/";
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
