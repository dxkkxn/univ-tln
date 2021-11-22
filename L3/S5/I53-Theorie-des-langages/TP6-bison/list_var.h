#ifndef LIST_VAR_H_
#define LIST_VAR_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct list_symb {
    char *symb;
    int val;
    struct list_symb * next;
} list_symb;


int inserer(char *nom, int val, list_symb** head);
void print_list(list_symb *head) ;
list_symb * find(list_symb *head, char * name);

#endif // LIST_VAR_H_
