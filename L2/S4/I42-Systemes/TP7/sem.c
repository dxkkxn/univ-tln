#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
typedef int semaphore[2];

void init_sem(semaphore s, int n) {
    char token = '#';
    pipe(s);
    for(int i = 0; i < n; i++) {
        write(s[1], &token, sizeof(char));
    }
}

void p(semaphore s) {
    char token;
    read(s[0], &token, sizeof(char));
}

void v(semaphore s) {
    char token = '#';
    write(s[1], &token, sizeof(char));
}

