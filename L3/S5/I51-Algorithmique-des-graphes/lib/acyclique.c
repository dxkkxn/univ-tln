#include "acyclique.h"
#define true 1
#define false 0

int * track;
int cycle_detected;

void browse(uint s, graph g) {
    track[s] = true;
    for (int t = 0; t < g.nbs && cycle_detected == false; t++) {
        if(g.mat[s][t]) {
            if (track[t] == true) {
                cycle_detected = true;
            } else {
                track[t] = true;
            }
            g.mat[s][t] = g.mat[t][s] = 0;
            browse(t, g);
        }
    }
}

int acyclique(graph g) {
    graph copy_g = copy_graph(g);
    cycle_detected = false;
    track = calloc(g.nbs, sizeof(uint));
    for (int i = 0; i < g.nbs && cycle_detected == false; i++) {
        if (degree(copy_g, i)) {
            browse(i, copy_g);
        }
    }
    return !cycle_detected;
}
