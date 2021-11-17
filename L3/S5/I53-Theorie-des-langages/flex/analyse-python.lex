%{
  /*Prologue*/
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
  list_symb * head = NULL;
  int words = 0;
  int fs
  int inserer(char *nom , list_symb** head) {
    if (*head == NULL) {
      list_symb * new = malloc(sizeof(list_symb));
      new->symb = calloc(strlen(nom), sizeof(char));
      strcpy(new->symb, nom);
      new->count = 1;
      new->next = NULL; 
      *head = new;
      return 1;
    }

    // if head is not null;
    list_symb * curr = *head;
    bool continue_b = true;
    while(curr->next != NULL && continue_b) {
      if (strcmp(curr->symb, nom) == 0){
        continue_b = false;
        curr->count++;
      }
      curr = curr->next;
    }
    if (continue_b) {
      printf("%s\n", nom);
      list_symb * new = malloc(sizeof(list_symb));
      new->symb = calloc(strlen(nom), sizeof(char));
      strcpy(new->symb, nom);
      new->count = 1;
      new->next = NULL; 
      (*curr).next = new;
    } 
    return continue_b;
  }

  void print_list(list_symb *head) {
    list_symb * curr = head;
    while(curr) {
      printf("[%s,%d]->",curr->symb, curr->count);
      curr = curr->next;
    }
    printf("[NULL]\n");
  }

  void print_freq() {
    list_symb * curr = head;
    while(curr) {
      printf("frequence de %s = %f\n", curr->symb, (float)curr->count/(float)words);
      curr = curr->next;
    }
  }

%}
%option nounput
%option noinput
/*Définitions*/
SPACE  [ ]
LETTRE   [a-zA-Z]
MOT      {LETTRE}+

%%
{SPACE} {

}
{MOT} { 
    //yytext: char * contient le motif reconnu
    //yyleng: contient le longeur motif reconnu
    //in flux d'entree
    inserer(yytext, &head);
    words++;
}
.

%%
int main(int argc, char * argv[]) {
  assert(argc == 2);
  yyin = fopen(argv[1], "r");
  yylex();
  print_freq();

  return 0;
}
