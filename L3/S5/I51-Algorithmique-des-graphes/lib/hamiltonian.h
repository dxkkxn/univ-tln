#ifndef HAMILTONIAN_H
#define HAMILTONIAN_H

#include <stdlib.h>
#include <stdbool.h>

#include "graph.h"

void hamiltonian_path(graph g, int vertex, int deep);

int * hamiltonian(graph g);

#endif
