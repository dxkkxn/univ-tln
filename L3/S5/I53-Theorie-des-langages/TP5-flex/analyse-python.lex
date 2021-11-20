%{
    /*Prologue*/
    #include <assert.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "frequence/count_names.h"
    list_symb * head = NULL;
    int nb_spaces = 0;
    bool seen_letter = 0;
    int level_nested_loops = 0;
    int imbrication = 0;
    int max_indent = 0;
    int indent_loop = 0;
    char * sup_spaces_parenthesis(char * name) {
        printf("%s\n", name);
        char * res = calloc(strlen(name), sizeof(char));
        uint i = 0;
        while(*name != '\0') {
            if (*name != ' ' && *name != '(')
                res[i++] = *name;
            name++;
        }
        return res;
    }
%}
%option nounput
%option noinput
/*Définitions*/
SPACE    [ ]
NEW_LINE [\n]
LOOP     while|for
LETTER   [a-zA-Z]
MOT      {LETTER}+
FUNCTION ({LETTER}|"_")+{SPACE}+"("

%%

{SPACE} {
    if (!seen_letter) {
        nb_spaces++;
    }
}
{NEW_LINE} {
    nb_spaces = 0;
    seen_letter = false;
}
{LOOP} {
    printf("[LOOP] %s\n", yytext);
    if(!seen_letter) {
        if ((nb_spaces/4) > indent_loop) {
            indent_loop = nb_spaces/4;
            level_nested_loops++;
        }
        if (nb_spaces/4 > max_indent) {
            max_indent = (nb_spaces/4);
        }
    }
    seen_letter = true;
}
{FUNCTION} {
    printf("[FUNCTION] %s\n", yytext);
    inserer(sup_spaces_parenthesis(yytext), &head);

}
{MOT} {
    printf("[MOT] %s\n", yytext);
    if(!seen_letter) {
        if (nb_spaces/4 > max_indent) {
            max_indent = (nb_spaces/4);
        }
    }
    seen_letter = true;
}
.
%%
int main(int argc, char * argv[]) {
    assert(argc == 3);
    yyin = fopen(argv[1], "r");
    yylex();
    printf("Maximal level of imbrication %d\n", max_indent);
    printf("Maximal level of nested loops %d\n", level_nested_loops);
    printf("Function %s: ", argv[2]);
    list_symb * target = find(head, argv[2]);
    if (target != NULL) {
        printf("%d\n", target->count);
    } else {
        printf("0\n");
    }
    return 0;
}
