#include "algos.h"

double* powerIterationPR(DirectedAdjlist* g, float alpha) {
  double* p1 = malloc(g->n*sizeof(double));
  double* p2 = malloc(g->n*sizeof(double));
  unsigned int i, u, v, d_u;
  double epsilon = pow(10, -12);
  double q, pnorm, x, diff, maxDiff;

  // initialize p1 and p2
  for (u=0; u<g->n; u++) {
    p1[u] = 1. / (double)g->n;
    p2[u] = 0.;
  }

  maxDiff = 0;
  diff = 1;
  unsigned int iterations = 0;
  while (diff > maxDiff*pow(10, -9)) {
    for (i=0; i<g->e; i++) {
      u = g->edges[i].s;
      v = g->edges[i].t;
      d_u = g->cd[u+1] - g->cd[u];
      p2[v] += p1[u] / (double)d_u;
    }

    q = 0;
    for (u=0; u<g->n; u++) {
      d_u = g->cd[u+1] - g->cd[u];
      if (d_u < epsilon) {
        q += p1[u];
      }
    }

    pnorm = 0;
    for (u=0; u<g->n; u++) {
      p2[u] += q / (double)g->n;
      p2[u] *= (1-alpha);
      p2[u] += alpha;
      pnorm += p2[u];
    }

    // normalize
    diff = 0;
    for (u=0; u<g->n; u++) {
      x = p2[u] + (1 - pnorm) / (double)g->n;
      diff += pow(p1[u] - x, 2);
      p1[u] = x;
      p2[u] = 0;
    }

    iterations += 1;
    maxDiff = (diff > maxDiff) ? diff : maxDiff;
    //printf("diff = %f * 10e-12\n", diff*pow(10, 12));
  }

  printf("Computed Page Rank in %u iterations\n", iterations);

  free(p2);
  return p1;
}
