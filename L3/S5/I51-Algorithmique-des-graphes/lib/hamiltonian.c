#include "hamiltonian.h"

int * track;
int * path;
void hamiltonian_path(graph g, int vertex, int deep) {
    if (deep == g.nbs-1) {
        track[vertex] = true;
        path[deep] = vertex;
        for (int  i = 0; i < g.nbs; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
        return;
    }
    for (int i = 0; i < g.nbs; i++) {
        if (g.mat[vertex][i] && track[i] == false) {
            track[vertex] = true;
            path[deep] = vertex;
            hamiltonian_path(g, i, deep+1);
            path[deep] = 0;
            track[vertex] = false;
        }
    }
}

int * hamiltonian(graph g) {
    track = calloc(g.nbs, sizeof(int));
    path = calloc(g.nbs, sizeof(int));
    hamiltonian_path(g, 0, 0);
    return path;
}
