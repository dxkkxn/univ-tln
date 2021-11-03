#include "compregrex.h"
#include <assert.h>
int main(int argc, char* argv[]) {
    assert(argc == 3);
    char * regex = argv[1];
    char * str = argv[2];
    print_arr_ul(scanner(regex), strlen(regex));

}
