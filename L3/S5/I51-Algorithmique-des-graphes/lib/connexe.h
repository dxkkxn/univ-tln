#ifndef CONNEXE_H
#define CONNEXE_H
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;
typedef enum {false = 0, true = 1} bool;

uint nb_of_components_r(graph g);
uint browse(uint s, graph g);
uint max_component(graph g);
uint nb_of_components_it(graph g);

#endif

