#include "swap.h"

void swap(int& a, int& b) {
    int temp = a;
    a = b, b = temp;
}

void swap(complex_num& a, complex_num& b) {
    complex_num tmp = a;
    a = b, b = tmp;
}

