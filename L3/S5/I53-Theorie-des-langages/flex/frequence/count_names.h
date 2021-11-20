#ifndef COUNT_NAMES_H_
#define COUNT_NAMES_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef struct list_symb {
    char *symb;
    int count;
    struct list_symb * next;
} list_symb;

typedef enum{false, true} bool;

int inserer(char *nom , list_symb** head);
void print_list(list_symb *head) ;
list_symb * find(list_symb *head, char * name);

#endif // COUNT_NAMES_H_
