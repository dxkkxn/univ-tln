#include "stack.h"

void print_stack(stack_t head) {
    stack_elm_t *aux = head;
    printf("/TOP\\\n");
    while (aux) {
        afn_print(aux->af);
        aux = aux->next;
    }
    printf("\\-/\n");
}

void push(stack_t* head, afn af) {
    stack_elm_t * new_head = malloc(sizeof(stack_elm_t));
    new_head->af = af;
    new_head->next = (*head);
    (*head) = new_head;
}

afn pop(stack_t* head) {
    assert(*head != NULL);
    afn af = (*head)->af;
    stack_elm_t * old_head = (*head);
    (*head) = (*head)->next;
    free(old_head);
    return af;
}
