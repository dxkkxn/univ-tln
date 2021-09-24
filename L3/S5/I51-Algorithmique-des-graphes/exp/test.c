#include "graph.h"
#include "inout.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    graph g;
    g = read_graph(argv[1]);
    printf("ok\n");
    write_graph(NULL, g);
    dessiner_graph(g,"maison");
    return 0;
}

