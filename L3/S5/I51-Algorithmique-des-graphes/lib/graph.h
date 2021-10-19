#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
typedef unsigned int uint;
typedef struct {
    int nbs;
    int **mat;
} graph;

graph create_graph(int n);
void free_graph(graph g);
graph random_graph(int n, float p);
uint degree(graph g, uint s);
graph copy_graph(graph g);
void print_mat(graph g);
#endif
