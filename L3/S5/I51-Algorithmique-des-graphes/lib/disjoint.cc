#include "disjoint.h"

disjoint singleton(int i) {
    disjoint res;
    res = malloc(sizeof(el_disjoint));
    res.num = i;
    res->svt = NULL;
    res.rep = res;
}

disjoint rep(disjoint ens) {
    while(ens->svt != NULL)
        ens = ens-svt;
    return ens;
}

void reunion(disjoint r, disjoint s) {
    disjoint aux = r;
    while(aux->svt != NULL)
        aux = aux-svt;
    aux->svt = s;
}






