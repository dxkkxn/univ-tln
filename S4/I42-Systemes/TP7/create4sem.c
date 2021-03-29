#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>

void main(int argc, char** argv) {
    char* filename = argv[0];
    int key = ftok(filename, 'a');
    int sem_id = semget(key, 4, IPC_CREAT);
    
    FILE* file = fopen("tmp_file", "w");
    fprintf(file, "%d\n", sem_id);
    fclose(file);
}

    
