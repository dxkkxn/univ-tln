#include "afd.h"
#include "compregrex.h"
#include <assert.h>
int main(int argc, char* argv[]) {
    assert(argc == 3);
    char * regex = argv[1];
    char * str = argv[2];
    unilex_t * arr_ul = scanner(regex);
    print_arr_ul(arr_ul, strlen(regex));
    char * rpn = parser(arr_ul, strlen(regex));
    printf("here --->%s\n", rpn);
    printf("--->%ld\n", strlen(rpn));
    afd res = codegen(rpn);
    printf("--->%d\n",afd_simul(str, res));
}
