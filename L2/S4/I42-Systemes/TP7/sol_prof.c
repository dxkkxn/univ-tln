//EXO 1
//A partir de la définition: typedef int Semaphore[2], écrivez les fonctions suivantes:
/*
    initSem(Semaphore S, int N) qui initialise le tube S avec N caractères quelconques,
    P(Semaphore S) qui lit un caractère dans S,
    V(Semaphore S) qui écrit un caractère dans S.
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
 
typedef int Semaphore[2];
 
int initSemaphore(Semaphore S, int n)
{           
 int i, code;
 char c='a';
 
 if ((code = pipe(S)) == 0);
      for (i = 1; i <=n ; i++)
        write(S[1],&c,1);
 return(code);
}
 
void P(Semaphore S)
{
  char c ;
  read(S[0],&c,1);
}
 
void V(Semaphore S)
{
  char c='a' ;
  write(S[1],&c,1);
}

//EXO 2
// rien

//EXO 3
//Le programme suivant (exo3-testflag-squel.c) permet de représenter et d'afficher une combinaison d'options de lecture, écriture et exécution sous la forme d'un seul paramètre entier de la fonction afficheDroit(). Chaque option est représentée par une constante. Complétez les parties manquantes.
#include <stdio.h>
#include <stdlib.h>
 
#define LECTURE   2 
#define ECRITURE  4 
#define EXECUTION 8
 
typedef int droits;
 
void afficheDroit(droits D)
{
  if (D&LECTURE) printf("r"); else printf("-");
  if (D&ECRITURE) printf("w"); else printf("-");
  if (D&EXECUTION) printf("x"); else printf("-");
  printf("\n");
}
 
int main(int argc, char **argv)
{
  /* Affiche les droits en lecture seules */
  afficheDroit(LECTURE);
  /* Affiche les droits en lecture et execution */
  afficheDroit(LECTURE|EXECUTION);
 
  /* Affiche les droits passes en parametres */
  if (argc > 1) afficheDroit(atoi(argv[1]));
  exit(0);
}

//EXO 4
/*Ecrire deux programmes ftok1.c et ftok2.c qui créent chacun une clé unique pour des objets représentés par les caractères 'A' et 'B' mais en utilisant le même nom de chemin.
Que se passe-t-il au niveau de la clé générée si l'on exécute deux fois ce programme ?
Que se passe-t-il au niveau de la clé générée si deux utilisateurs différents utilisent ce programme ?
Ecrire un programme ftok3.c qui crée une clé qui dépend de l'utilisateur qui exécute le programme (cf. la fonction getenv()).*/

/* ftok1.c */
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
 
int main(int argc, char * argv[])
{
  printf("ftok1\n");
  printf("  Ma cle A: %d \n",ftok("ftok1.c",'A'));
  printf("  Ma cle B: %d \n",ftok("ftok1.c",'B'));
  return 1;
}
/* ftok2.c */
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main(int argc, char * argv[])
{
  printf("ftok2\n");
  printf("  Ma cle A: %3d \n",ftok("ftok2.c",'A'));
  printf("  Ma cle B: %3d \n",ftok("ftok2.c",'B'));
  return 1;
}
/* ftok3.c */
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main(int argc, char * argv[])
{
  printf("ftok3\n");
  printf("  Ma cle A: %d \n",ftok(getenv("HOME"),'A'));
  printf("  Ma cle B: %d \n",ftok(getenv("HOME"),'B'));
  return 1;
}

//EXO 5
/*Ecrire un programme cree4sem.c qui crée un ensemble de quatre sémaphores. On s'assurera que la clé est unique sur le système en utilisant la fonction ftok(). On s'assurera qu'aucun groupe de sémaphores n'est associé à la clé.
Exécutez le programme et vérifiez la création de l'ensemble avec la commande ipcs.
Exécutez le programme une seconde fois.
Remettez le système dans son état initial en utilisant la commande ipcrm.*/

/*
* exemple d'utilisation de semget()
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define CLE 123
int main()
{
  int semid ; /* identificateur des semaphores */
   int cle;
  /*
   * allocation de quatre semaphores
   */
  if (( semid = semget(cle=ftok("cree4sem.c",(key_t)CLE), 4, 0600|IPC_CREAT|IPC_EXCL)) == -1) {
    perror("Echec de semget") ;
    exit(1) ;
  }
  printf(" le semid de l'ensemble de semaphore est : %d\n",semid) ;
  printf(" cet ensemble est identifie par la cle unique : %d\n",cle) ;
  exit(0);
}

//EXO 6
//En supposant qu'un sémaphore a déjà été créé (par l'exécution de l'exercice précédent), écrire un programme initsem.c qui met le troisième sémaphore de l'ensemble à 1, affiche la valeur du troisième sémaphore, affiche le pid du processus qui a effectué la dernière modification et finalement détruit l'ensemble de sémaphores.

/*
* exemple d'utilisation de semctl()
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define CLE 123
union semun {
  int val ;
  struct semid_ds *buf ;
  ushort array[4] ;
} arg ;
 
int main()
{
  int semid, val_sem ,val_pid;
  char *path = "cree4sem.c" ;
  /*
   * recuperation de l'identificateur
   * de l'ensemble de semaphores de cle 123
   */
  if (( semid = semget(ftok(path,(key_t)CLE),0,0)) == -1 ) {
    perror ("Semget()") ;
    exit(1) ;
  }
  printf("L'ensemble de semaphore a comme semid : %d\n",semid) ;
  printf("La cle d'acces est %d\n",ftok(path,(key_t)CLE)) ;
  /*
   * mise a 1 du
   * troisieme semaphore
   */
  arg.val = 1 ;
  if ( semctl(semid,2,SETVAL,arg) == -1){
    perror("Semctl()") ;
    exit(1) ;
  }
  /*
   * lecture du
   * troisieme semaphore
  */
  if ( (val_sem = semctl(semid,2,GETVAL,arg)) == -1){
    perror("Semctl()") ;
    exit(1) ;
  }
  else printf("la valeur du troisieme semaphore est : %d\n",val_sem) ;
  /*
   * lecture du pid du processus qui a
   * effectue la derniere operation
   */
  if (( val_pid = semctl(semid,2,GETPID,arg) )== -1){
    perror("Semctl()") ;
    exit(1) ;
  }
  else printf("la valeur du pid du processus qui a effectue la derniere operation est : %d,\nmon pid est :%d\n",val_pid,getpid()) ;
  /*
   * destruction du semaphore
   */
  if (semctl(semid,0,IPC_RMID,0)==-1){
    perror("impossible de detruire le semaphore") ;
    exit(1) ;
  }
  exit(0);
}

//EXO 7
//Ecrire un programme ressource.c qui crée un ensemble de sémaphores, fixe la valeur de l'un d'eux à 1, puis demande une ressource et se met en attente pendant 10 secondes puis libère la ressource.
/*
 * programme execute par le premier processus
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define CLE 123
int semid ;
struct sembuf operation[1] ;
char *path = "ressource.c" ;
union {
  int val ;
  struct semid_ds *buf ;
  ushort array[4] ; } arg ;
int main()
{
    /*
     * creation d'un ensemble de 4 semaphores
     */
    if (( semid = semget(ftok(path,(key_t)CLE),4,0600|IPC_CREAT))==-1){
      perror("impossible de creer l'ensemble de semaphores") ;
      exit(1) ;
    }
  printf("process1: je viens de creer un ensemble de semphore : %d\n",semid) ;
  /*
   * mise a 1 du troisieme semaphore
   */
  arg.val=1 ;
  if ((semctl(semid,2,SETVAL,arg))==-1){
    perror("semctl") ;
    exit(1);
  }
  /*
   * demande de ressource au troisieme semaphore
   */
  printf("process1: je vais demander une ressource\n") ;
  operation[0].sem_num = 2 ; /* operation sur le troisieme semaphore */
  operation[0].sem_op = -1 ; /* operation de decrementation */
  operation[0].sem_flg = SEM_UNDO; /* pour defaire les operations */
  if ( semop(semid,operation,1) == -1){
    perror("semop:operation de decrementation non effectuee") ;
    exit(1) ;
  }
  /*
   * attente pour bloquer le second processus
   */
  printf("process1: j'attends 10 sec\n") ;
  sleep(10) ; /* attente ... */
  printf("process1: j'ai fini d'attendre: je libere la ressource\n") ;
  /*
   * liberation de ressource
   */
   operation[0].sem_op = 1 ; /* incrementation */
  if ( semop(semid,operation,1) == -1){
    perror("semop:operation d'incrementation non effectuee") ;
    exit(1) ;
  }
    printf("mort de process1\n") ;
  exit(0) ;
}

//EXO 8
/*L'objectif de cet exercice est de simuler le fonctionnement d'une mine d'or. Cette mine est composée de mineurs, de pioches, de pelles et d'une seule caisse pour ranger l'or. Chaque mineur agit de la façon suivante:

il attend entre une et cinq heures avant de commencer,
il prend une pelle et une pioche,
il travaille entre une et cinq heures (des secondes dans la simulation) et extrait entre 1 et 1000 grammes d'or,
il rend sa pelle et sa pioche,
il ajoute l'or qu'il a extrait à la caisse.
Plusieurs mineurs peuvent travailler en même temps.

Dans cet exercice nous ne simulerons pas le remplissage de la caisse d'or.

Ecrire un programme C qui simule le fonctionnement de la mine sans la gestion de la caisse d'or.
Votre programme devra créer autant de processus fils qu'il y a de mineurs.

Rappel: Pour que le père attende la fin de ses fils, vous utiliserez le fait que la fonctions waitpid(-1, NULL, 0) retourne -1 quand un processus n'a plus de fils.*/
#include <unistd.h>
#include <time.h>
#include <wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>


#define CLE 1
#define CLE_MEM 2

int semid ;
int shmid ;
int *caisse;


struct sembuf operation[2] ;
char *path = "mineOr.c" ;

union {
  int val ;
  struct semid_ds *buf ;
  ushort array[3] ; } arg ;


void mineur(int numMineur) {
   srand((unsigned)time(NULL)*getpid());

  int qtOr = 0;
  int attenteAvantTravail = 1+(int) (5.0*rand()/(RAND_MAX+1.0));
  int dureeDeTravail = 1+(int) (5.0*rand()/(RAND_MAX+1.0));

  /* attente avant de se mettre au travail */
  printf("Le mineur %d attend %d heures avant de travailler.\n",numMineur,attenteAvantTravail);
  sleep(attenteAvantTravail);

  /* Prise de la pelle */
  operation[0].sem_num = 0 ;
  operation[0].sem_op = -1 ;
  operation[0].sem_flg = SEM_UNDO ;
  /* Prise de la pioche */
  operation[1].sem_num = 1 ;
  operation[1].sem_op = -1 ;
  operation[1].sem_flg = SEM_UNDO ;
  if (semop(semid,operation,2) == -1)
    perror("Erreur d'op<E9>ration sur le s<E9>maphore\n");
  printf("Le mineur %d prend une pelle et une pioche\n",numMineur);

  /* mise au travail */
  printf("Le mineur %d commence <E0> travailler pour %d heures.\n",numMineur,dureeDeTravail);
  sleep(dureeDeTravail);
  printf("Le mineur %d a extrait %d g d'or\n",numMineur,qtOr=1+(int) (1000.0*rand()/(RAND_MAX+1.0)));

 /* Remise de la pelle */
  operation[0].sem_num = 0 ;
  operation[0].sem_op = 1 ;
  operation[0].sem_flg = SEM_UNDO ;
  /* Remise de la pioche */
  operation[1].sem_num = 1 ;
  operation[1].sem_op = 1 ;
  operation[1].sem_flg = SEM_UNDO ;
  if (semop(semid,operation,2) == -1)
    perror("Erreur d'op<E9>ration sur le s<E9>maphore\n");
  printf("Le mineur %d rend une pelle et une pioche\n",numMineur);

  /* Prise de la caisse */
  operation[0].sem_num = 2 ;
  operation[0].sem_op = -1 ;
  operation[0].sem_flg = SEM_UNDO ;
  if (semop(semid,operation,2) == -1)
    perror("Erreur d'op<E9>ration sur le s<E9>maphore\n");
  *caisse = *caisse + qtOr;
  printf("Le mineur %d met %d g d'or dans la caisse\n",numMineur,qtOr);
  /* rendu de la caisse */
  operation[0].sem_num = 2 ;
  operation[0].sem_op = 1 ;
  operation[0].sem_flg = SEM_UNDO ;
  if (semop(semid,operation,2) == -1)
    perror("Erreur d'op<E9>ration sur le s<E9>maphore\n");
}

int main(int argc, char *argv[])
{
   if (argc<3) {
     printf("mineOr nbDeMineurs nbDePelles nbDePioches\n");
     exit(0);
   }

   int pid = getpid();
   int numMineur = 1;

   int nbDeMineurs = atoi(argv[1]);
   int nbDePelles = atoi(argv[2]);
   int nbDePioches = atoi(argv[3]);

    /*
     * creation d'un ensemble de deux semaphores pour repr<E9>senter
     * les pelles, les pioches et la quantite d'or.
     */
    if (( semid = semget(ftok(path,(key_t)CLE),4,0600|IPC_CREAT))==-1){
      perror("impossible de creer l'ensemble de semaphores") ;
      exit(1) ;
    }
    arg.val=nbDePelles ;
    if ((semctl(semid,0,SETVAL,arg))==-1){
      perror("Erreur d'initialisation") ;
      exit(1);
    }
    arg.val=nbDePioches ;
    if ((semctl(semid,1,SETVAL,arg))==-1){
      perror("Erreur d'initialisation") ;
      exit(1);
    }
    arg.val=1 ;
    if ((semctl(semid,2,SETVAL,arg))==-1){
       perror("Erreur d'initialisation") ;
      exit(1);
    }

    /* creation de la zone de memoire partagee qui represente
       la caisse */

 /*
   * recuperation du shmid
   */
  if (( shmid = shmget(ftok(path,(key_t)CLE_MEM), 4,IPC_CREAT|IPC_EXCL|SHM_R|SHM_W)) == -1) {
    perror("Echec de shmget") ;
    exit(1) ;
  }

/*
   * attachement du processus a la zone de memoire
   * recuperation du pointeur sur la zone memoire commune
   */
  if ((caisse = (int *)shmat (shmid, 0, 0)) == (int*)-1){
    perror("attachement impossible") ;
    exit (1) ;
  }

  *caisse = 0;

    while (numMineur<=nbDeMineurs) {
      pid = fork();
      if (pid == 0)
        {
          mineur(numMineur);
          exit(0);
        }
      else printf("cr<E9>ation du mineur %d (%d)\n",numMineur,pid);
      numMineur++;
    }

    while ((pid=waitpid(-1,NULL,0)) != -1)
      printf("Le mineur de pid %d a fini.\n",pid);
    printf("Fin du travail des mineurs, la caisse contient: %d g d'or.\n",*caisse);

 /*
   * detachement du segment
   */
  if (shmdt(caisse)== -1){
    perror("detachement impossible") ;
    exit(1) ;
  }

  /* Destruction du semaphore et de la memoire partagee */
  shmctl(shmid,IPC_RMID,NULL);
  semctl(semid,0,IPC_RMID,NULL);
  exit(0);
}

//EXO 9
/*Ecrire un programme testshm.c qui crée un segment de mémoire partagée avec ftok() et l'identificateur 123 (le second paramètre de ftok), puis affiche l'identificateur de segment et la clé unique.
Relancez le programme, vérifiez l'état du système avec la commande ipcs, remettez le système dans son état initial.*/
/*
 * exemple d'utilisation de shmget()
 */
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define CLE 123
int main()
{
  int shmid ; /* identificateur de la memoire commune */
  int size = 1000 ;
  char *path="testshm.c" ;
  if (( shmid = shmget(ftok(path,(key_t)CLE), size, IPC_CREAT|IPC_EXCL|SHM_R|SHM_W)) == -1) {
    perror("Echec de shmget") ;
    exit(1) ;
  }
  printf("identificateur du segment: %d \n",shmid) ;
  printf("ce segment est associe a la cle unique: %d\n",
         ftok(path,(key_t)CLE)) ;
  exit(0);
}
//EXO 10
//En supposant qu'un segment de mémoire partagée a été créé par le programme de l'exercice précédent, écrire un programme updateShm.c qui récupère l'identifiant du segment de mémoire partagée, affiche les informations suivantes: uid et gid du propriétaire, uid et gid du créateur, le mode d'accès, la taille de la zone mémoire, le pid du créateur et le pid du processus ayant fait la dernière opération et libère la mémoire partagée.

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define CLE 123
struct shmid_ds buf ;
int main()
{
  char *path = "testshm.c" ; /* ATTENTION la clé doit être la même que lors de la création du segment */
  int shmid ;
  int size = 1000 ;
  /* recuperation de l'identificateur du segment de memoire de cle 123 */
  if (( shmid = shmget(ftok(path,(key_t)CLE),size,0)) == -1 ) {
    perror ("Erreur shmget()") ;
    exit(1) ;
  }
  /* lecture du pid du processus qui a effectue la derniere operation*/
  if ( shmctl(shmid,IPC_STAT,&buf) == -1){
    perror("Erreur shmctl()") ;
    exit(1) ;
  }
  printf("ETAT DU SEGMENT DE MEMOIRE PARTAGEE %d\n",shmid) ;
  printf("identificateur de l'utilisateur proprietaire: %d\n",buf.shm_perm.uid) ;
  printf("identificateur du groupe proprietaire: %d\n",buf.shm_perm.gid) ;
  printf("identificateur de l'utilisateur createur: %d\n",buf.shm_perm.cuid) ;
  printf("identificateur du groupe createur: %d\n",buf.shm_perm.cgid) ;
  printf("mode d'acces: %d\n",buf.shm_perm.mode) ;
  printf("taille de la zone memoire: %d\n",buf.shm_segsz) ;
  printf("pid du createur: %d\n",buf.shm_cpid) ;
  printf("pid (derniere operation): %d\n",(int) buf.shm_lpid) ;
  /* destruction du segment */
  if ((shmctl(shmid, IPC_RMID, NULL)) == -1){
    perror("Erreur shmctl()") ;
    exit(1) ;
  }
  exit(0);
}
//EXO 11
/*Nous allons nous intéresser au problème classique du producteur-consommateur (client/serveur). Ecrire deux programmes: le premier shm-ecrit s'attache à un segment de mémoire déjà créé et écrit un nombre aléatoire à l'intérieur, le second shm-lit se connecte au même segment et affiche son pid et le nombre lu, puis le premier programme place un autre entier aléatoire …
Que se passe-t-il si le second programme est exécuté plusieurs fois ?*/

/* shm-ecrit.c */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define CLE 123

int main()
{
  int shmid ; /* identificateur de la memoire commune */
  int size = 1000 ; /* taille en octet de la memoire */
  char *path="shm-ecrit.c";
  char *mem ; /* pointeur sur la zone commune */
  int flag = 0 ; /* drapeau associe au segment */

  /*
   * recuperation du shmid
   */
  if (( shmid = shmget(ftok(path,(key_t)CLE), size,IPC_CREAT|0666)) == -1) {
    perror("Echec de shmget") ;
    exit(1) ;
  }
  printf("identificateur du segment: %d \n",shmid) ;
  printf("ce segment est associe a la cle unique: %d\n",
         ftok(path,(key_t)CLE)) ;
  /*
   * attachement du processus a la zone de memoire
   * recuperation du pointeur sur la zone memoire commune
   */
  if ((mem = shmat (shmid, 0, flag)) == (char*)-1){
    perror("attachement impossible") ;
    exit (1) ;
  }

  /*
   * ecriture dans la zone de memoire partagee
   */
  strcpy(mem,"Ceci est ecrit en memoire commune") ;

  /*
   * detachement du segment
   */
  if (shmdt(mem)== -1){
    perror("detachement impossible") ;
    exit(1) ;
  }
  exit(0);
}

//EXO 12 
/*Dans un exercice précédent, nous avons modélisé une mine d'or avec des processus parallèles, nous allons y ajouter la gestion de la caisse d'or.

La gestion de la caisse d'or (représentée par un entier) est faite en utilisant la mémoire partagée. Modifier le programme précédent pour que le processus père crée un segment de mémoire partagée de 4 octets. Chaque mineur pourra alors ajouter la quantité d'or extrait à l'or déjà présent dans la caisse.
Attention: il faudra vous assurer qu'un seul mineur ne met à jour la caisse en même temps.
A la fin de l'exécution, le processus père devra afficher le poids total de l'or contenu dans la caisse.*/
#include <unistd.h>
#include <time.h>
#include <wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>


#define CLE 1
#define CLE_MEM 2

int semid ;
int shmid ;
int *caisse;


struct sembuf operation[2] ;
char *path = "mineOr.c" ;

union {
  int val ;
  struct semid_ds *buf ;
  ushort array[3] ; } arg ;


void mineur(int numMineur) {
   srand((unsigned)time(NULL)*getpid());

  int qtOr = 0;
  int attenteAvantTravail = 1+(int) (5.0*rand()/(RAND_MAX+1.0));
  int dureeDeTravail = 1+(int) (5.0*rand()/(RAND_MAX+1.0));

  /* attente avant de se mettre au travail */
  printf("Le mineur %d attend %d heures avant de travailler.\n",numMineur,attenteAvantTravail);
  sleep(attenteAvantTravail);

  /* Prise de la pelle */
  operation[0].sem_num = 0 ;
  operation[0].sem_op = -1 ;
  operation[0].sem_flg = SEM_UNDO ;
  /* Prise de la pioche */
  operation[1].sem_num = 1 ;
  operation[1].sem_op = -1 ;
  operation[1].sem_flg = SEM_UNDO ;
  if (semop(semid,operation,2) == -1)
    perror("Erreur d'op<E9>ration sur le s<E9>maphore\n");
  printf("Le mineur %d prend une pelle et une pioche\n",numMineur);

  /* mise au travail */
  printf("Le mineur %d commence <E0> travailler pour %d heures.\n",numMineur,dureeDeTravail);
  sleep(dureeDeTravail);
  printf("Le mineur %d a extrait %d g d'or\n",numMineur,qtOr=1+(int) (1000.0*rand()/(RAND_MAX+1.0)));

  /* Remise de la pelle */
  operation[0].sem_num = 0 ;
  operation[0].sem_op = 1 ;
  operation[0].sem_flg = SEM_UNDO ;
  /* Remise de la pioche */
  operation[1].sem_num = 1 ;
  operation[1].sem_op = 1 ;
  operation[1].sem_flg = SEM_UNDO ;
  if (semop(semid,operation,2) == -1)
    perror("Erreur d'op<E9>ration sur le s<E9>maphore\n");
  printf("Le mineur %d rend une pelle et une pioche\n",numMineur);

  /* Prise de la caisse */
  operation[0].sem_num = 2 ;
  operation[0].sem_op = -1 ;
  operation[0].sem_flg = SEM_UNDO ;
  if (semop(semid,operation,2) == -1)
    perror("Erreur d'op<E9>ration sur le s<E9>maphore\n");
  *caisse = *caisse + qtOr;
  printf("Le mineur %d met %d g d'or dans la caisse\n",numMineur,qtOr);
  /* rendu de la caisse */
  operation[0].sem_num = 2 ;
  operation[0].sem_op = 1 ;
  operation[0].sem_flg = SEM_UNDO ;
  if (semop(semid,operation,2) == -1)
    perror("Erreur d'op<E9>ration sur le s<E9>maphore\n");
}

int main(int argc, char *argv[])
{
   if (argc<3) {
     printf("mineOr nbDeMineurs nbDePelles nbDePioches\n");
     exit(0);
   }

   int pid = getpid();
   int numMineur = 1;
    int nbDeMineurs = atoi(argv[1]);
   int nbDePelles = atoi(argv[2]);
   int nbDePioches = atoi(argv[3]);

    /*
     * creation d'un ensemble de deux semaphores pour repr<E9>senter
     * les pelles, les pioches et la quantite d'or.
     */
    if (( semid = semget(ftok(path,(key_t)CLE),4,0600|IPC_CREAT))==-1){
      perror("impossible de creer l'ensemble de semaphores") ;
      exit(1) ;
    }
    arg.val=nbDePelles ;
    if ((semctl(semid,0,SETVAL,arg))==-1){
      perror("Erreur d'initialisation") ;
      exit(1);
    }
    arg.val=nbDePioches ;
    if ((semctl(semid,1,SETVAL,arg))==-1){
      perror("Erreur d'initialisation") ;
      exit(1);
    }
    arg.val=1 ;
    if ((semctl(semid,2,SETVAL,arg))==-1){
      perror("Erreur d'initialisation") ;
      exit(1);
    }

    /* creation de la zone de memoire partagee qui represente
       la caisse */

 /*
   * recuperation du shmid
   */
  if (( shmid = shmget(ftok(path,(key_t)CLE_MEM), 4,IPC_CREAT|IPC_EXCL|SHM_R|SHM_W)) == -1) {
    perror("Echec de shmget") ;
    exit(1) ;
  }

/*
   * attachement du processus a la zone de memoire
   * recuperation du pointeur sur la zone memoire commune
   */
  if ((caisse = (int *)shmat (shmid, 0, 0)) == (int*)-1){
    perror("attachement impossible") ;
    exit (1) ;
  }

  *caisse = 0;

     while (numMineur<=nbDeMineurs) {
      pid = fork();
      if (pid == 0)
        {
          mineur(numMineur);
          exit(0);
        }
      else printf("cr<E9>ation du mineur %d (%d)\n",numMineur,pid);
      numMineur++;
    }

    while ((pid=waitpid(-1,NULL,0)) != -1)
      printf("Le mineur de pid %d a fini.\n",pid);



    printf("Fin du travail des mineurs, la caisse contient: %d g d'or.\n",*caisse);

 /*
   * detachement du segment
   */
  if (shmdt(caisse)== -1){
    perror("detachement impossible") ;
    exit(1) ;
  }
  /* Destruction du semaphore et de la memoire partagee */
  shmctl(shmid,IPC_RMID,NULL);
  semctl(semid,0,IPC_RMID,NULL);
  exit(0);
}
//EXO 13
//Ecrire un jeu de bataille navale en mémoire partagée pour deux joueurs. Chaque joueur lancera une instance du programme, un paramètre sur la ligne de commande indiquera s'il s'agit du joueur1 ou du joueur2. Le squelette des sources et des explications complémentaires (dans le squelette) se trouvent dans le fichier suivant 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
 
/* A VOIR
   union semun {
   int val ;
   struct semid_ds *buf ;
   ushort *array ;
   } arg_ctl ;
*/
 
/* Une seul groupe de sémaphore dans ce programme */
/* Nous garderons l'ID en global */
key_t SEMID;
 
void sem_create(key_t cle, int semNum) /* creation d'un ensemble de semaphores relie a cle */
{
  int semid ;
  semid = semget(ftok("bataille.c",cle),semNum,IPC_CREAT|IPC_EXCL|0666) ;
  if (semid == -1) {
    semid = semget(ftok("bataille.c",cle),semNum,IPC_EXCL|0666) ;
    if (semid == -1) {
      perror("Erreur semget()") ;
      exit(1) ;      
    }
  }
  SEMID = semid ;
}
 
void init_sem(int SemNum, int initval)
{
  union semun {
    int val ;
    struct semid_ds *buf ;
    ushort *array ;
  } arg_ctl ;
 
  arg_ctl.val = initval ;
  if (semctl(SEMID,SemNum,SETVAL,arg_ctl) == -1) {
    perror("Erreur initialisation semaphore") ;
    exit(1) ;
  }
}
 
void P(int sem)
{
  struct sembuf sempar ;
  sempar.sem_num = sem ;
  sempar.sem_op = -1 ;
  sempar.sem_flg = SEM_UNDO ;
  if (semop(SEMID, &sempar, 1) == -1)
    perror("Erreur operation P") ;
}
 
void V(int sem)
{
  struct sembuf sempar ;
  sempar.sem_num = sem ;
  sempar.sem_op = 1 ;
  sempar.sem_flg = SEM_UNDO ;
  if (semop(SEMID, &sempar, 1) == -1)
    perror("Erreur operation V") ;
}
 
void sem_delete()
{
  if (semctl(SEMID,0,IPC_RMID,0) == -1)
    perror("Erreur dans destruction semaphore") ;
}
 
int main (int argc, char* argv[]){
  typedef int booleen;
#define faux 0
#define vrai 1 
#define S0   0 /* semaphore 0 du groupe */
#define S1   1
#define S2   2
#define NBBAT 5 /* Nombre de bateaux */
#define RATE 1
#define COULE 2
 
#define CLE 123
 
  char *path="bataille.c";
 
  char Bat [NBBAT][NBBAT]; /* Mes bateaux */
  char BatA [NBBAT][NBBAT]; /* Mes bateaux */
 
  int i,j,N;
  int NumM;
  typedef struct {
    int R; /* Résultat du tir précédent */
    int X; /* Nouveau tir */
    int Y;
  } Tir;
 
  Tir *pTir;
  int X, Y;
  int Fin = faux;
  int param = atoi (argv[1]);
 
  int NBCAdv = 0; /* Nb de bateaux adverses coulés */
  int NBC = 0;
 
  printf("Bataille navale\n");
 
  for (i=0; i<NBBAT; i++){
    for (j=0; j<NBBAT; j++){
      Bat[i][j] = '.';
      BatA[i][j] = '.';
    }
  }
 
  srand(getpid());
  N=NBBAT;
  while (N>0) {
    i = rand() % NBBAT;
    j = rand() % NBBAT;
    if (Bat[i][j] == '.'){
      Bat[i][j]='B';
      N--;
    }
  }
 
  printf("Initialisation des bateaux OK\n");
 
  /* ### Exercice 1 ### */
  NumM = shmget (ftok(path,(key_t)CLE),sizeof(Tir), IPC_CREAT | 0666);
  printf("NumM %d\n", NumM);
  pTir = (Tir*) shmat (NumM, NULL, 0);
 
  sem_create(ftok(path,(key_t)CLE), 3);
 
  if (param == 1){
    printf("Joueur 1\n");
    pTir->R=0;
    init_sem(S0, 1);
    init_sem(S1, 0);
    init_sem(S2, 2);
  } else     printf("Joueur 2\n");
 
 
  P(S2); /* seulement deux joueurs */
 
  while (!Fin) {
    printf("En attente de l'autorisation de tir....\n");
    param == 1 ? P(S0) : P(S1);
    printf("OK\n");
 
    /* Résultat de mon tir précédent */
    switch (pTir->R) {
    case 0 :
      /* premier tir : pas de résultats */
      break;
    case RATE :
      if (BatA[X][Y] != 'C') BatA[X][Y] = 'R';
      printf("Mon tir raté en %d %d\n", X, Y);      
      break;
    case COULE :
      BatA[X][Y] = 'C';
      NBCAdv++;
      printf("Adversaire coul<E9> en %d %d, Nb de bateaux coulés: %d\n",X, Y,NBCAdv);
      if (NBCAdv == NBBAT) {
        Fin = 1;
        printf("Tous les bateaux adverses sont coulés\n");
      }
      break;
    }
 
    if (!Fin) {
      if (pTir->R == 0) {
        pTir->R = -1; /* de Resultat pour l'adversaire */
      }
      else if (Bat[pTir->X][pTir->Y] == 'B'){
        printf("== Mon bateau coulé en %d %d\n",pTir->X,pTir->Y);
 
        pTir->R = COULE;
        Bat[pTir->X][pTir->Y] = 'C';
        NBC++;
        if (NBC==NBBAT) {
          Fin = vrai;
          printf("Tous mes bateaux sont coulés.\n");
        }
    } else {
      if (Bat[pTir->X][pTir->Y] != 'C') {
        Bat[pTir->X][pTir->Y] = 'R';
      }
      printf("== Tir adverse raté en %d %d\n",pTir->X,pTir->Y);
      pTir->R = RATE;
    }
  }
 
  printf("\nMes bateaux         Adversaires\n\n");
  for(i=0; i<NBBAT; i++) {
    for(j=0; j<NBBAT;j++) printf("%c ",Bat[i][j]);
    printf("%10s", " ");
    for(j=0; j<NBBAT;j++) printf("%c ",BatA[i][j]);
    printf("\n");
  }
 
  printf("\nCoulés : %d         Coulés : %d\n",NBC, NBCAdv);
 
  if (!Fin) {
    printf("\n\n");
    printf("Tir en X Y ?");scanf("%d %d",&X, &Y);
    pTir->X = X;
    pTir->Y = Y;
  }
  param == 1 ? V(S1):V(S0);
  }
  if (param==1) sem_delete();
  exit(0);
}

//EXO 14
///* client */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>

#define CLE 123

typedef struct msg_struc {
  long mtype;
  long data;
} msg;

int main(void) {

  int pid; /* notre pid */
  msg message; /* une variable de type message */
  int msg_id;

  /* on recupere la file de message */
  msg_id = msgget(CLE, 0777);

  /* on recupere notre pid */
  pid = getpid();

  printf("Client de pid %d envoie un message\n", pid);

  /* preparation d'un message */
  message.mtype = 1;
  message.data = pid;

  /* envoie du message au serveur */
  msgsnd(msg_id, &message, sizeof(long), 0);

  printf("Client de pid %d, message envoyee\n", pid);

  /* on attend le message de retour */
  sleep(5);
  msgrcv(msg_id, &message, sizeof(long), (long) pid,0);

  printf("Client de pid %d, message de type %ld recu de %ld\n",pid, message.mtype, message.data);

  return 0;
}

/* serveur */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
 
#define CLE 123
 
int msg_id;
 
typedef struct msg_struc {
  long mtype;
  long data;
} msg;
 
void nettoie(int sig) {
  printf("Serveur: destruction de la file de message\n");
  msgctl(msg_id, IPC_RMID,0);
  exit(0);
}
 
int main(void) {
 
  int pid; /* notre pid */
  msg message; /* une variable de type message */
  long pid_client;
 
  /* prepare à nettoyer la file de message en quittant */
  signal(SIGINT, nettoie);
 
  /* on recupere la file de message */
  msg_id = msgget(CLE, 0777 | IPC_CREAT);
 
  /* on recupere notre pid */
  pid = getpid();
 
  printf("Serveur de pid %d en attente de messages\n", pid);
 
  while(1) {
    /* envoie du message au serveur */
    msgrcv(msg_id, &message, sizeof(long), 1,0);
 
    printf("Serveur de pid %d, message de type %ld recu de %ld\n", pid, message.mtype, message.data);
 
    /* on envoie le message de retour */
    /* avec comme contenu le pid du serveur */
    pid_client = message.data;
    message.mtype = pid_client;
    message.data = pid;
    msgsnd(msg_id, &message, sizeof(long),0);
 
    printf("Serveur de pid %d, message de type %ld envoye\n",pid, message.mtype);
  }
 
  return 0;
}

//EXO 15
/* serveur */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>
#include <time.h>
 
#define N 5
 
typedef struct msg_struc {
  long mtype;
  long data;
  int pid;
} msg;
 
int main(void) {
 
  int msg_id;
  msg message; /* une variable de type message */
  int i;
  int nb_fils_finis = 0;
  int somme[N];
  int pid[N]; /* notre pid */
 
  /* on initialise le tableau des sommes cumulees */
  for (i = 0; i < N; i++)
    somme[i] = 0;
 
  /* on recupere la file de message */
  msg_id = msgget(IPC_PRIVATE, 0777 | IPC_CREAT);
 
  for (i = 0; i < N; i++)  {
    if ((pid[i] = fork()) == 0) {
      int j, t;
      long v;
 
      /* processus fils (client) */
 
      srand(time(NULL)*getpid());
      for (j = 0; j < 10; j++) {
	/* tirage d'une valeur aleatoire */
	v = rand() % 10;
	message.mtype = i+1;
	message.data = (long) v;
	message.pid = getpid();
	msgsnd(msg_id, &message, sizeof(long)+sizeof(int), 0);
	printf("Client %d envoie de message de valeur %ld\n", getpid(), v);
	t = rand() % 2 + 1;
	sleep(t);
      }
      printf("Fin du client %d\n", getpid()); 
      message.mtype = N+1;
      msgsnd(msg_id, &message, sizeof(long)+sizeof(int), 0);
      exit(0);
    }
  }
  /* processus pere (serveur) */
 
  printf("Serveur de pid %d en attente de messages\n", getpid());
 
  while(nb_fils_finis != N) {
    /* envoie du message au serveur */
    msgrcv(msg_id, &message, sizeof(long)+sizeof(int), 0,0);
 
    printf("Serveur de pid %d, message de type %ld recu de %d avec la valeur %ld\n", getpid(), message.mtype, message.pid, message.data);
    if (message.mtype < N+1) {
      /* reception d'un message avec une valeur */
      somme[message.mtype-1] += message.data;
    }
    else {
      /* reception d'un message de terminaison d'un client */
      waitpid(message.pid, NULL,0);
      nb_fils_finis ++;
    }
  }
 
  printf("Sommes cumulees pour les clients\n");
  for (i = 0; i < N; i++)
    printf("  pid = %d  somme = %d\n", pid[i], somme[i]);
  printf("Serveur: destruction de la file de message\n");
  msgctl(msg_id, IPC_RMID,0);
  exit(0);
}

