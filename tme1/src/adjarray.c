/*
Maximilien Danisch
September 2017
http://bit.ly/danisch
maximilien.danisch@gmail.com

Info:
Feel free to use these lines as you wish. This program loads a graph in main memory.

To compile:
"gcc adjlist.c -O9 -o adjlist".

To execute:
"./adjlist edgelist.txt".
"edgelist.txt" should contain the graph: one edge on each line (two unsigned long (nodes' ID)) separated by a space.
The prograph will load the graph in main memory and then terminate.

Note:
If the graph is directed (and weighted) with selfloops and you want to make it undirected unweighted without selfloops, use the following linux command line.
awk '{if ($1<$2) print $1" "$2;else if ($2<$1) print $2" "$1}' net.txt | sort -n -k1,2 -u > net2.txt

Performance:
Up to 200 million edges on my laptop with 8G of RAM: takes more or less 4G of RAM and 30 seconds (I have an SSD hardrive) for 100M edges.
*/

#include "adjarray.h"

#define NLINKS 100000000 //maximum number of edges for memory allocation, will increase if needed


//compute the maximum of three unsigned long
inline unsigned long max3(unsigned long a,unsigned long b,unsigned long c){
	a=(a>b) ? a : b;
	return (a>c) ? a : c;
}

//reading the edgelist from file
adjlist* read_toadjlist(char* input){
	unsigned long e1=NLINKS;

	FILE* file = readBeginningFile(input);

	adjlist *g=malloc(sizeof(adjlist));
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

adjlist* read_toadjlist_clean(char* input) {
	unsigned long u,v;
	unsigned long e1=NLINKS;

	FILE* file = readBeginningFile(input);

	adjlist *g=malloc(sizeof(adjlist));
	g->n=0;
	g->e=0;
	g->edges=malloc(e1*sizeof(edge));//allocate some RAM to store edges

	while (fscanf(file,"%lu %lu", &u, &v)==2) {
		if (u < v) {
			g->edges[g->e].s = u;
			g->edges[g->e].t = v;
		} else if (v < u){
			g->edges[g->e].s = v;
			g->edges[g->e].t = u;
		} else {
			continue;
		}
		g->n=max3(g->n, u, v);
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

//building the adjacency matrix
void mkadjlist(adjlist* g){
	unsigned long i,u,v;
	unsigned long *d=calloc(g->n,sizeof(unsigned long));

	for (i=0;i<g->e;i++) {
		d[g->edges[i].s]++;
		d[g->edges[i].t]++;
	}

	g->cd=malloc((g->n+1)*sizeof(unsigned long));
	g->cd[0]=0;
	for (i=1;i<g->n+1;i++) {
		g->cd[i]=g->cd[i-1]+d[i-1];
		d[i-1]=0;
	}

	g->adj=malloc(2*g->e*sizeof(unsigned long));

	for (i=0;i<g->e;i++) {
		u=g->edges[i].s;
		v=g->edges[i].t;
		g->adj[ g->cd[u] + d[u]++ ]=v;
		g->adj[ g->cd[v] + d[v]++ ]=u;
	}

	free(d);
	//free(g->edges);
}

int cmpfunc(const void* a, const void* b) {
	unsigned long* x = (unsigned long*) a;
	unsigned long* y = (unsigned long*) b;
	if (*x < *y) {
		return -1;
	} else if (*x > *y) {
		return 1;
	}
	return 0;
}

void sortadjlist(adjlist* g) {
	unsigned long nbNeighbors;
	for (unsigned long i=0; i<g->n; i++) {
		nbNeighbors = g->cd[i+1]-g->cd[i];
		qsort(&(g->adj[g->cd[i]]), nbNeighbors, sizeof(g->adj), cmpfunc);
	}
}

void cleanadjlist(adjlist* g) {
	unsigned long* cd = calloc((g->n+1), sizeof(unsigned long));
	unsigned long* adj = malloc(2*g->e*sizeof(unsigned long));
	unsigned long u,v;
	unsigned long neigh;
	for (u=0; u<g->n; u++) {
		neigh = g->cd[u+1] - g->cd[u];
		if (neigh == 0) {
			cd[u+1] = cd[u];
			continue;
		}
		v = g->adj[g->cd[u]];
		adj[cd[u]] = v;
		cd[u+1] = cd[u] + 1;
		for (unsigned long j=1; j<neigh; j++) {
			if (g->adj[g->cd[u] + j] > v) {
				v = g->adj[g->cd[u] + j];
				adj[cd[u+1]] = v;
				cd[u+1] += 1;
			}
		}
	}
	adj = realloc(adj,cd[g->n]*sizeof(unsigned long));

	unsigned long e1=NLINKS;
	edge* edges = malloc(e1*sizeof(edge));//allocate some RAM to store edges
	unsigned long e = 0;
	for (u=0; u<g->n; u++) {
		for (unsigned long j=cd[u]; j<cd[u+1]; j++) {
			v = adj[j];
			//printf(" %lu", v);
			if (u < v) {
				edges[e].s = u;
				edges[e].t = v;
				e += 1;
				if (e == e1) {//increase allocated RAM if needed
					e1+=NLINKS;
					edges = realloc(edges,e1*sizeof(edge));
				}
			}
		}
	}
	edges = realloc(edges,e*sizeof(edge));

	g->e = e;
	free(g->edges);
	g->edges = edges;
	free(g->cd);
	g->cd = cd;
	free(g->adj);
	g->adj = adj;
}


//freeing memory
void free_adjlist(adjlist *g){
	free(g->edges);
	free(g->cd);
	free(g->adj);
	free(g);
}

void saveAdjlist(adjlist* g, char* savePath) {
	FILE* file = fopen(savePath, "w");
	for (unsigned long i=0; i<g->e; i++) {
		fprintf(file, "%lu %lu\n", g->edges[i].s, g->edges[i].t);
	}
	fclose(file);
}
