#include "kruskal.h"

int comp_edge(const void * p1, const void * p2) {
  return ((edge_t *)p1)->wt -((edge_t *)p2)->wt;
}

edge_t* kruskal(graph g) {
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
  edges = realloc(edges, nmemb_edge);
  qsort(edges, nmemb_edge, sizeof(edge_t), comp_edge);
  disjoint* t = calloc(ordre_g, sizeof(disjoint));
  for (i = 0; i < ordre_g ; i++)
      t[i] = singleton(i);

  disjoint tmp1, tmp2;
  int m = 0;
  int x, y;
  while (ordre_g > 1) {
    x = edges[m].i;
    y = edges[m].j;
    if ((tmp1 = rep(t[x])) != (tmp2 = rep(t[y]))) {
        reunion(tmp1, tmp2);
        ordre_g--;
    }
    m++;
  }
  return 0;
}
