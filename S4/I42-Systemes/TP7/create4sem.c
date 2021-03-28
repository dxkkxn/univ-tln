#include <stdio.h>
#include <sys/ipc.h>

void main(int argc, char** argv) {
    char* filename = argv[0];
    int key = ftok(filename, 'a');
    
}

    
