#include "graph.h"
#include "eulerien.h"
#include <stdlib.h>
#include <stdio.h>

int pre_eulerien(int *s, graph g) {
    // return 0 not eulerien
    // return 1 eulerien
    // return 2 semi-eulerien
    uint nb_odds = 0;
    uint res;
    uint last_odds;
    for(int i = 0; i < g.nbs; i++) {
        if (degree(g,i) % 2 != 0) {
            // deg(i) odd
            nb_odds++;
            last_odds = i;
        }
    }
    if (nb_odds == 2) {
        //semi-eulerien
        res = 2;
        (*s) = last_odds;
    } else if (nb_odds == 0) {
        res = 1;
        (*s) = 0;
    } else {
        res = 0;
    }
    return res;
}

uint neigh_exist(graph g, uint s) {
    // return 0 if there arent neighbours
    // return x | x is a neighbour of s
    uint res = 0;
    for(uint i = 0; i < g.nbs && res == 0; i++) {
        if(g.mat[s][i] == 1)
            res = i;
    }
    printf("%d\n", res);
    return res;
}

int* balade(graph* g, uint s) {
    int n = (g->nbs * g->nbs)/2;
    int * track = calloc(n, sizeof(int));
    int i;
    for(i = 0; i<n; i++)
        track[i] = -1;
    uint neigh;
    uint curr_s = s;
    track[0] = curr_s;
    i = 1;
    while(neigh = neigh_exist((*g), curr_s)) {
        track[i] = neigh;
        g->mat[curr_s][neigh] = g->mat[neigh][curr_s] = 0;
        printf("%d->%d\n", curr_s, neigh);
        curr_s = neigh;
        i++;
    }
    return track;
}


void parcours_eulerien(graph g, uint s, graph* g_copy) {
    //g should be eulerien or semi-eulerien and s the start point
    int *l = balade(g_copy, s);
    int i = 0;
    while (l[i] != -1) {
        if(degree(*g_copy, l[i]) > 0){
            parcours_eulerien(g, s, g_copy);
        } else {
            printf("%d\n", i);
        }
        i++;
    }
    free(l);
}

void eulerien(graph g) {
    int start;
    if (pre_eulerien(&start, g)) {
        graph g_copy = copy_graph(g);
        parcours_eulerien(g, start, &g_copy);
    }
}
