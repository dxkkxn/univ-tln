#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef unsigned int uint;
typedef struct {
    uint nbd;
    uint *digits;
} number;

void print(number num) {
    printf("number of digits = %d\n[", num.nbd);
    int i;
    for(i = 0; i < (num.nbd-1); i++)
        printf("%d,",num.digits[i]);
    printf("%d]\n", num.digits[i]);
}

number i2n(int n, uint base) {
    int digits_size = floor(log(n)/log(base)) + 1;
    uint *digits = malloc(sizeof(uint)*digits_size);
    for(int i = 0; i < digits_size; i++) {
        digits[i] = (n%base);
        n /= base;
    }
    number newnum = {digits_size, digits};
    return newnum;
}

number s2n(char *chaine) {
    uint len = strlen(chaine);
    uint *digits = malloc(sizeof(uint)*len);
    for (int i = 0; i < len; i++) 
        digits[i] = chaine[len-i-1] - 48;
    number newnum = {len, digits};
    return newnum;
}

char *n2s(number num) {
    char *str = malloc(sizeof(char)*(num.nbd+1));
    int i; 
    for(i = 0; i<num.nbd; i++) 
        str[i] = num.digits[num.nbd-1-i]+48;
    str[i] = '\0';
    return str;
}

number add(number a, number b, uint base) {
    uint len_max = a.nbd > b.nbd ? a.nbd : b.nbd;
    uint *digits = malloc(sizeof(uint)*(len_max+1));
    uint carry = 0, res;
    for (int i = 0; i<(len_max+1); i++) {
        res = a.digits[i] + b.digits[i] + carry;
        if (res >= base) {
            res %= base;
            carry = 1;
        } else {
            carry = 0 ;
        }
        digits[i] = res;
    }
    number newnum = {len_max+1,digits};
    return newnum;
}

number mult(number a, number b, uint base) {
    uint *digits = calloc(a.nbd+b.nbd, sizeof(uint));
    uint carry, j;
    for (int i = 0; i < a.nbd; i++) {
        carry = 0;
        for (j = 0; j < b.nbd; j++) {
            digits[i+j] += (a.digits[i] * b.digits[j] + carry);
            if (digits[i+j] >= base) {
                carry = digits[i+j]/base;
                digits[i+j] %= base;
            } else {
                carry = 0;
            }
        }
        if (carry) 
            digits[i+j] += carry;

    }
    number newnum = {a.nbd+b.nbd, digits};
    return newnum;
}

number factmp(uint n){
    number one_mp = i2n(1,10);
    number i_mp = one_mp;
    number n_mp = i2n(n,10);
    number res = one_mp;
    int i = 1;
    while (i < n) {
        i_mp = add(one_mp, i_mp, 10);
        res = mult(res,i_mp,10);
        i++;
    }
    return res;
}
    
    

int main(int argc, char **argv) {
    printf("%s\n",n2s(factmp(7)));
    return 0;
}
