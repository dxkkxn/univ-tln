#include "graph.h"
#include "inout.h"
#include "connexe.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    /*
    graph g;
    g = read_graph(argv[1]);
    printf("ok\n");
    write_graph(NULL, g);
    dessiner_graph(g,"maison");
    return 0;
    */
    graph g = random_graph(10, 0.2);
    int nb_cc = nb_of_components_r(g);
    printf("Nombre des composantes connexes %d\n", nb_cc);
    draw_graph(g, "test");

}

