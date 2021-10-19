#ifndef EULERIEN_H
#define EULERIEN_H
int pre_eulerien(int *s, graph g);
uint neigh_exit(graph g, uint s);
int* balade(graph* g, uint s);
void parcours_eulerien(graph g, uint s, graph* g_copy) ;
void eulerien(graph g);
#endif
