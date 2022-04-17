#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#define K 4
#define N 7

float PROB; 
int INTEN; 

bool in(int* arr, int size,  int x){
  for(int i = 0; i < size; i++){
    if(arr[i]==x)
      return true;
  }
  return false;
}

void print_arr(int *arr, int size, bool lf){
  printf("[");
  for(int i = 0; i < size-1; i++){
    printf("%d, ", arr[i]);
  }
  printf("%d]", arr[size-1]);
  if (lf)
    printf("\n");
}

void print_bits(int x){
  unsigned int y = 1<<31;
  while(y){
    if(y&x){
      printf("1");
    } else {
      printf("0");
    }
    y >>= 1;
  }
  printf("\n");
}

int bruite(int octet, float p, int n) {
  if ((float)rand() < p*(float)RAND_MAX) { 
    int * sel_bits= calloc(n, sizeof(int));
    int i = 0;
    while (i< n)  {
      int x = rand()%32;
      if (!in(sel_bits, n, x)) {
        sel_bits[i] = x;
        i++;
      }
    }
    //print_arr(sel_bits, n);
    for(int i = 0; i<n; i++){
      int aux = 1<<sel_bits[i];
      octet ^= aux;
    }
  }
  return octet;
}

int * copy_arr(int * arr, int n) {
  int * copy = calloc(n, sizeof(int));
  for (int i = 0; i < n; i++) {
    copy[i] = arr[i];
  }
  return copy;
}
int * bruite_bit(int* arr, int n, int i) {
  int * arr_copy =  copy_arr(arr, n);
  assert(arr_copy[i] == 0 || arr_copy[i] == 1);
  arr_copy[n-i-1] = !arr_copy[n-i-1];
  return arr_copy;
}
void copie(const char* in_fn, const char* out_fn) {
  FILE * in_file = fopen(in_fn, "r");
  FILE * out_file = fopen(out_fn, "w");
  int lettre;
  while((lettre = fgetc(in_file)) != EOF) {
    fputc(bruite(lettre, PROB, 4), out_file);
  }
  fclose(in_file);
  fclose(out_file);
  printf("Bruited file generated\n");
  return;
}

uint32_t weight(int x) {
  uint32_t res = 0;
  while(x) {
    if(x&1)
      res++;
    x >>= 1;
  }
  return res;
}

uint32_t weight_vect(int* x, int n) {
  uint32_t res = 0;
  for (int i = 0; i < n; i++) {
    if (x[i])
      res++;
  }
  return res;
}

int * diff_vect(int* v1, int* v2, int n) {
  int * res = calloc(n, sizeof(int));
  for (int i = 0; i < n; i++) {
    res[i] = v1[i]^v2[i];
  }
  return res;

}

uint32_t hamming(int v1, int v2) {
  return weight(v1^v2);
}
uint32_t hamming_vect(int * v1, int * v2, int n) {
  return weight_vect(diff_vect(v1, v2, n), n);
}

int dist_min(int ** vecteurs, int n_lines, int n_vect) {
  int min = hamming_vect(vecteurs[0], vecteurs[1], n_vect);
  for (int i = 0 ; i < n_lines; i++) {
    for (int j = i+1; j < n_lines; j++) {
      if (i != j) {
        int curr_dist = hamming_vect(vecteurs[i], vecteurs[j], n_vect);
        if (curr_dist < min)
          min = curr_dist;
      }
    }
  }
  return min;
}

int* vecteur(int val, int size) {
  int *arr = calloc(size, sizeof(int));
  unsigned int y = 1<<(size-1);
  int i = 0;
  while(y){
    if (y & val) {
      arr[i] = 1;
    } else {
      arr[i] = 0;
    }
    y >>= 1;
    i++;
  }
  return arr;
}

int valeur(int* vect, int n) {
  int res = 0;
  for(int i = n-1; i >= 0 ; i--) {
    if (vect[i]){
      res += pow(2, n-1-i);
    }
  }
  return res;
}

int * encode(int* v, int lenv, int** g, int lenlg, int lencg) {
  assert(lenv == lenlg);
  int * res = calloc(lencg, sizeof(int));
  for(int i = 0; i < lencg; i++){
    int curr_res = 0;
    for(int j = 0; j < lenlg; j++) {
      curr_res ^= v[j] * g[j][i];
    }
    res[i] = curr_res;
  }
  return res;
}


int * control(int ** h, int lenl, int lenc, int * code, int len_code) {
  assert(lenc == len_code);
  int * res = calloc(lenl, sizeof(int));
  for(int i = 0; i <lenl; i++){
    int curr_res = 0;
    for(int j = 0; j < lenc; j++) {
      curr_res ^= code[j] * h[i][j];
    }
    res[i] = curr_res;
  }
  return res;
}

void print_matrix(int ** matrix, int n_lines, int n_cols) {
  for(int i = 0; i < n_lines; i++) {
    print_arr(matrix[i], n_cols, true);
  }
}

int comp_arr(int* arr1, int n1, int * arr2, int n2) {
  assert(n1 == n2);
  for (int i = 0; i < n1; i++) {
    if (!(arr1[i] == arr2[i]))
      return false;
  }
  return true;
}
int indice_colonne(int** H, int sl, int sc, int * target, int size) {
  assert(size == sl);
  for (int i = 0; i < sc; i++) {
    bool error = false;
    int j;
    for (j = 0; j < sl && !error; j++) {
      if (!(target[j] == H[j][i]))
        error = true;
    }
    if (error == false)
      return i;
  }
  return -1;
}

int detect_error(int * v, int n) {
  for (int i = 0; i < n; i++) {
    if (v[i] != 0)
      return true;
  }
  return false;
}
int * correct(int * v, int sv, int** H, int sl, int sc) {
  int * syndrome = control(H, sl, sc, v, sv);
  /* print_arr(syndrome, sl, true); */
  int * copy = NULL;
  if (detect_error(syndrome, sc-sl)) {
    int index = indice_colonne(H, sl, sc, syndrome, sl);
    /* printf("index -> %d \n", index); */
    copy = bruite_bit(v, sv, sv-1-index);
  } else {
    copy = copy_arr(v, sv);
  }
  return copy;
}

int * decode (int *v, int k, int n) {
  assert(k<=n);
  int * res = calloc(k, sizeof(int));
  for(int i = 0; i < k; i++){
    res[i] = v[i];
  }
  return res;
}


int main(){
//  PROB = 0.75;
//  INTEN = 3;
  srand(time(NULL));
//  int bruit_32 = bruite(32, 1.0, 4);
//  print_bits(32);
//  print_bits(bruit_32);
//  printf("%d\n", hamming(bruit_32, 32));
//  copie("example.txt", "out_example.txt");
//  print_arr(vecteur(32), 32);
//  printf("%d\n", valeur(vecteur(32)));
  /* int l0[N] = {1, 0, 0, 0, 1, 0, 1}; */
  /* int l1[N] = {0, 1, 0, 0, 1, 1, 1}; */
  /* int l2[N] = {0, 0, 1, 0, 1, 1, 0}; */
  /* int l3[N] = {0, 0, 0, 1, 0, 1, 1}; */
  /* int *G[K] = {l0, l1, l2, l3}; */
  /* int l4[N] = {1, 1, 1, 0, 1, 0, 0}; */
  /* int l5[N] = {0, 1, 1, 1, 0, 1, 0}; */
  /* int l6[N] = {1, 1, 0, 1, 0, 0, 1}; */
  /* int *H[3] = {l4, l5, l6}; */
  int l0[N] = {1, 1, 1, 0, 0, 0, 0};
  int l1[N] = {1, 0, 0, 1, 1, 0, 0};
  int l2[N] = {0, 1, 0, 1, 0, 1, 0};
  int l3[N] = {1, 0, 0, 1, 0, 0, 1};
  int *G[K] = {l0, l1, l2, l3};
  int l4[N] = {0, 0, 0, 1, 1, 1, 1};
  int l5[N] = {0, 1, 1, 0, 0, 1, 1};
  int l6[N] = {1, 0, 1, 0, 1, 0, 1};
  int *H[3] = {l4, l5, l6};
  int V[4] = {0, 1, 1, 1};

  /* int ** encoded_matrix = calloc(pow(2, K), sizeof(int*)); */
  int * encoded = encode(V, K, G, K, N);
  printf("<vecteur original> - <syndrome original> -> <vecteur bruité> - syndrome\n");
  /* for(int i = 0; i<pow(2, K); i++) { */
  /*     int * v = vecteur(i, K) ; */
  /*     int * encoded = encode(v, K, G, K, N); */
  /*     int * syndrome = control(H, N-K, N, encoded, N); */
  /*     /\* int syndrome = valeur(control_b, N-K); *\/ */
  /*     /\* int index = sizes[syndrome]; *\/ */
  /*     int * b_arr = bruite_bit(encoded, N, rand()%N); */
  /*     int * syndrome_b = control(H, N-K, N, b_arr, N); */
  /*     /\* print_arr(encoded, N, true); *\/ */
  /*     /\* print_arr(b_arr, N, true); *\/ */
  /*     /\* printf("syndrome -> %d, index -> %d, N-K -> %d\n", syndrome, index, N-K); *\/ */
  /*     /\* equiv_class[syndrome][index] = v; *\/ */
  /*     /\* sizes[syndrome]++; *\/ */
  /*     printf("<"); */
  /*     print_arr(encoded, N, false); */
  /*     printf("> - "); */
  /*     printf("<"); */
  /*     print_arr(syndrome, N-K, false); */
  /*     printf("> - "); */
  /*     printf("<"); */
  /*     print_arr(b_arr, N, false); */
  /*     printf("> - "); */
  /*     printf("<"); */
  /*     print_arr(syndrome_b, N-K, false); */
  /*     printf(">\n"); */
  /*     printf("corrected -> "); */
  /*     int * corrected = correct(b_arr, N, H, N-K, N); */
  /*     print_arr(corrected, N, false); */
  /*     printf(" decode -> "); */
  /*     print_arr(decode(corrected, K, N), K, true); */
  /*     printf("\n\n"); */
  /*     /\* printf("> indice_col = %d \n", indice_colonne(H, N-K, N, syndrome_b, N-K)); *\/ */
  /*     /\* print_arr(control_b, 4); *\/ */
  /*     /\* encoded_matrix[i] = encoded; *\/ */
  /*     /\* free(v); *\/ */
  /* } */
  /* encoded_matrix[0][N-1] =  1; */
/*   print_matrix(encoded_matrix, pow(2,K)-1, N); */
/*   printf("dist_min = %d\n", dist_min(encoded_matrix, pow(2,K), N)); */
/* /\*   /\\* printf("dist_min = %d\n", dist_min(G, 4, N)); *\\/ *\/ */
/*   printf("\n\n"); */
/*   int *** equiv_class = calloc(pow(2, N-K), sizeof(int **)); */
/*   for (int i = 0; i < pow(2, N); i++) { */
/*     equiv_class[i] = calloc(pow(2, N), sizeof(int *)); */
/*   } */
  /* int * sizes = calloc(pow(2, N-K), sizeof(int)); */
  /* printf("%d\n", sizes[0]); */
  /* print_arr(sizes, pow(2, N-K)); */
  for(int i = 0; i<pow(2, N); i++) {
      /* int* v = vecteur(i, N) ; */
      /* int * syndrome = control(H, N, N-K, v, N); */
      /* /\* int syndrome = valeur(control_b, N-K); *\/ */
      /* /\* int index = sizes[syndrome]; *\/ */
      /* int * b_arr = bruite_bit(v, N, rand()%N); */
      /* int * syndrome_b = control(H, N, N-K, b_arr, N); */
      /* /\* printf("syndrome -> %d, index -> %d, N-K -> %d\n", syndrome, index, N-K); *\/ */
      /* /\* equiv_class[syndrome][index] = v; *\/ */
      /* /\* sizes[syndrome]++; *\/ */
      /* printf(">"); */
      /* print_arr(v, N, false); */
      /* printf("> - "); */
      /* printf(">"); */
      /* print_arr(syndrome, N-K, false); */
      /* printf("> - "); */
      /* printf(">"); */
      /* print_arr(b_arr, N, false); */
      /* printf("> - "); */
      /* printf(">"); */
      /* print_arr(syndrome_b, N-K, false); */
      /* printf(">"); */
     /* print_arr(encoded, N); */
      /* if (control_b[0] == 0 && control_b[1] == 0 && control_b[2] == 0){ */
      /*   print_arr(v, N); */
      /* } */
  }
  /* for(int i = 0; i < pow(2, N-K); i++) { */
  /*   print_arr(vecteur(i, N-K), N-K, false); */
  /*   for(int j = 0; j<sizes[i]; j++) { */
  /*     print_arr(equiv_class[i][j], N); */
  /*   } */
  /*   printf("\n\n"); */
  /* } */

  /* int l0[7] = {0, 0, 0, 0, 0, 0, 0}; */
  /* int l1[7] = {0, 0, 1, 0, 1, 1, 0}; */
  /* int l2[7] = {0, 1, 0, 0, 1, 1, 1}; */
  /* int l3[7] = {0, 1, 1, 0, 0, 0, 1}; */
  /* int l4[7] = {1, 0, 0, 0, 1, 0, 1}; */
  /* int l5[7] = {1, 0, 1, 0, 0, 1, 1}; */
  /* int l6[7] = {1, 1, 1, 1, 1, 1, 1}; */
  /* int *l[7] = {l0, l1, l2, l3, l4, l5, l6}; */
  /* for(int i = 0; i < 7; i++) { */
  /*   int * b_arr = bruite_bit(l[i], 7, i); */
  /*   print_arr(b_arr, 7); */
  /* } */
}
