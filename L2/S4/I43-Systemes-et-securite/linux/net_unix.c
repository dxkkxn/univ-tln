#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv, char *W[]) {
    int x = atoi(argv[1]);
    int i = 0;
    while (argv[i])
        puts(argv[i++]);
    for (i = 0; i<argc; i++) 
        puts(argv[i]);
    i = 0;
    while (W[i])
        puts(W[i++]);
    i = 0;
    while (i != 1) i+=2;
    return x;
}
