#include "afn.h"
#include <assert.h>
#include <math.h>

char * ALPHABET = "&abcdefghijklmnopqrstuvwxyzABCDEFGHIJLMNOPQRSTVWXYZ0123456789";

void afn_init(afn *A, uint nbetat, char * alphabet, ullong init, ullong finals) {
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
void afn_add_trans(afn *A, uint q1, uint s, uint q2) {
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
void afn_free(afn *A) {
    free(A->alphabet);

    int i;
    for (i=0; i < A->nbetat; i++)
        free(A->delta[i]);
    free(A->delta);
}


/*
  Affiche l'AFN <A>
*/
void afn_print(afn A) {
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
  Return 1 if (p,c,q) exists
  0 if not
*/
char exist_trans(afn A, ullong q, char c, ullong p) {
    return ((A.delta[q][A.tsymb[c-SYMB_ASCII_DEB]]) & INT_ETAT(p));
}

void print_array(ullong* array, int n) {
	printf("[");
	for(int i = 0; i < n - 1; i++)
		printf("%lld,", array[i]);
	printf("%lld]\n", array[n-1]);
}
/*
  Retourne l'epsilon fermeture de l'ensemble d'états <R> par
  l'automate <A>
*/
ullong afn_epsilon_fermeture(afn A, ullong R) {
    uchar track[A.nbetat];
    for(uint i = 0; i < A.nbetat; i++) {
        track[i] = 0;
    }
    ullong stack[INT_ETAT(A.nbetat)-1];
    int top = -1;

    ullong r = R; //copy of R
    ullong temp;
    ullong state;
    while (r) {
        temp = r;
        r &= r - 1;
        state = log(temp^r)/log(2);
        top++;
        stack[top] = state;
    }
    ullong ferm = R;
    ullong q;
    ullong q2;
    while (top != -1) {
        q = stack[top];
        top--;
        q2 = 0;
        while (A.nbetat > q2 && track[q] == 0) {
            if(exist_trans(A, q, '&', q2) ) {
                ferm |= INT_ETAT(q2);
                top++;
                stack[top] = q2;
            }
            q2++;
        }
        track[q] = 1;
    }
    return ferm;
}
  
/*
  Calcule un automate deterministe equivalent à <A> et affecte le
  resultat a <D>. Les etats de l'afd sont renumerotés à partir de 1
*/

uchar all_states_marked(uchar *track, uchar size) {
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
        n &= n-1;
        res++;
    }
    return res;
}

int in(ullong * arr, uint size, ullong q) {
    bool is_in = false;
    for(uint i = 0; i < size && is_in == false; i++) {
        is_in = (arr[i] == q);
    }
    return is_in;
}

/* Takes un state and a character in parameter and */
/* returns all states where can go with that single parameter */
ullong simul(afn A, ullong states, char c) {
    ullong copy;
    ullong res = 0;
    ullong curr_state;
    while(states) {
        copy = states;
        states &= states -1;
        curr_state = log(states^copy)/log(2);

        for(uint i = 0; i < A.nbetat; i++) {
            if(exist_trans(A, curr_state, c, i))
                res |= INT_ETAT(i);
        }
    }
    return res;
}

uint indexof(ullong *arr, uint size, ullong target) {
    bool found = false;
    uint i;
    for(i = 0; i < size && found == false; i++) {
        if(arr[i] == target)
            found = true;
    }
    assert(arr[i-1]==target);
    return i-1;
}

void afn_determinisation(afn A, afd *D) {
    uint size_states_q  = 64;
    ullong * states_q = calloc(size_states_q, sizeof(ullong));
    uint size_of_trans = 64;
    trans_t * trans = calloc(size_of_trans, sizeof(trans_t));
    assert(trans != NULL);
    assert(states_q != NULL);
    states_q[0] = afn_epsilon_fermeture(A, A.init);
    // at most all the states are final so the size of finals is 64
    uint * finals = calloc(64, sizeof(uint));
    uint nb_finals = 0;

    uint nb_etats = 1;
    uint i = 0;
    ullong ferm;
    uint trans_i = 0;
    while(nb_etats > i) {
        printf("%lld %lld \n", states_q[i], A.finals);
        if(states_q[i] & A.finals) {
            finals[nb_finals] = i;
            nb_finals++;
        }
        char * sigma = A.alphabet;
        while(*sigma != '\0') {
            if (*sigma != '&') {
                ferm = afn_epsilon_fermeture(A, simul(A, states_q[i], *sigma));
                if(!in(states_q, nb_etats, ferm)) {
                    if(nb_etats >= size_states_q) {
                        size_states_q += 64;
                        states_q = realloc(states_q, size_states_q * sizeof(ullong));
                        assert(states_q != NULL);
                    }
                    states_q[nb_etats] = ferm;
                    nb_etats++;
                }
                trans_t new_trans = {i,*sigma, indexof(states_q, nb_etats, ferm)};
                if (trans_i >= size_of_trans) {
                    size_of_trans += 64;
                    trans = realloc(trans, size_of_trans * sizeof(trans_t));
                    assert(trans != NULL);
                }
                trans[trans_i] = new_trans;
                trans_i++;
            }
            sigma++;
        }
        i++;
    }
    afd_init(D, nb_etats, A.alphabet, nb_finals, 0, finals);
    for(i = 0; i< trans_i; i++) {
        afd_add_trans(D, trans[i].q, trans[i].c, trans[i].q2);
    }
}

/*
  Calcule l'automate qui reconnait le caractere <c> dans un alphabet a
  <nbsymb> symboles
*/
void afn_char(afn *C, char c) {
    afn_init(C, 2, ALPHABET, 1, 2);
    afn_add_trans(C, 0, c, 1);
}

/*
  Add all transitions of A to C starting at start in C
  i.e
  0 in A is start in B
  1 in b is start+1 in B
*/
void add_all_trans(afn *C, afn A, uint start) {
    ullong all_st_a = INT_ETAT(A.nbetat);
    ullong curr_state_i = 1, curr_state_j = 1;
    uint i = 0;
    ullong st_j, st_i;
    while (all_st_a > curr_state_i){
        curr_state_j = 1;
        st_i = log(curr_state_i)/log(2);
        while (all_st_a > curr_state_j) {
            i = 0;
            st_j = log(curr_state_j)/log(2);
            while(i < strlen(ALPHABET)) {
                if (exist_trans(A, st_i, ALPHABET[i], st_j)) {
                    afn_add_trans(C, st_i+start, ALPHABET[i], st_j+start);
                }
                i++;
            }
            curr_state_j <<=1;
        }
        curr_state_i <<= 1;
    }
}

/*
** Add & trans in C from 0 to all initial states of A
** renaming 0 in A to start ...
*/
void add_ep_trans(afn *C, afn A, uint start){
    ullong curr_st = 1;
    ullong st;
    while(A.init >= curr_st) {
        if (A.init & 1) {
            st = log(curr_st)/log(2);
            afn_add_trans(C, 0, '&', st+start);
        }
        curr_st <<= 1;
    }
}

/*
  Calcule un automate qui reconnait l'union de <A> et <B>
*/
void afn_union(afn *C, afn A, afn B) {
    uint nb_states = A.nbetat + B.nbetat;
    ullong fin_states = A.finals | B.finals;
    afn_init(C, nb_states + 1, ALPHABET, 1, fin_states);

    // add all trans of A to C
    add_all_trans(C, A, 1);
    // add all trabs of B to A
    add_all_trans(C, B, A.nbetat+1);
    // add ep trans from c->init to A
    add_ep_trans(C, A, 1);
    // add ep trans from c->init to A
    add_ep_trans(C, A, A.nbetat+1);
    // test
}

/*
  Calcule un automate qui reconnait la concatenation de <A> et <B>
*/
void afn_concat(afn *C, afn A, afn B) {
    afn_init(C,A.nbetat+B.nbetat, ALPHABET,A.init,B.finals);
    add_all_trans(C, A, 0);
    add_all_trans(C, B, A.nbetat);
    // for each final state of A add a ep trans to each initial
    // state of B
    ullong curr_stateb = 1;
    ullong curr_state = 0;
    ullong curr_statejb = 1;
    ullong curr_statej = 0;
    while (A.finals >= curr_state) {
        if (A.finals & curr_stateb) {
            // curr_state is a final state
            curr_statejb = 1;
            curr_statej = 0;
            while(B.init >= curr_statejb) {
                if (curr_statejb & B.init)
                    //
                    afn_add_trans(C,curr_state, '&', curr_statej+A.nbetat);
                curr_statejb <<= 1;
                curr_statej++;
            }
        }
        curr_stateb <<= 1;
        curr_state++;
    }
}

/*
  Calcule un automate qui reconnait la fermeture de Kleene de <A>
*/
void afn_kleene(afn *C, afn A) {
    afn_init(C, A.nbetat, A.alphabet, A.init, A.finals);
    add_all_trans(C, A, 0);
    ullong finals = A.finals;
    ullong initials;
    ullong temp;
    uint state_f;
    uint state_i;
    while(finals) {
       temp = finals;
       finals &= finals - 1;
       state_f = log(temp^finals)/log(2);
       initials = A.init;
       while(initials) {
           temp = initials;
           initials &= initials - 1;
           state_i = log(initials^temp)/log(2);
           afn_add_trans(C, state_f, '&', state_i);
       }
    }

}
