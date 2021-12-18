#include "disjoint.h"
#include "graph.h"
graph detection(graph g) {
  int ordre_g = g.nbs;
  edge_t * edges =  calloc((ordre_g*(ordre_g-1))/2, sizeof(edge_t));;
  size_t nmemb_edge = 0;
  int i,j;
  for (i=0; i < ordre_g; i++) {
    for (j=i+1; j < ordre_g; j++) {
      if (g.mat[i][j]) {
        edges[nmemb_edge].i = i;
        edges[nmemb_edge].j = j;
        edges[nmemb_edge].wt = g.wt[i][j];
        nmemb_edge++;
      }
    }
  }

  disjoint* t = calloc(ordre_g, sizeof(disjoint));

  for (i = 0; i < ordre_g ; i++)
      t[i] = singleton(i);

  disjoint tmp1, tmp2;
  int m = 0;
  edge_t * edges_res = calloc(g.nbs-1, sizeof(edge_t));
  int index = 0;
  int cycle_detected = false
  while (index < nmemb_edge && cycle_detected == false) {
    x = edges[m].i;
    y = edges[m].j;
    if ((tmp1 = rep(t[x])) != (tmp2 = rep(t[y]))) {
        reunion(tmp1, tmp2);
    } else {
      cycle_detected = true;
      *i = x;
      *j = y;
    }
    index++;
  }
  free(edges);
  for (i = 0; i < g.nbs ; i++)
      free(t[i]);
  free(t);
  return cycle_detected;
}
