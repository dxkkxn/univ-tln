#include "compregrex.h"
#include "afn.h"

bool is_char(char c) {
    uint minus = ('a' <= c && c <= 'z');
    uint mayus = ('A' <= c && c <= 'Z');
    return(minus || mayus || c == '&');
}

void print_arr_ul(unilex_t * arr, uint size) {
    printf("[");
    uint i;
    for (i = 0; i < (size-1); i++) {
        printf("(%d,%c),", arr[i].type, arr[i].val);
    }
    printf("(%d,%c)]\n", arr[i].type, arr[i].val);
}

unilex_t * scanner(char * str) {
    unilex_t * arr_ul = calloc(strlen(str), sizeof(unilex_t));
    assert(arr_ul != NULL);
    uint i = 0;
    while(*str != '\0') {
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
                if (is_char(*str)) {
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

/* Expr -> Terme Reste_e
 *
 * Reste_e -> + Terme Reste_e
 *         | epsilon
 * Terme -> Fact Reste_t
 *
 * Reste_t -> . Fact Reste_t
 *         | epsilon
 *
 * Fact  -> Reste_F*
 *       |  Reste_F
 * Reste_F -> CHAR
 *         | ( Expr )
*/
uint i = 0;
uint top = 0;
char * rpn;
unilex_t * l;
uint n;
char * parser(unilex_t * arr_ul, uint size) {
    l = arr_ul;
    n = size;
    rpn = calloc(size+1, sizeof(char));
    assert(rpn != NULL);
    if(expr() && i == size)
        return rpn;
    rpn = NULL;
    return rpn;
}

bool expr() {
    return (terme() && reste_e());
}

bool reste_e() {
    if (i < n && l[i].val == '+') {
        i++;
        if (terme() && reste_e()) {
            rpn[top++] = '+';
            return true;
        }
        return false;
    }
    return true;
}

bool terme() {
    return (fact() && reste_t());
}

bool reste_t() {
    if (i < n && l[i].val == '.') {
        i++;
        if (fact() && reste_t()) {
            rpn[top++] = '.';
            return true;
        }
        return false;
    }
    return true;
}

bool fact() {
    if (reste_f()) {
        if (i < n && l[i].val == '*') {
            rpn[top++] = '*';
            i++;
        }
        return true;
    }
    return false;
}

bool reste_f() {
    if ( i < n && l[i].type == CHAR) {
        rpn[top++] = l[i].val;
        i++;
        return true;
    } else if (i < n && l[i].type == PO) {
        i++;
        if (expr() && i < n && l[i].type == PF) {
            i++;
            return true;
        }
    }
    return false;
}

afd codegen(char * rpn_n) {
    printf("here>>>>rpn = %s\n", rpn);
    stack_t stack = NULL;
    afn * curr_af;
    afn aux_af;
    afn aux_af2;
    while (*rpn != '\0') {
        printf("*rpn = %c\n", *rpn);
        curr_af = malloc(sizeof(afn));
        if (is_char(*rpn)) {
            afn_char(curr_af, *rpn);
            push(&stack, *curr_af);
        } else if (*rpn == '*') {
            aux_af = pop(&stack);
            afn_kleene(curr_af, aux_af);
            afn_free(&aux_af);
            push(&stack, *curr_af);
        } else if (*rpn == '.'){
            aux_af = pop(&stack);
            aux_af2 = pop(&stack);
            afn_concat(curr_af, aux_af2, aux_af);
            afn_free(&aux_af);
            afn_free(&aux_af2);
            push(&stack, *curr_af);
        } else {
            assert(*rpn == '+');
            aux_af = pop(&stack);
            aux_af2 = pop(&stack);
            afn_union(curr_af, aux_af2, aux_af);
            afn_free(&aux_af);
            afn_free(&aux_af2);
            push(&stack, *curr_af);
        }
        rpn++;
        print_stack(stack);
    }
    afd res;
    afn_determinisation(pop(&stack), &res);
    afd_print(res);
    return res;
}
