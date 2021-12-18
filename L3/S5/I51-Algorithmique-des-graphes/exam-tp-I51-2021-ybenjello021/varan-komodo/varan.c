#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;
typedef enum{false = 0, true = 1} bool;

uint* arr;
uint* columns;
uint size;

void print_chessboard(uint arr[], uint size) {
    int i, j;
    for(j = 0; j < size; j++) {
        printf("==");
    }
    printf("=\n");
    for(i= 0; i < size; i++) {
        printf("|");
        for(j = 0; j < size; j++) {
            if(j == arr[i]) {
                printf("Q|");
            } else {
               printf(" |");
            }
        }
        printf("\n");
    }
    for(j = 0; j < size; j++) {
        printf("==");
    }
    printf("=\n");
}

bool valid(uint line, uint col) {
    if(columns[col])
        return false;

    if ((int)line - 2 >= 0) {
        if (arr[line-2] == col-1 || arr[line-2] == col+1) {
            return false;
        }
    }
    if ((int)line - 1 >= 0) {
        if (arr[line-1] == col-2 || arr[line-1] == col+2) {
            return false;
        }
    }

    return true;
}


int nb_solutions;
void varan(uint line) {
    if(line == size) {
//      printf("One solution is : ");
//      printf("[");
//      for(uint i = 0; i < size-1; i++) {
//          printf("%d,",arr[i]);
//      }
//      printf("%d]\n", arr[size-1]);
//      /* print_chessboard(arr, size); */
      nb_solutions++;
    }
    for(uint col = 0; col < size; col++) {
        if(valid(line, col)) {
            arr[line] = col;
            columns[col] = true;

            varan(line+1);

            arr[line] = 0;
            columns[col] = false;

        }
    }
}

void print_all_solutions(uint size_bis) {
    size = size_bis;
    arr = calloc(size, sizeof(uint));
    columns = calloc(size, sizeof(uint));
    nb_solutions = 0;
    varan(0);

    free(columns);
    free(arr);
}


int main(int argc, char *argv[]) {
    print_all_solutions(atoi(argv[1]));
    //for(int i = 1; i<9; i++) {
    //  print_all_solutions(i);
    //  printf("V(%d) = %d\n", i, nb_solutions);
    //}
    printf("V(%s) = %d\n", argv[1], nb_solutions);
    return 0;
}
