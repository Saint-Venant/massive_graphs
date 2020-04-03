#include "tools.h"



int cmpVertexDegree(const void* a, const void* b) {
  Vertex* u = (Vertex*)a;
  Vertex* v = (Vertex*)b;
  if (u->degree < v->degree) {
    return 1;
  } else if (u->degree > v->degree) {
    return -1;
  }
  return 0;
}

Vertex* createSortedVertices(adjlist* g) {
  /*
  => Given a full adjlist, build a new adjlist where vertices are sorted by descendant degree
  */
  Vertex* vertices = malloc(g->n*sizeof(Vertex));
  for (unsigned long i=0; i<g->n; i++) {
    vertices[i].index = i;
    vertices[i].degree = g->cd[i+1] - g->cd[i];
  }
  qsort(vertices, g->n, sizeof(Vertex), cmpVertexDegree);

  return vertices;
}

unsigned long* createMapIndexVertex(adjlist* g, Vertex* vertices) {
  unsigned long* mapIndexVertex = malloc(g->n*sizeof(unsigned long));
  for (unsigned long i=0; i<g->n; i++) {
    mapIndexVertex[vertices[i].index] = i;
  }
  return mapIndexVertex;
}

adjlist* createTriangleAdjlist(adjlist* g) {
  Vertex* vertices = createSortedVertices(g);
  unsigned long* mapIndexVertex = createMapIndexVertex(g, vertices);
  adjlist* gTr = malloc(sizeof(adjlist));
  gTr->n = g->n;
  gTr->e = 0;
  gTr->cd = malloc((g->n+1)*sizeof(unsigned long));
  gTr->cd[0] = 0;
  gTr->adj = malloc(2*g->e*sizeof(unsigned long));

  unsigned long index_u, index_v;
  unsigned long d;
  unsigned long u, v;
  for (u=0; u<g->n; u++) {
    index_u = vertices[u].index;
    d = 0;
    for (unsigned long j=g->cd[index_u]; j<g->cd[index_u+1]; j++) {
      index_v = g->adj[j];
      v = mapIndexVertex[index_v];
      if (u < v) {
        gTr->adj[gTr->cd[u] + d] = v;
        d += 1;
      }
    }
    gTr->cd[u+1] = gTr->cd[u] + d;
  }
  gTr->adj = realloc(gTr->adj, gTr->cd[gTr->n]*sizeof(unsigned long));

  free(vertices);
  free(mapIndexVertex);

  return gTr;
}

bool isArc(adjlist* g, unsigned long origin, unsigned int destination) {
  for (unsigned long i=g->cd[origin]; i<g->cd[origin+1]; i++) {
    if (g->adj[i] == destination) {
      return true;
    }
  }
  return false;
}
