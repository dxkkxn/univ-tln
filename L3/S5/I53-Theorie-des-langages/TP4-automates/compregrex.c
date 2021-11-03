#include "compregrex.h"

void print_arr_ul(unilex_t * arr, uint size) {
    printf("[");
    uint i;
    for (i = 0; i < (size-1); i++) {
        printf("(%d,%c),", arr[i].type, arr[i].val);
    }
    printf("(%d,%c)]", arr[i].type, arr[i].val);
}

unilex_t * scanner(char * str) {
    unilex_t * arr_ul = calloc(strlen(str)-1, sizeof(unilex_t));
    uint i = 0;
    uint mayus, minus;
    while(*str != '\0') {
        printf("%c\n", *str);
        switch (*str) {
            case  '(':
                arr_ul[i].type = PO;
                arr_ul[i].val =  *str;
                break;
            case  ')':
                arr_ul[i].type = PF;
                arr_ul[i].val =  *str;
                break;
            case  '.': case '*': case '+':
                arr_ul[i].type = OP;
                arr_ul[i].val =  *str;
                break;
            default:
                minus = ('a' <= *str && *str <= 'z');
                mayus = ('A' <= *str && *str <= 'Z');
                if(minus || mayus || (*str) == '&') {
                    arr_ul[i].type = CHAR;
                    arr_ul[i].val =  *str;
                } else {
                    fprintf(stderr, "[scanner] SYNTAX ERROR near character %c", *str);
                    exit(-1);
                }
                break;
        }
        str++;
        i++;
    }
    return arr_ul;
}

/* Expr -> Terme + Expr
 *      | Terme
 * Terme -> Fact . Terme
 *       | Fact
 * Fact ->  Reste *
 *      | Reste
 * Reste -> CHAR
 *       | ( Expr )
*/
uint i = 0;
char * rpn;
unilex_t * l;
uint n;
char * parser(unilex_t * arr_ul, uint size) {
    l = arr_ul;
    n = size;
    rpn = calloc(size, sizeof(char));
    if(expr() && i == size) {
    }
}

bool expr() {
    return ()
}
