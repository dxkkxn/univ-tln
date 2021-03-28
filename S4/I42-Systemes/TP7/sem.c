#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
typedef int semaphore[2];

void init_sem(semaphore s, int n) {
    char jeton = '#';
    pipe(s);
    for(int i = 0; i < n; i++) {
        write(s[1], &jeton, sizeof(jeton));
    }
}

void p(semaphore s) {
    char jeton;
    read(s[0], &jeton, sizeof(char));
}

void v(semaphore s) {
    char jeton = '#';
    write(s[1], &jeton, sizeof(char));
}

