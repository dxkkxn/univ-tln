#include "afn.h"
#include <assert.h>
#include <math.h>


void afn_init(afn *A, uint nbetat, char * alphabet, ullong init, ullong finals)
{
  A->nbetat = nbetat;

  A->alphabet = malloc(strlen(alphabet)+1);
  strcpy(A->alphabet, alphabet);
  A->nbsymb = strlen(alphabet);

  A->init = init;
  A->finals = finals;

  int i;
  uchar symb;

  for (i=0; i<SYMB_NB_MAX; i++)
    A->tsymb[i] = SYMB_NONE;

  for (i=0; i<A->nbsymb; i++){
    if ( (alphabet[i] < SYMB_ASCII_DEB) ||
	 (alphabet[i] > SYMB_ASCII_FIN) ){
      fprintf(stderr,"[afd_init] caractere ascii numero %d invalide\n", alphabet[i]);
      exit(-1);
    }
    symb = (uchar) (alphabet[i] - SYMB_ASCII_DEB);
    if ( A->tsymb[symb] != SYMB_NONE ){
      fprintf(stderr,"[afd_init] caractere <%c> deja defini (ignorer)\n",alphabet[i]);
    }
    else {
      A->tsymb[symb] = i;
    }
  }
  A->delta = calloc(nbetat, sizeof(ullong *));
  for (i=0; i<nbetat; i++){
    A->delta[i] = calloc(A->nbsymb, sizeof(ullong));
  }
}

  /*
  Ajoute la relation (<q1>, <s>, <q2>) a l'AFN <A>
*/
void afn_add_trans(afn *A, uint q1, uint s, uint q2)
{
  uchar symb = A->tsymb[s-SYMB_ASCII_DEB];

  if (symb == SYMB_NONE){
    fprintf(stderr, "[add_trans] %u -- %c --> %u symbole inconnu\n", q1,s,q2);
    exit(-1);
  }

  if ( (q1<0) || (q1>=A->nbetat) ){
   fprintf(stderr, "[add_trans] etat <%d> non reconnu\n", q1);
    exit(-1);
  }
  if ( (q2<0) || (q2>=A->nbetat) ){
   fprintf(stderr, "[add_trans] etat <%d> non reconnu\n", q2);
    exit(-1);
  }

  A->delta[q1][symb] |= INT_ETAT(q2);
}


/*
  Libere la memoire de l'AFN <A>
*/
void afn_free(afn *A)
{
  free(A->alphabet);

  int i;
  for (i=0; i < A->nbetat; i++)
    free(A->delta[i]);
  free(A->delta);
}


/*
  Affiche l'AFN <A>
*/
void afn_print(afn A){
  uint q,q1,s;
  printf("init:");
  for (q=0; q<A.nbetat; q++)
    {
      if IN(q,A.init)
	     printf(" %d",q);
    }
  printf("\n");
  printf("finals:");
  for (q=0; q<A.nbetat; q++)
    {
      if IN(q,A.finals)
	     printf(" %d",q);
    }
  printf("\n");
  for (q=0; q<A.nbetat; q++){
    for (s=0; s<A.nbsymb; s++){
      if (A.delta[q][s]!=0){
	printf("%d -- %c --> {", q, A.alphabet[s]);
	for (q1=0; q1<A.nbetat; q1++)
	  {
	    if (IN(q1, A.delta[q][s]))
	      printf("%d,",q1);
	  }
	printf("\b}\n");
      }
    }
  }
}



/*
  Initialise l'AFN <A> a partir des donnees du fichier <nomfichier> au
  format:

  nb_etats alphabet nbr_etats_initiaux nbr_etats_finals
  etat_initial....
  etats_finals....
  etat_i_11 symb_j_1 etat_i_12
  etat_i_21 symb_j_2 etat_i_22
  .
  .
  .
  etat_i_n1 symb_j_n etat_i_n2

*/
void afn_finit(afn *A, char *nomfichier) {
    FILE *f;
    uint nb_states;
    char alphabet[128];
    if ((f = fopen(nomfichier, "r")) == NULL) {
        perror("fopen");
        exit(1);
    }

    uint nb_st_init;
    uint nb_st_fin; 
    int r;
    r = fscanf(f, "%u %s %u %u", &nb_states, alphabet, &nb_st_init, &nb_st_fin);
    assert(r == 4);
    
    uint i;
    i = 0;
    ullong st_init = 0;
    ullong curr_st;
    while(i < nb_st_init) {
        fscanf(f, "%llu", &curr_st);
        st_init |= INT_ETAT(curr_st);
        i++;
    }
    

    i = 0;
    ullong st_fin = 0;
    while(i < nb_st_fin) {
        fscanf(f, "%llu", &curr_st);
        st_fin |= INT_ETAT(curr_st);
        i++;
    }
    
    afn_init(A, nb_states, alphabet, st_init, st_fin);

    uint st_i; //state_i
    uint st_j; //state_j
    char symb;
    printf("OK\n");
    while(fscanf(f, "%d %c %d\n", &st_i, &symb, &st_j) == 3) {
        printf("%d %c %d\n", st_i, symb, st_j);
        afn_add_trans(A, st_i, symb, st_j);
    }
}


/*
   Return 1 if (p,~,q) exists
   0 if not
*/
char exist_ep_trans(afn A, ullong q, ullong p) {
    return ((A.delta[q][A.tsymb['~'-SYMB_ASCII_DEB]]) & INT_ETAT(p));
}

    

/*
  Retourne l'epsilon fermeture de l'ensemble d'états <R> par
  l'automate <A>
*/
ullong afn_epsilon_fermeture(afn A, ullong R) {
  printf("R = %lld\n", R);
  uchar track[64];
  for(int i = 0; i < 64; i++) {
      track[i] = 0;
  }
  ullong stack[64];  
  uint top = -1;

  ullong next;
  ullong r = R; //copy of R
  uint st_i = 1;
  r = r>>1;
  while (r) {
      if (r & 1) {
          top++;
          stack[top] = st_i;
      }
      r = r >> 1;
      st_i++;
  }

  ullong ferm = R;
  ullong q;
  ullong q2;
  ullong Q;
  Q = INT_ETAT(A.nbetat) - 1;
  while (top != -1) {
      q = stack[top];
      top--;
      r = Q;
      r = r>>1;
      st_i = 1;
      while (r && track[q] == 0) {
          if (r&1) 
              q2 = st_i;

          printf("q=%lld q2=%lld\n",q, q2);
          if(exist_ep_trans(A, q, q2) ) {
              printf("EXISTS %lld\n", q2);
              ferm |= INT_ETAT(q2);
              top++;
              stack[top] = q2;
          }
          st_i++;
          r = r >> 1;
      }
      track[q] = 1;
  }
  return ferm;
}
  



      


/*
  Calcule un automate deterministe equivalent à <A> et affecte le
  resultat a <D>. Les etats de l'afd sont renumerotés à partir de 1
*/

uchar all_states_tracked(uchar *track, uchar size) {
    uchar res_ast = 1;
    for(uchar i = 0; i < size && res_ast; i++) {
        if(track[i] == 0) 
            res_ast = 0;
    }
    return res_ast;
}

uint wt(ullong n) {
    uint res = 0;
    while(n) {
        res++;
        n &= n-1;
    }
    return res;
}

void create_arr_Q(uchar * track, ullong Q) {
    track[0] = 1;
    Q = Q>>1;
    uchar st_i = 1;
    uint i = 1;
    while(Q) {
        if (Q&1){
            track[i] = st_i;
            i++;
        }
        st_i++;
        Q = Q>>1;
    }
void afn_determinisation(afn A, afd *D) {
    ullong Q = afn_epsilon_fermeture(A, A.init);
    uchar * track = calloc(wt(Q), sizeof(uchar));
    create_arr_Q(track, Q);
    uchar i = 0;
    while(all_states_tracked(track, wt(Q)) == 0) {
        track[i] = 1;
        char * sigma = A.alphabet;
        while(*sigma != '\0') {
            sigma++;
        }
    }
}




}
/*
  Calcule l'automate qui reconnait le caractere <c> dans un alphabet a
  <nbsymb> symboles
*/
void afn_char(afn *C, char c, uint nbsymb);

/*
  Calcule un automate qui reconnait l'union de <A> et <B>
*/
void afn_union(afn *C, afn A, afn B);

/*
  Calcule un automate qui reconnait la concatenation de <A> et <B>
*/
void afn_concat(afn *C, afn A, afn B);

/*
  Calcule un automate qui reconnait la fermeture de Kleene de <A>
*/
void afn_kleene(afn *C, afn A);
