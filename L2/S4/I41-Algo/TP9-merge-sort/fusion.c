#include <stdio.h>
#include <stdlib.h>

#define N 11
typedef struct { 
    unsigned int n;
    int *vals;
} list;

void print_list(list arr) {
    printf("[");
    for (int i = 0; i < (arr.n)-1; i++) {
        printf("%d,", arr.vals[i]);
    }
    printf("%d]\n", arr.vals[arr.n-1]);
}


void copy (list X, unsigned int i, list Y, unsigned int j, int n) {
    // copy n values of X[i,i+n-1] in Y[j, j+n-1] 
    for (int k = 0; k < n; k++) {
        Y.vals[j+k] = X.vals[i+k];
    }
}

void fusion(list L, unsigned int p, unsigned int q, unsigned int r) {
    int left_tab[q-p+1];
    int right_tab[r-q]; 
    list left_list = {(q-p+1), left_tab};
    list right_list = {r-q, right_tab};
    copy(L, p, left_list, 0, q-p+1);
    copy(L, q+1, right_list, 0, r-q);

    int i = 0, j = 0, k = p;
    while(i < left_list.n && j < right_list.n) {
        if (left_list.vals[i] > right_list.vals[j]) {
            L.vals[k] = right_list.vals[j];
            k++, j++;
        } else {
            L.vals[k] = left_list.vals[i];
            k++, i++;
        }
    }
    copy(left_list, i, L, k, left_list.n-i);
}

void fusion_sort(list L, unsigned int p, unsigned int r) {
    int mid;
    if (p != r) {
        mid = (p+r)/2;
        fusion_sort(L, p, mid);
        fusion_sort(L, mid+1, r);
        fusion(L, p, mid, r);
    }
}


void main() {
    int tab[11] = {-1,-3,1,6,3,4,16,26,-514,-47, 0};
    list main_list = {10, tab};
    //print_list(main_list);
    //int tab_sup[5];
    //list sup_list = {5, tab_sup};
    //print_list(sup_list);
    //copy(main_list, 5, sup_list, 0, 5);
    //print_list(sup_list);
    //fusion(main_list, 9, 9, 10);
    //fusion_sort(main_list, 0, 10);
    fusion_sort(main_list, 0, 10);

    print_list(main_list);
}


