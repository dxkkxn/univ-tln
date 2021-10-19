#include "graph.h"
#include <stdlib.h>
#define true 1
#define false 0

graph create_graph(int n) {
    graph res; int i;
    res.nbs = n;
    res.mat = calloc(n, sizeof(int *));
    for(i = 0; i < n; i++)
        res.mat[i] = calloc(n,sizeof(int));
    return res;
}

graph copy_graph(graph g) {
  graph res = create_graph(g.nbs);
  for(uint i = 0; i < g.nbs; i++) {
    for(uint j = (i+1); j < g.nbs; j++) {
      res.mat[i][j] = res.mat[j][i] = g.mat[i][j];
    }
  }
  return res;
}
void free_graph(graph g) {
    for (int i = 0; i < g.nbs; i++)
        free(g.mat[i]);
    free(g.mat);
}

graph random_graph(int n, float p) {
    graph res = create_graph(n);
    double threshold = p*RAND_MAX;
    for(int i = 0; i < n; i++) {
        for (int j = (i+1); j < n; j++) {
            if (random() < threshold)
                res.mat[i][j] = res.mat[j][i] = 1;

        }
    }
    return res;
}

uint degree(graph g, uint s) {
    uint res = 0;
    for(int i = 0; i < g.nbs; i++) {
        if (g.mat[s][i] == true)
            res++;
    }
    return res;
}
