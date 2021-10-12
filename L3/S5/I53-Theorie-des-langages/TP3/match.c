# include <regex.h>
# include <stdio.h>
# include <stdlib.h>
int main ( int argc , char * argv[])
{
    regex_t regex ;
    regmatch_t pmatch;
    if (regcomp(&regex, argv[1], REG_EXTENDED )!=0)
        return 1;
    if (regexec(&regex, argv[2], 1, &pmatch, 0)==0) {
        printf("motif trouve !\n" );
        printf("indice debut = %d, indice fin = %d \n",pmatch.rm_so, pmatch.rm_eo);
    } else {
        printf ( "motif non trouve !\n" );
    }
    regfree(&regex);
    return 0;
}
