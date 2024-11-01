#include "disjoint.h"

disjoint singleton(int i) {
    disjoint res;
    res = malloc(sizeof(el_disjoint));
    res->num = i;
    res->next = NULL;
    res->rep = res;
    res->card = 0;
    res->rang = 0;
    return res;
}

disjoint rep(disjoint set) {
    /* while(set->next != set) */
    /*     set = set->next; */
    /* return set; */
    return set->rep;
}

void reunion(disjoint r, disjoint s) {
    disjoint aux = r;
    while (aux->next != NULL)
        aux = aux->next ;
    aux->next = s;
    aux = s;
    while (aux) {
        aux->rep = r->rep;
        aux = aux->next;
    }
}

void reunion_h(disjoint r, disjoint s) {
    disjoint temp;
    if (r->card > s->card) {
        temp = r;
        r = s;
        s = temp;
    }
    disjoint aux = r;
    while (aux->next != NULL)
        aux = aux->next ;
    aux->next = s;
    aux = s;
    while (aux) {
        aux->rep = r->rep;
        aux = aux->next;
    }
    r->card += s->card;
}

disjoint rep_rang(disjoint set) {
    while(set->rep != set)
        set = set->rep ;
    return set;
}

void reunion_rang(disjoint r, disjoint s) {
    disjoint temp;
    if (r->rang> s->card) {
        temp = r;
        r = s;
        s = temp;
    }
    s->rep = r->rep;
    r->rang++;
}
