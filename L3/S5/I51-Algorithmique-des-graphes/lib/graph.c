#include "graph.h"
#include <stdlib.h>

graph create_graph(int n) {
    graph res; int i; 
    res.nbs = n;
    res.mat = calloc(n, sizeof(int *));
    for(i = 0; i < n; i++) 
        res.mat[i] = calloc(n,sizeof(int));
    return res;
}

void free_graph(graph g) {
    for (int i = 0; i < g.nbs; i++) 
        free(g.mat[i]);
    free(g.mat);
}

