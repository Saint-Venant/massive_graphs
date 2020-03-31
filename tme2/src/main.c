#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time

#include <string.h>

#include "../../struct/edgelist.h"
#include "../../struct/adjarray.h"
#include "../../struct/adjmatrix.h"
#include "../../struct/directedAdjArray.h"
#include "../../struct/minHeap.h"

#include "algos.h"
#include "pages.h"
#include "tools.h"



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

void Exercise2() {
	char* wikiLinksPath = "../../instances_tme2/Wikipedia-directed-links.txt";
	char* wikiPagesPath = "../../instances_tme2/Wikipedia-pages-names.txt";
	char* outputDir = "../outputEx2/";
	time_t t1,t2;
	t1=time(NULL);

	printf("Reading DirectedAdjlist from file %s\n", wikiLinksPath);
	DirectedAdjlist* g=read_toDirectedAdjlist(wikiLinksPath);

	printf("\nNumber of nodes: %lu\n",g->n);
	printf("Number of edges: %lu\n\n",g->e);

	mkDirectedAdjlist(g);

	float alpha15 = 0.15;
	printf("Running Page Rank with alpha = %f\n", alpha15);
	double* pagerank15 = powerIterationPR(g, alpha15);

	Exercise2_1_2(g, pagerank15, outputDir);

	Exercise2_saveX(g, pagerank15, alpha15, outputDir, "exercise2_save15.txt");
	free(pagerank15);

	float alpha10 = 0.1;
	printf("\nRunning Page Rank with alpha = %f\n", alpha10);
	double* pagerank10 = powerIterationPR(g, alpha10);
	Exercise2_saveX(g, pagerank10, alpha10, outputDir, "exercise2_save10.txt");
	free(pagerank10);

	float alpha20 = 0.2;
	printf("\nRunning Page Rank with alpha = %f\n", alpha20);
	double* pagerank20 = powerIterationPR(g, alpha20);
	Exercise2_saveX(g, pagerank20, alpha20, outputDir, "exercise2_save20.txt");
	free(pagerank20);

	float alpha50 = 0.5;
	printf("\nRunning Page Rank with alpha = %f\n", alpha50);
	double* pagerank50 = powerIterationPR(g, alpha50);
	Exercise2_saveX(g, pagerank50, alpha50, outputDir, "exercise2_save50.txt");
	free(pagerank50);

	float alpha90 = 0.9;
	printf("\nRunning Page Rank with alpha = %f\n", alpha90);
	double* pagerank90 = powerIterationPR(g, alpha90);
	Exercise2_saveX(g, pagerank90, alpha90, outputDir, "exercise2_save90.txt");
	free(pagerank90);

	free_DirectedAdjlist(g);

	t2=time(NULL);
	printf("- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));
}

void Exercise3() {
	testHeap();
}

int main(int argc, char** argv) {
	int exercise = atoi(argv[1]);
	printf("Exercise %u\n\n", exercise);

	if (exercise == 1) {
		Exercise1();
	} else if (exercise == 2) {
		Exercise2();
	} else if (exercise == 3) {
		Exercise3();
	}
}
