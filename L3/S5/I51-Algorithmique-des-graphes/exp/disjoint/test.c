#include "disjoint.h"
#define n 10

int main() {
    disjoint t[n];
    for (int i = 0; i < n; i++) 
        t[i] = singleton(i);
    int m = n;
    int tmp1, tmp2;
    while (m > 1) {
        i = rand() % n;
        j = rand() % n;
        if ((tmp1 = rep(i)) != (tmp2 = rep(j))) {
            reunion(tmp1, tmp2);
            m--;
        }
    return 0;
}
