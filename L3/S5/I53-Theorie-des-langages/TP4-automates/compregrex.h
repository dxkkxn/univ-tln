#ifndef COMPREGREX_H
#define COMPREGREX_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum{PO, PF, OP, CHAR} type_t;
typedef struct  {
    type_t type;
    char val;
} unilex_t;
typedef unsigned int uint;
typedef enum{false, true} bool;

void print_arr_ul(unilex_t * arr, uint size);
unilex_t * scanner(char * str);
char * parser(unilex_t * arr_ul, uint size);

#endif // COMPREGREX_H
