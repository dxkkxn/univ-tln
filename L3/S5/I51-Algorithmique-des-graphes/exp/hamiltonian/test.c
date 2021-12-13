#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hamiltonian.h"
#include "inout.h"
int main(int argc, char* argv[]) {
    assert(argc==3);
    graph g = random_graph(atoi(argv[1]), atof(argv[2]));
    draw_graph(g, "test");
    hamiltonian(g);
    free_graph(g);
}
