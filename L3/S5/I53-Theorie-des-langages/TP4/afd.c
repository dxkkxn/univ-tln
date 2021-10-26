#include "afd.h"
#define true 1
#define false 0

void afd_init(afd *A, uint nbetat, char * alphabet, uint nbfinal, uint init, uint *finals)
{
  int i, nbsymb=0;
  uchar symb;
  
  A->nbetat = nbetat;
  A->nbfinal = nbfinal;
  A->init = init;
  
  for (i=0; i<SYMB_NB_MAX; i++)
    A->tsymb[i] = SYMB_NONE;

  A->alphabet = malloc(strlen(alphabet)+1);
  strcpy(A->alphabet, alphabet);
  A->nbsymb = strlen(alphabet);
    
  while (*alphabet != '\0'){
    
    if ( (*alphabet < SYMB_ASCII_DEB) ||
	 (*alphabet > SYMB_ASCII_FIN) ){
      fprintf(stderr,"[afd_init] caractere ascii numero %d invalide\n", *alphabet);
      exit(-1);
    }
    
    symb = (uchar) (*alphabet - SYMB_ASCII_DEB);
    if ( A->tsymb[symb] != SYMB_NONE ){
      fprintf(stderr,"[afd_init] caractere <%c> deja defini (ignorer)\n",symb);
    }
    else {
      A->tsymb[symb] = nbsymb;
      nbsymb++;
    }
    alphabet++;
  }

  A->finals = calloc(nbfinal, sizeof(uint));
  for (i=0; i < nbfinal; i++){
    A->finals[i] = finals[i];
  }

  int j;
  A->delta = calloc(nbetat, sizeof(uint *));
  for (i=0; i<nbetat; i++){
    A->delta[i] = calloc(A->nbsymb, sizeof(uint));
    for (j=0; j<A->nbsymb; j++)
      A->delta[i][j] = ETAT_NONE;
  }
}

void afd_free(afd *A)
{
  int i;
  free(A->finals);
  free(A->alphabet);
  for (i=0; i<A->nbetat; i++)
    free(A->delta[i]);
  free(A->delta);
}

void afd_add_trans(afd *A, uint q1, uint s, uint q2)
{
  uchar symb = A->tsymb[s-SYMB_ASCII_DEB];

  if (symb == SYMB_NONE){
    fprintf(stderr, "[add_trans] %u -- %c --> %u\n", q1,s,q2);
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

  A->delta[q1][symb] = q2;
}

void afd_copy(afd *dest, afd *src)
{
  dest->nbetat = src->nbetat;
  dest->nbsymb = src->nbsymb;
  dest->nbfinal = src->nbfinal;
  dest->init = src->init;

  dest->alphabet = calloc(src->nbsymb, sizeof(char));
  strcpy(dest->alphabet, src->alphabet);

  memcpy(dest->tsymb, src->tsymb,SYMB_NB_MAX);

  int size = (src->nbetat-1)/ULLONG_BIT+1;
  dest->finals = calloc(sizeof(ullong),size);
  memcpy(dest->finals, src->finals, sizeof(ullong)*size);

  int i;
  dest->delta = calloc(src->nbetat, sizeof(uint *));
  for (i=0; i<src->nbetat; i++){
    dest->delta[i] = calloc(src->nbsymb, sizeof(uint));
    memcpy(dest->delta[i], src->delta[i], sizeof(uint)*src->nbsymb);
  }
}

void afd_print(afd A)
{
  int i,j;
  
  printf("etat initial: %d\n", A.init);
  printf("etats finals:");

  for (i=0; i< ((A.nbetat-1)/ULLONG_BIT)+1; i++){
    
    for (j=0; j<ULLONG_BIT; j++){
      if ((1ULL<<j) & A.finals[i])
	printf(" %lu", i*ULLONG_BIT+j);
    }
  }
  printf("\n");

  uint q;
  int printed;
  
  for (q=0; q<A.nbetat; q++){
    printed = 0;
    for (i=0; i<A.nbsymb; i++){
      if (A.delta[q][i]!=ETAT_NONE){
	if (printed==1)
	  printf("    ");
	else
	  printf("%4u", q);
	printf(" -- %c --> %u\n", A.alphabet[i], A.delta[q][i]);
	printed=1;
      }
    }
    //if (printed==0) printf("\n");
  }
}

void afd_finit(afd *A, char *nomfichier) {
    FILE * f;
    if((f = fopen(nomfichier, "r")) == NULL){
        perror("fopen");
        exit(1);
    }
    uint nb_etat, nb_final, init, curr_final;
    char alphabet[128];
    uint* finals = calloc(nb_final, sizeof(uint));
    uint i = 0;
    fscanf(f, "%u %s %u\n", &nb_etat, alphabet, &nb_final);
    fscanf(f, "%u\n", &init);
    while(i<nb_final) {
        fscanf(f, "%u", &curr_final);
        finals[i] = curr_final;
        i++;
    }
    afd_init(A, nb_etat, alphabet, nb_final, init, finals);

    uint state_i; //state i
    uint state_j; //state j
    uchar symb;
    // statei symb statej
    while(fscanf(f, "%u %c %u", &state_i, &symb, &state_j) == 3) {
        afd_add_trans(A, state_i, symb, state_j);
    }
}  

int afd_simul(char *s, afd A){
    uint curr_state = A.init;
    uint i = 0;
    char curr_char;
    while(i<strlen(s)) {
        curr_char = s[i];
        curr_state = A.delta[curr_state][A.tsymb[curr_char-SYMB_ASCII_DEB]];
        i++;
    }
    
    uint res = false;
    for(i = 0; i < A.nbfinal && res == false; i++) 
        res = (curr_state == A.finals[i]);
    return res;
}
