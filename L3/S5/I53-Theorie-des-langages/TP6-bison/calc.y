%{
    #include <stdio.h>
    #include <ctype.h>
    #include <stdlib.h>
    #include "list_var.h"

    //int yylval;
    int yylex();
    int yyerror(const char *msg);
    /* calc a^b */
    int mypow(unsigned int a, unsigned int b) {
      int res = 1;
      unsigned int x = a;
      while(b) {
         if (b&1) 
            res *= x;
          x*=x;
          b >>= 1;
      }
      return res;
    }
    char next_char(){
      char car;
      do {
          car = getchar();
      } while(car == ' ' || car == '\t' );
      return car;
    }
    //int mem[26] = {0};
    list_symb * head = NULL;
%}
%define parse.error verbose 
%union {
  int num;
  list_symb * node;
}

%type<node> MEM
%type<num> EXP NB

%token NB FIN PO PF MEM FINLIGNE
// Unites lexicales
%right AFFECT 
%left PLUS MOINS
%left MULT DIV
%right POW 

%start PROG


%%

PROG : %empty
     | PROG EXP FINLIGNE { printf("%d\n", $2 );}
     ;
EXP  : NB { $$ = $1 ;}
     | MEM { $$ = $1->val; }
     | PO EXP PF { $$ = $2 ;}
     | EXP MULT EXP { $$ = $1 * $3 ;}
     | EXP DIV EXP { $$ = $1 / $3 ;}
     | EXP PLUS EXP { $$ = $1 + $3 ;}
     | EXP MOINS EXP { $$ = $1 - $3 ;}
     | EXP POW EXP {$$ = mypow($1, $3);}
     | MEM AFFECT EXP { $$ = ($1->val = $3);}
     ;
%%

int main( void ) {
    yyparse() ;
    return 0;
}

int yylex(){
    char car = next_char();
    if (car == EOF )
        return 0;

    if (isdigit(car)) {
        int nb = car -'0';
        car = next_char();
        while (isdigit(car)) {
            nb *= 10;
            car = next_char();
        }
        ungetc(car,stdin);
        yylval.num = nb;
        return NB;
    }
    if ('a' <= car && car <= 'z') {
        char name[16];
        int i = 0;
        while(i < 16 && 'a' <= car && car <= 'z') {
            name[i++] = car;
            car = getchar();
        }
        if (i == 16) {
            fprintf(stderr, "variable name overflow");
            exit(1);
        } else {
            ungetc(car,stdin);
        }
        inserer(name, 0, &head);
        yylval.node = find(head, name);
        //yylval = car - 'A';
        return MEM; 
    } 
    switch (car) {
        case '=':
            return AFFECT;
        case '(':
            return PO;
        case ')':
            return PF;
        case '*': 
            if ((car = next_char()) == '*') {
                return POW;
            }
            ungetc(car, stdin);
            return MULT;
        case '/': 
            return DIV;
        case '-': 
            return MOINS;
        case '+':
            return PLUS;
        case '\n':
            return FINLIGNE;
    }
  return -1;
}
 
int yyerror( const char *msg) {
    printf("\n%s\n", msg);
    return 1;
}

