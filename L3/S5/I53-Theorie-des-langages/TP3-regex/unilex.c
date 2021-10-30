#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0

typedef struct {
    regex_t regex;
    char name[32];
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

// return main_str[start:end] like in python
char* slice(char * main_str, unsigned start, unsigned end) {
    char *buff = calloc(end-start+2, sizeof(char));
    int i;
    for(i = start; i<end; i++) {
        buff[i-start] = main_str[i];
    }

    return buff;
}


unilex_t* create_unilex_arr(char * filename, int n) {
    FILE* fp;
    if ((fp = fopen(filename, "r")) < 0) {
        perror("fopen");
        exit(1);
    }
    char * line = NULL;
    size_t len = 0;
    int i = 0;
    char * buffer = NULL;
    unilex_t *ul_arr = calloc(n, sizeof(unilex_t));
    int index_lq; //index last quotes
    char *lq; //last quotes
    while(getline(&line, &len, fp)!= -1) {
        //searches the las occurrence of the character c and returns line[index_c]
        lq = strrchr(line, '"');
        index_lq = (int)(lq-line);
        // buffer <- regex
        // buffer <- a  | "a"
        buffer = slice(line, 1, index_lq);
        if (regcomp(&(ul_arr[i].regex), buffer, REG_EXTENDED) != 0){
            perror("regcomp");
            exit(1);
        }
        free(buffer);
        //buffer <- name | "xxxx" name\n;
        //                        ^^^^
        //                      ^
        //                  index_lq
        //  strlen(line)-1 to ignore last '\n'
        buffer = slice(line, index_lq+2,strlen(line)-1);
        strcpy(ul_arr[i].name, buffer);
        free(buffer);
        i++;
    }
    return ul_arr;
}

unsigned count_char(FILE *f) {
    unsigned nb_chars;
    // Should check fseek and ftell returns
    fseek(f, 0, SEEK_END);
    nb_chars = ftell(f);
    fseek(f, 0, SEEK_SET);
    return nb_chars;
}



int main ( int argc , char * argv[])
{
    int n = countline(argv[1]);
    unilex_t *ul_arr = create_unilex_arr(argv[1], n);

    FILE* f;
    if ((f = fopen(argv[2], "r")) < 0) {
        perror("fopen");
        exit(1);
    }
    // buffer <- all file
    char * buffer;
    long length;
    length = count_char(f);
    buffer = calloc(length,sizeof(char));
    fread(buffer, 1, length, f);

    int shift = 0;
    char * temp = NULL;
    int regex_success;
    char failed_to_reg = false;
    regmatch_t pmatch;
    while(buffer[shift] != '\n' && failed_to_reg == false) {
        failed_to_reg = true; 
        for(int i = 0; i<n; i++) {
            regex_success = (regexec(&ul_arr[i].regex, buffer+shift, 1, &pmatch, 0) == 0);
            //regex that starts at 0 index;
            if (regex_success && pmatch.rm_so == 0) {
                failed_to_reg = false;
                temp = slice(buffer+shift,pmatch.rm_so,pmatch.rm_eo);
                printf("<%s,%s> ",temp, ul_arr[i].name);
                shift +=pmatch.rm_eo;
                free(temp);
            }
        }
    }
    if(failed_to_reg == true) {
        printf("failed to read the whole file char %d\n", buffer[shift]);
    } else {
        printf("success\n");
    }
    
    return 0;
}
