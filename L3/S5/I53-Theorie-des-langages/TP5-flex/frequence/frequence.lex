%{
  /*Prologue*/
  #include "count_names.h"
  list_symb * head = NULL;
  int words = 0;

  void print_freq() {
    list_symb *curr = head;
    while (curr) {
      printf("frequence de %s = %f\n", curr->symb,
            (float)curr->count / (float)words);
      curr = curr->next;
    }
}
%}
%option nounput
%option noinput
/*Définitions*/
LETTRE   [a-zA-Z]
MOT      {LETTRE}+

%%
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
