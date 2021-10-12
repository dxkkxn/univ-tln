# include <regex.h>
# include <stdio.h>
# include <stdlib.h>
#include <string.h>

typedef struct {
    regex_t regex;
    char name[32];
    int n;
} unilex_t;

int countline(char *filename) {
    FILE* fp;
    if ((fp = fopen(filename, "r")) < 0) {
        perror("fopen");
        exit(1);
    }
    int lines = 0;
    char ch;
    while(!feof(fp)) {
        ch = fgetc(fp);
        if (ch == '\n')
            lines++;
    }
    fclose(fp);
    return lines;
}


unilex_t* create_unilex_arr(char * filename, int lines) {
    FILE* fp;
    if ((fp = fopen(filename, "r")) < 0) {
        perror("fopen");
        exit(1);
    }
    char * line = NULL;
    size_t len = 0;
    int i = 0;
    char buffer[50];
    regex_t regex;
    unilex_t *ul_arr = calloc(lines, sizeof(unilex_t));
    int i_arr; //indice arr
    printf("apres %s\n", ul_arr[0].name);
    /*

    while(getline(&line, &len, fp)!= -1) {
        buffer[0] = '"';
        for(i = 1; i<len && line[i] != '"'; i++) 
            buffer[i] = line[i];
        line[i] = '"';
        if (regcomp(&regex, buffer, REG_EXTENDED) != 0){
            perror("regcomp");
            exit(1);
        }
        ul_arr[i_arr].regex = regex;
        while (line[i] != '\n') {
            ul_arr[i_arr].name[i] = line[i];
            i++;
        }
        strcpy(ul_arr[i_arr].name, buffer);
        i_arr++;
        }
        */
    return ul_arr;
    }




int main ( int argc , char * argv[])
{
    regex_t regex ;
    regmatch_t pmatch;
    int n = countline(argv[1]);
    printf("%d\n", n);
    unilex_t *ul_arr = create_unilex_arr(argv[1], n);
    for(int i = 0; i<n; i++) {
        printf("OOOOK");
        printf("%s",ul_arr[i].name);
    }
    
    /*
    if (regcomp(&regex, argv[1], REG_EXTENDED )!=0)
        return 1;
    if (regexec(&regex, argv[2], 1, &pmatch, 0)==0) {
        printf("motif trouve !\n" );
        printf("indice debut = %d, indice fin = %d \n",pmatch.rm_so, pmatch.rm_eo);
    } else {
        printf ( "motif non trouve !\n" );
    }
    regfree(&regex);
    */
    return 0;
}
