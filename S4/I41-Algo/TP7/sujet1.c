#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned int uint;

void swap(uint *arr, uint i, uint j) {
    uint tmp;
    tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

uint* gen_perm(uint *arr, uint n) {
    srand(time(NULL));
    for (uint i = 0; i < n; i++) {
        uint tmp = i + rand() % n;
        swap(arr, tmp, n-1);    

    
