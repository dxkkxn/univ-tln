#ifndef STACK_H_
#define STACK_H_

#include "afn.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct stack_elm{
    afn af;
    struct stack_elm * next;
} stack_elm_t, * stack_t;

void print_stack(stack_t head);
void push(stack_t* head, afn af);
afn pop(stack_t* head);


#endif // STACK_H_
