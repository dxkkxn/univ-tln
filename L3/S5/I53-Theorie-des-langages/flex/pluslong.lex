%{
  /*Prologue*/
  #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>
  #include <assert.h>
  int longmax = 0;
  char motlepluslong[256];
  int ligne = 0;
  int col = 0;
  int ligne_max = 0;
  int col_max = 0;
  int sum = 0;
%}
%option nounput
%option noinput
/*Définitions*/
SAUT_LIGNE [\n]
BLANC    [ \t\n]
LETTRE   [a-zA-Z]
MOT      {LETTRE}+
INT      [0-9]+

%%
{INT} {
    sum+=atoi(yytext);
}
{LETTRE} {
  col++;
}
{SAUT_LIGNE} {
  ligne++;
  col=0;
}
{MOT} { 
    if (yyleng > longmax){
    //yytext: char * contient le motif reconnu
    //yyleng: contient le longeur motif reconnu
    //in flux d'entree
    longmax = yyleng;
    ligne_max = ligne; 
    col_max = col;
    strcpy(motlepluslong, yytext);
    printf("\n%s",yytext);
  }
}
{BLANC} {
    col++;
}
.

%%
int main(int argc, char * argv[]) {
  assert(argc == 2);
  yyin = fopen(argv[1], "r");
  yylex();
  printf("\nMot le plus long: %s, de longueur: %d, a la ligne %d et a la colonne %d\n", motlepluslong, longmax, ligne_max, col_max);
  printf("sum all nums %d\n", sum);
  return 0;
}
