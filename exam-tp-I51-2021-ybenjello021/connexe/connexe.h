#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "graph.h"
#include "list.h"

int nb_of_components(graph g) ;
void simple_browse(int s, graph g);
list_t browse(uint s, graph g) ;
list_t * stats_search(graph g, int n_comp);
int edges_component(graph g,list_t sommets);
void stats(graph g) ;
int edges_graph(list_t * sommets, int p);
int cycle(graph g);
