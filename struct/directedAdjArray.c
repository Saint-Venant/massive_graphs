#include "directedAdjArray.h"

#define NLINKS 100000000 //maximum number of edges for memory allocation, will increase if needed


//compute the maximum of three unsigned long
inline unsigned long max3(unsigned long a,unsigned long b,unsigned long c){
	a=(a>b) ? a : b;
	return (a>c) ? a : c;
}

DirectedAdjlist* read_toDirectedAdjlist(char* input){
	unsigned long e1=NLINKS;

	FILE* file = readBeginningFile(input);

	DirectedAdjlist *g=malloc(sizeof(DirectedAdjlist));
	g->n=0;
	g->e=0;
	g->edges=malloc(e1*sizeof(edge));//allocate some RAM to store edges

	while (fscanf(file,"%lu %lu", &(g->edges[g->e].s), &(g->edges[g->e].t))==2) {
		g->n=max3(g->n,g->edges[g->e].s,g->edges[g->e].t);
		if (++(g->e)==e1) {//increase allocated RAM if needed
			e1+=NLINKS;
			g->edges=realloc(g->edges,e1*sizeof(edge));
		}
	}
	fclose(file);

	g->n++;

	g->edges=realloc(g->edges,g->e*sizeof(edge));

	return g;
}

void mkDirectedAdjlist(DirectedAdjlist* g){
	unsigned long i,u,v;
	unsigned long *d=calloc(g->n,sizeof(unsigned long)); // degree out !

	for (i=0;i<g->e;i++) {
		d[g->edges[i].s]++;
	}

	g->cd=malloc((g->n+1)*sizeof(unsigned long));
	g->cd[0]=0;
	for (i=1;i<g->n+1;i++) {
		g->cd[i]=g->cd[i-1]+d[i-1];
		d[i-1]=0;
	}

	g->adj=malloc(g->e*sizeof(unsigned long));

	for (i=0;i<g->e;i++) {
		u=g->edges[i].s;
		v=g->edges[i].t;
		g->adj[ g->cd[u] + d[u]++ ]=v;
	}

	free(d);
}

void free_DirectedAdjlist(DirectedAdjlist *g){
	free(g->edges);
	free(g->cd);
	free(g->adj);
	free(g);
}
