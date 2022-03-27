#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

float PROB; 
int INTEN; 

bool in(int* arr, int size,  int x){
  for(int i = 0; i < size; i++){
    if(arr[i]==x)
      return true;
  }
  return false;
}

void print_arr(int *arr, int size){
  printf("[");
  for(int i = 0; i < size-1; i++){
    printf("%d, ", arr[i]);
  }
  printf("%d]\n", arr[size-1]);
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

uint32_t hamming(int v1, int v2) {
  return weight(v1^v2);
}

int* vecteur(int val, int size) {
  int *arr = calloc(size, sizeof(int));
  unsigned int y = 1<<(size-1);
  int i = 0;
  while(y){
    if(y&val){
      arr[i] = 1;
    } else {
      arr[i] = 0;
    }
    y >>= 1;
    i++;
  }
  return arr;
}

int valeur(int* vect) {
  int res = 0;
  for(int i = 31; i >= 0 ; i--) {
    if (vect[i]){
      res += pow(2, 31-i);
    }
  }
  return res;
}

int * encode(int* v, int lenv, int** g, int lencg, int lenlg) {
  assert(lenv == lenlg);
  int * res = calloc(lenv, sizeof(int));
  for(int i = 0; i <lencg; i++){
    int curr_res = 0;
    for(int j = 0; j < lenlg; j++) {
      curr_res ^= v[j] * g[j][i];
    }
    res[i] = curr_res;
  }
  return res;
}


int * control(int ** h, int lenc, int lenl, int * code, int len_code) {
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

int main(){
//  PROB = 0.75;
//  INTEN = 3;
//  srand(time(NULL));
//  int bruit_32 = bruite(32, 1.0, 4);
//  print_bits(32);
//  print_bits(bruit_32);
//  printf("%d\n", hamming(bruit_32, 32));
//  copie("example.txt", "out_example.txt");
//  print_arr(vecteur(32), 32);
//  printf("%d\n", valeur(vecteur(32)));
  int l0[6] = {1, 0, 0, 0, 1, 0};
  int l1[6] = {0, 1, 0, 0, 1, 0};
  int l2[6] = {0, 0, 1, 0, 0, 1};
  int l3[6] = {0, 0, 0, 1, 0, 1};
  int *G[4] = {l0, l1, l2, l3};
  int l4[6] = {1, 1, 0, 0, 1, 0};
  int l5[6] = {0, 0, 1, 1, 0, 1};
  int *H[2] = {l4, l5};
  int V[4] = {1, 0, 1, 1};
  int K = 4;
  int N = 6;
  for(int i = 0; i<pow(2, K); i++) {
      int* v = vecteur(i, K) ;
      int * encoded = encode(v, K, G, N, K);
      int * control_b = control(H, N, N-K, encoded, N);
//      print_arr(v, K);
//      print_arr(encoded, N);
      print_arr(encoded, N);
      free(v);
  }
  printf("\n\n");
  for(int i = 0; i<pow(2, N); i++) {
      int* v = vecteur(i, N) ;
      int * control_b = control(H, N, N-K, v, N);
//      print_arr(v, K);
//      print_arr(encoded, N);
      if (control_b[0]==0 && control_b[1] == 0){
        print_arr(v, N);
      }
      free(v);
  } 

}
