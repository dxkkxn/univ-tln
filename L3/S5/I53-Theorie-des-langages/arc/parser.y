%{
  #include <stdio.h>
  #include <ctype.h>
  #include <unistd.h>
  
  #include "asa.h"
  #include "ts.h"

  extern int yylex();
  
%}

%union{
  int nb;
  struct asa * noeud;
 };

%define parse.error verbose

%token ALGO "ALGO"
%token ENTREE "ENTREE"
%token DEBUT "DEBUT"
%token FIN "FIN"
%token SI "SI"
%token SINON "SINON"
%token ALORS "ALORS"
%token FSI "FSI"
%token VAR "VAR"
%token TQ "TQ"
%token FAIRE "FAIRE"
%token FTQ "FTQ"
%token SAUT_LIGNE "\n"
%token ID 
%token <nb> NB
%token AFFECT "<-"
%token SUPEGAL ">="
%token INFEGAL "<="
%token DIFF "!="
%token OU "OU"
%token ET "ET"
%token NON "NON"



%type <noeud> EXP 

%right AFFECT
%left '+' '-'
%left '*' '/' '%'
%right NON 
%left ET
%left OU
%left "<" ">" "=" SUPEGAL INFEGAL DIFF
%start PROG

%%

PROG : ALGO ID SAUT_LIGNE
       ENTREE LIST_VAR SAUT_LIGNE
       DEBUT
       INSTS
       FIN{ codegen($1); }
;

INSTS : INSTS INST {}
      | INST  {}
      ;

EXP : NB      { $$ = creer_feuilleNb(yylval.nb); }
    | EXP OU EXP {}
    | EXP ET EXP {}
    | NON EXP {}
    | EXP '*' EXP {}
    | EXP '/' EXP {}
    | EXP '%' EXP {}
    | EXP '-' EXP {}
    | EXP '+' EXP { $$ = creer_noeudOp('+', $1, $3); }
    ;
INST : SAUT_LIGNE
     | VAR ID AFFECT EXP 
     | SI EXP ALORS INSTS
     | SI EXP ALORS INSTS SINON INSTS
     | TQ EXP FAIRE INSTS FTQ
     ; 

%%
int main( int argc, char * argv[] ) {

  extern FILE *yyin;
  if (argc == 1){
    fprintf(stderr, "aucun fichier fournie\n");
    return 1;
  }
  yyin = fopen(argv[1],"r");
  yyparse();
  return 0;
}

