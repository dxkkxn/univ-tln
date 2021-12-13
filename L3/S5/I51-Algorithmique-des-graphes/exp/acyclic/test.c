#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "acyclique.h"
#include "inout.h"

int main(int argc, char* argv[]) {
    assert(argc==3);
    srand(time(NULL));
    graph g = random_graph(atoi(argv[1]), atof(argv[2]));
    draw_graph(g, "test");
    if (acyclique(g)) {
        printf("acyclique\n");
    } else {
        printf("cyclique\n");
    }
}

