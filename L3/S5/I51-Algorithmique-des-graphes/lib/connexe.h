#ifndef CONNEXE_H
#define CONNEXE_H
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;
typedef enum {false = 0, true } bool;

int nb_of_components_r(graph g);
uint browse(uint s, graph g);

#endif

