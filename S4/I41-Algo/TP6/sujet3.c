#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* l2s(unsigned int* arr, int n);
unsigned int* s2l(char* ch);
int print_array(int* arr, int n);


unsigned int* add(unsigned int* A, int na, unsigned int* B, int nb, unsigned int base) {
    int tmp, *temp, carry = 0;
    if (na < nb) {
        tmp = na;
        na = nb;
        nb = tmp;

        temp = A;
        A = B;
        B = temp;
    } 
    unsigned int* res = (unsigned int *) malloc(sizeof(unsigned int) * na+1); 
    for (int i = 0; i < nb; i++) {
        tmp = carry + A[i] + B[i];
        if (tmp >= base) {
            carry = 1;
            tmp %= base;
        } else {
            carry = 0;
        }
        res[i] = tmp; 
    }
    for (int i = nb; i < na; i++) {
        tmp = A[i] + carry;
        if (tmp >= base) { 
            tmp %= base;
            carry = 1;
        } else {
            carry = 0; 
        }
        res[i] = tmp;
    }
    return res;
}
        
unsigned int* mult(unsigned int* A, int na, unsigned int* B, int nb, unsigned int base) {
}    
    

void main (int argc, char** argv) {
    int max = strlen(argv[2]) > strlen(argv[1]) ? strlen(argv[2]) : strlen(argv[1]);
   printf(">>>>>>>%s\n", l2s(add(s2l(argv[1]), strlen(argv[1]), s2l(argv[2]), strlen(argv[2]), atoi(argv[3])), max + 1));
}


