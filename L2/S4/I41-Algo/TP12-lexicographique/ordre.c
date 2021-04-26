#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ordre(char *u, char *v) {
    int i, len_u = strlen(u), len_v = strlen(v);
    for(i = 0; i <= len_u && i <= len_v && u[i] == v[i]; i++);
    if(i > len_u && i > len_v)
        return 0;
    else if(i > len_u || u[i] < v[i]) {
        printf("%d %d\n", u[i], v[i]);
        return -1;
    }
    else if(i > len_v || v[i] < u[i]){
        printf("%d %d\n", u[i], v[i]);
        return 1;
    }
}

void main(int argc, char **argv) {
    int d = ordre(argv[1], argv[2]);
    if (d == -1)
        printf("%s < %s\n",argv[1],argv[2]);
    if (d == 0)
        printf("%s == %s\n",argv[1],argv[2]);
    if (d == 1)
        printf("%s > %s\n",argv[1],argv[2]);
}
