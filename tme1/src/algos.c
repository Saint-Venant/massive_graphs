#include "algos.h"

void fifo_add(unsigned long* fifo, unsigned long elementToAdd, unsigned long* end, unsigned long sizeMax) {
  if (*end < sizeMax) {
    fifo[*end] = elementToAdd;
    *end += 1;
  } else {
    printf("PROBLEM : fifo tries to add element without memory space !\n");
  }
}

unsigned long fifo_pop(unsigned long* fifo, unsigned long* begin, unsigned long* end) {
  if (*begin < *end) {
    *begin += 1;
    return fifo[*begin-1];
  } else {
    printf("PROBLEM : fifo tries to pop whereas empty\n");
    return 0;
  }
}

unsigned long BFS_connected(adjlist* g, bool* mark, unsigned long startVertex) {
  /*
  => Compute the size of the connected component of startVertex

  g : adjlist of the graph
  mark : array to indicate whether a vertex has been marked or not
  */
  unsigned long n = g->n;
  unsigned long* fifo = malloc(n*sizeof(unsigned long));
  unsigned long begin = 0;
  unsigned long end = 0;

  unsigned long size = 0;

  fifo_add(fifo, startVertex, &end, n);
  mark[startVertex] = 1;
  size += 1;

  unsigned long s, v;
  while (begin < end) {
    s = fifo_pop(fifo, &begin, &end);

    for (unsigned long i=g->cd[s]; i<g->cd[s+1]; i++) {
      v = g->adj[i];
      if (mark[v] == 0) {
        fifo_add(fifo, v, &end, n);
        mark[v] = 1;
        size += 1;
      }
    }
  }

  free(fifo);

  return size;
}

unsigned int BFS_diameter(adjlist* g, int* mark, unsigned long* currentVertex) {
  /*
  => Compute the maximum distance from startVertex

  g : adjlist of the graph
  mark : array to indicate whether a vertex has been marked or not
  */
  unsigned long n = g->n;
  unsigned long* fifo = malloc(n*sizeof(unsigned long));
  unsigned long begin = 0;
  unsigned long end = 0;

  unsigned int dist;

  fifo_add(fifo, *currentVertex, &end, n);
  mark[*currentVertex] = 1;

  unsigned long s, v;
  while (begin < end) {
    s = fifo_pop(fifo, &begin, &end);
    dist = mark[s] - 1;
    //printf("mark[s] = %lu\n", mark[s]);

    for (unsigned long i=g->cd[s]; i<g->cd[s+1]; i++) {
      v = g->adj[i];
      if (mark[v] == 0) {
        fifo_add(fifo, v, &end, n);
        mark[v] = mark[s] + 1;
      }
    }
  }

  free(fifo);

  srand(time(NULL));
  *currentVertex = rand()%n;
  while (mark[*currentVertex] < dist + 1) {
    if (*currentVertex < n-1) {
      *currentVertex += 1;
    } else {
      *currentVertex = 0;
    }
  }

  return dist;
}

unsigned int countTriangles(adjlist* g) {
  unsigned int nbTriangles = 0;
  unsigned long u, v, w;

  adjlist* gTr = createTriangleAdjlist(g);

  for (u=0; u<gTr->n; u++) {
    for (unsigned long i=gTr->cd[u]; i<gTr->cd[u+1]; i++) {
      v = gTr->adj[i];
      // u < v by construction of gTr
      for (unsigned long j=gTr->cd[u]; j<gTr->cd[u+1]; j++) {
        w = gTr->adj[j];
        if ((v < w) && (isArc(gTr, v, w))) {
          nbTriangles += 1;
        }
      }
    }
  }

  free(gTr->cd);
  free(gTr->adj);
  free(gTr);

  return nbTriangles;
}
