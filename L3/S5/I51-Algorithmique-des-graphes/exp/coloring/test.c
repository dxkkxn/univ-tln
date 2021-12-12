/* #include "graph.h" */
/* #include "inout.h" */
/* #include "coloring.h" */
/* int main(int argc, char* argv[]) { */
/*     graph g; */
/*     g = read_graph(argv[1]); */
/*     print_mat(g); */
/*     printf("nb_solutions 5 coloreables %d",n_colorable(g, 5)); */
/*     free_graph(g); */
/*     return 0; */
/* } */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "coloring.h"
#include "inout.h"

int main(int argc, char* argv[]) {
    assert(argc==3);
    srand(time(NULL));
    graph g = random_graph(atoi(argv[1]), atof(argv[2]));
    draw_graph(g, "test");
    if (bicolore(g)) {
        printf("bicolore\n");
    } else {
        printf("pas  bicolore\n");
    }
}
