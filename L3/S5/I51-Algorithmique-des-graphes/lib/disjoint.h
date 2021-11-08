#ifndef DISJOINT_H
#define DISJOINT_H
typedef struct _disjoint_ {
    int num;
    struct _disjoint_ * next;
} el_disjoint, * disjoint;
disjoint singleton(int);
disjoint rep(disjoint);
void reunion(disjoint r, disjoint s);
#endif
