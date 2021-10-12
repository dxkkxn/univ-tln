# include <regex.h>
# include <stdio.h>
# include <stdlib.h>
int main ( int argc , char * argv[])
{
    if (argc < 3) {
        printf("ERROR 404 Argument not found");
        return 1;
    }

    regex_t regex ;
    regmatch_t pmatch;
    FILE* file = fopen(argv[2], "r");
    char * line = NULL;
    size_t len = 0;
    char to_p = ' ';
    int i;
    int regex_success, print_n;

    if (regcomp(&regex, argv[1], REG_EXTENDED )!=0)
        return 1;

    while (getline(&line, &len,file) != -1) {
        //printf("line read\n");
        //fflush(stdout);
        regex_success = regexec(&regex, line, 1, &pmatch, 0); 
        if(regex_success == 0){
            printf("%s", line);
            print_n = 1;
        } else {
            print_n = 0;
        }
        while (regex_success==0) {
            for(i = 0; i<pmatch.rm_eo; i++) {
                if (i < pmatch.rm_so)
                    printf(" ");
                else
                    printf("^");
            }
            // line = line[pmath.rm_eo:]
            char * buffer = calloc(len, sizeof(char));
            for(i = pmatch.rm_eo; i<len; i++)
                buffer[i-pmatch.rm_eo] = line[i];
            free(line);
            line = buffer;
            regex_success = regexec(&regex, line, 1, &pmatch, 0); 
        }
        if(print_n)
            printf("\n");
    }
    fclose(file);
    regfree(&regex);
    return 0;
}
