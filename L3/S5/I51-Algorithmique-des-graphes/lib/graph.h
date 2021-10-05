#ifndef GRAPH_H
#define GRAPH_H
typedef struct {
    int nbs;
    int **mat;
} graph;

graph create_graph(int n);
void free_graph(graph g);
graph random_graph(int n, float p);

#endif
