#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
} arg;

void main (int argc, char** argv) {
    int miners = atoi(argv[1]), shovel = atoi(argv[2]), pickaxe = atoi(argv[3]);
    // 0 - shovel | 1 - pickaxe
    int semid = semget(ftok("tmp_file", 'a'), 2, 0777|IPC_CREAT|IPC_EXCL); 
    arg.val = shovel;
    semctl(semid, 0, SETVAL, arg); 
    arg.val = pickaxe;
    semctl(semid, 1, SETVAL, arg); 
    srand((unsigned int) NULL);
    for (int i; i < miners; i++) {
        if (fork() == 0) {
            // miner

            printf("Creation of miner %d (%d)\n", i+1, getpid());
            
            wait_rand = 1 + srand() % 5; 
            printf("The miner %d wait %d hours before work\n", i+1, wait_rand);
            sleep(wait_rand);

            struct sembuf sops[2] = {{0,-1,0}, {1,-1,0}};
            semop(semid, sops, 2);
            printf("The miner %d take a shovel and a pickaxe.", i+1);

            wait_rand = 1 + srand() % 5; 
            printf("The miner %d start work for %d.", i+1, wait_rand);
            sleep(wait_rand);

            int gold;
            gold = 1 + rand() % 1000;
            printf("The miner %d has extracted %d of gold\n", i, gold);

            printf("The miner %d return a shovel and a pickaxe\n", i);
            struct sembuf sops[2] = {{0,1,0}, {1,1,0}};
            semop(semid, sops, 2);

            printf("The miner of pid %d finished\n", getpid());
            exit(0);
        }
    }
    while (waitpid(-1, NULL, 0)  > 0);

}

