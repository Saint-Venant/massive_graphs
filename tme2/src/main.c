#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time

#include <string.h>

#include "../../struct/edgelist.h"
#include "../../struct/adjarray.h"
#include "../../struct/adjmatrix.h"
#include "../../struct/directedAdjArray.h"

#include "algos.h"
#include "pages.h"


char* concat(char* a, char* b) {
	char* s = malloc((strlen(a) + strlen(b) + 1)*sizeof(char));
	strcpy(s, a);
	strcat(s, b);
	return s;
}

void Exercise1() {
	char* wikiLinksPath = "../../instances_tme2/Wikipedia-directed-links.txt";
	char* wikiPagesPath = "../../instances_tme2/Wikipedia-pages-names.txt";
	time_t t1,t2;
	t1=time(NULL);

	printf("Reading DirectedAdjlist from file %s\n", wikiLinksPath);
	DirectedAdjlist* g=read_toDirectedAdjlist(wikiLinksPath);

	printf("\nNumber of nodes: %lu\n",g->n);
	printf("Number of edges: %lu\n\n",g->e);

	mkDirectedAdjlist(g);

	float alpha = 0.15;
	printf("Running Page Rank with alpha = %f\n", alpha);
	double* p = powerIterationPR(g, alpha);
	free_DirectedAdjlist(g);

	printf("\nReading Pages from file %s\n", wikiPagesPath);
	unsigned long nbPages;
	Page* pages = readPages(wikiPagesPath, &nbPages);
	printf(" > Read %lu pages\n\n", nbPages);

	for (unsigned long i=0; i<nbPages; i++) {
		pages[i].pagerank = p[pages[i].id];
	}
	free(p);

	sortPages(pages, nbPages);
	printf(" --- First 5 pages ---\n");
	for (unsigned long i=0; i<10; i++) {
		printf("Page : %s\n", pages[i].name);
		printf(" > PageRank = %.12f\n", pages[i].pagerank);
	}
	printf("\n --- Last 5 pages ---\n");
	for (unsigned long i=10; i>0; i--) {
		printf("Page : %s\n", pages[nbPages-i].name);
		printf(" > PageRank = %.12f\n", pages[nbPages-i].pagerank);
	}
	printf("\n");

	free_pages(pages, nbPages);

	t2=time(NULL);
	printf("- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));
}

int main(int argc, char** argv) {
	//char* instancesDir = "../../instances_tme2/";
	//char* graph = argv[1];
	//char* graphPath = concat(instancesDir, graph);
	int exercise = atoi(argv[1]);
	//printf("Instances dir : %s\n", instancesDir);
	//printf("Graph : %s\n", graph);
	//printf("Graph path : %s\n", graphPath);
	printf("Exercise %u\n\n", exercise);

	if (exercise == 1) {
		Exercise1();
	}
}
