%{
#include <string.h>
#include "parser.h" 
%}
  
%option nounput
%option noinput

CHIFFRE  [0-9]
OP_ARITH [-+*/%]
ID [^0-9][A-Za-z0-9_]+
NB 0|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-6]


%%
"\n"    {return SAUT_LIGNE;}
"ALGO"   {return ALGO;}
"ENTREE"  {return ENTREE;}
"DEBUT"   { return DEBUT;}
"FIN"   { return FIN;}
"SI"      {return SI;}
"ALORS"   { return ALORS;}
"SINON"   {return SINON;}
"FSI"      {return FSI;}
"VAR"      {return VAR;}
"TQ"      {return TQ;}
"FAIRE"   {return FAIRE;}
"FTQ"     {return FTQ;}
"!="      { return DIFF;}
">="      { return SUPEGAL;}
"<="      { return INFEGAL;}
"="       { return yytext[0];}
"<"       { return yytext[0];}
">"       { return yytext[0];}
"<-"      { return AFFECT; }
"OU"      { return OU;}
"ET"      { return ET;}
"NON"     { return NON;}
{ID}      { return ID;}
{OP_ARITH}  { return yytext[0];}

{NB} { yylval.nb = atoi(yytext); return NB;}
.         { fprintf(stderr, "[err lexer] caractere inconnu %c\n",yytext[0]); return 1;}

%%
