#include "graph.h"
#include "connexe.h"

int * track;
int nb_of_components_r(graph g) {
    track = calloc(g.nbs, sizeof(int));
    int nbc = 0, comp_max = 0, max = 0;

    for(uint s = 0; s < g.nbs; s++) {
        if (track[s] == false) {
            comp_max = browse(s, g);
            nbc += 1;
            if (comp_max > max) 
                max = comp_max;
            comp_max = 0;
        }
    }
    free(track);
    printf("comp max = %d\n", max);
    return nbc;
}

uint browse(uint s, graph g) {
    track[s] = true;
    uint temp = 1;
    for (int t = 0; t < g.nbs; t++) {
        if(g.mat[s][t] && track[t] == false) {
            temp += browse(t, g);
        }
    }
    return temp;
}




