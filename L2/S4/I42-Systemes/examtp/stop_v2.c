#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <errno.h>

#define NP 2
#define NT 5
#define CLE 123

void P(int semid, int n_sem){
    struct sembuf sops;
    sops.sem_num = n_sem;
    sops.sem_op = -1;
    sops.sem_flg = 0;
    semop(semid, &sops, 1);
}

void V(int semid, int n_sem) {
    struct sembuf sops;
    sops.sem_num = n_sem;
    sops.sem_op = 1;
    sops.sem_flg = 0;
    semop(semid, &sops, 1);
}

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
} arg;

int main() {
    int decision_shmid, res_shmid, scores_shmid, semid;
    key_t key = ftok("stop_v1.c", CLE);

    if ((decision_shmid = shmget(key, sizeof(int)*NP, 0600|IPC_CREAT)) == -1)
        perror("shmget decision"), exit(-1);
    if ((scores_shmid = shmget(key, sizeof(int)*NP, 0600|IPC_CREAT)) == -1)
        perror("shmget scores"), exit(-1);
    if ((res_shmid = shmget(key, sizeof(int), 0600|IPC_CREAT)) == -1)
        perror("shmget resultat"), exit(-1);

    if ((semid = semget(key, 3, 0600|IPC_CREAT)) == -1) 
        perror("semget"), exit(-1);
    //sem[0] indiquer au fils resultat du pere initialise' 'a 1
    if (semctl(semid, 0, SETVAL, 0) == -1)
        perror("semclt"), exit(-1);
    //sem[1] fils indique prise de decision initialise a -NB + 1
    if (semctl(semid, 1, SETVAL, -NB + 1) == -1)
        perror("semclt"), exit(-1);
    //sem[1] pere indique leur score au processus ayant fini NB
    if (semctl(semid, 2, SETVAL, NB) == -1)
        perror("semclt"), exit(-1);

    int sleep_sec, decision, *tab_decision, *tab_scores, *res;

    if ((tab_decision = (int *)shmat(decision_shmid, NULL, 0)) ==(int *) -1) 
        perror("shmat decision"), exit(-1);
    if ((res = (int *)shmat(res_shmid, NULL, 0)) ==(int *) -1) 
        perror("shmat resultat"), exit(-1);
    if ((tab_scores = (int *)shmat(scores_shmid, NULL, 0)) ==(int *) -1) 
        perror("shmat scores"), exit(-1);

    for(int i = 0; i < NP; i++) {
        tab_decision[i] = 0;
        tab_scores[i] = 0;
    }


    for(int i = 0; i < NP; i++) {
        if (fork() == 0) {
            // fils 
            srand(getpid());

            for (int j = 0; j < NT; j++) {
                 // si ce n'est pas le premier tour on lit
                 // le resultat precedant;
                if (j != 0) {
                    //si res est egal `a 0, partie termine'
                    P(semid, 0);
                    if (res == 0) 
                        exit(0);
                    V(semid, 0);
                }

                sleep_sec = (rand()%3)+1;
                sleep(sleep_sec);

                decision = rand()%2;
                tab_decision[i] = decision;
                P(semid, 1);

                printf("Fils %d: tour %d, decision: %d\n", i, j, decision);

                P(semid, 2);
                printf("Fils %d: fin au tour %d, score: %d\n", i,j, tab_scores[i]);
                V(semid, 2);
                if (!decision) {
                    printf("Fils %d: bye\n", i);
                    shmdt(tab_decision);
                    shmdt(tab_scores);
                    shmdt(res);
                    exit(0);
                }
            }
            printf("Nombre de tours maximum atteint terminaison fils %d\n", i);
            exit(0);
        }
    }
    // pere
    printf("Pere commence\n");

    srand(getpid());

    int res_defi, j_enlice;

    j_enlice = 1;
    int j = 0;
    while (j_enlice && j < NT) {
        sleep_sec = (rand()%3)+1;
        sleep(sleep_sec);
        j_enlice = 0;

        P(semid, 0);
        res_defi = rand()%2;
        V(semid, 0);

        P(semid, 1)
        for(int i = 0; i < NP; i++) {
            if (res_defi == 1 && tab_decision[i] == 1) 
                tab_scores[i] = i, j_enlice++;
            else if (tab_decision[i] == 1)
                tab_scores[i] = 0;
        }
        arg.val = -NB+1
        semctl(semid, 1, SETVAL,arg)
        printf("Pere: tour %d, resultat %d\n", j, res_defi); 
        j++;
    }

    shmdt(tab_decision);
    shmdt(tab_scores);
    shmdt(res);
    shmctl(decision_shmid, IPC_RMID, NULL);
    shmctl(res_shmid, IPC_RMID, NULL);
    shmctl(scores_shmid, IPC_RMID, NULL);
    semctl(semid, IPC_RMID, NULL);
    printf("Pere terminaison");
    return 0;
}
