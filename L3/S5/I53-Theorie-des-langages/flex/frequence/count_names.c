#include "count_names.h"
int inserer(char *nom, list_symb **head) {
  if (*head == NULL) {
    list_symb *new = malloc(sizeof(list_symb));
    new->symb = calloc(strlen(nom), sizeof(char));
    strcpy(new->symb, nom);
    new->count = 1;
    new->next = NULL;
    *head = new;
    return 1;
  }

  // if head is not null;
  list_symb *curr = *head;
  bool continue_b = true;
  while (curr->next != NULL && continue_b) {
    if (strcmp(curr->symb, nom) == 0) {
      continue_b = false;
      curr->count++;
    }
    curr = curr->next;
  }
  if (continue_b) {
    list_symb *new = malloc(sizeof(list_symb));
    new->symb = calloc(strlen(nom), sizeof(char));
    strcpy(new->symb, nom);
    new->count = 1;
    new->next = NULL;
    (*curr).next = new;
  }
  return continue_b;
}

void print_list(list_symb *head) {
  list_symb *curr = head;
  while (curr) {
    printf("[%s,%d]->", curr->symb, curr->count);
    curr = curr->next;
  }
  printf("[NULL]\n");
}

/*
** returns the list_symb where name is found
*/
list_symb * find(list_symb *head, char * name) {
  list_symb *curr = head;
  while (curr) {
      if (strcmp(curr->symb, name) == 0) {
          break;
      }
    curr = curr->next;
  }
  return curr;
}
