#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#define K 4
#define N 7


void print_bits(int x, int n, bool b){
  unsigned int y = 1<<(n-1);
  while(y){
    if(y&x){
      printf("1");
    } else {
      printf("0");
    }
    y >>= 1;
  }
  if (b)
    printf("\n");
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

int dist_min(int * vects, int n) {
  int min = hamming(vects[0], vects[1]);
  for (int i = 0 ; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      if (i != j) {
        int curr_dist = hamming(vects[i], vects[j]);
        if (curr_dist < min)
          min = curr_dist;
      }
    }
  }
  return min;
}

int get_bit_at_index(int v, int i) {
  return v&(1<<i);
}

int encode(int v, int* g, int n) {
  int  res = 0;
  for(int i = 0; i < n; i++){
    res ^= (weight(v&g[i])%2)<<(n-i-1);
  }
  return res;
}

int control(int v, int * h, int n) {
  int res = 0;
  for(int i = 0; i < n; i++){
    res ^= (weight(v&h[i])%2)<<(n-i-1);
  }
  return res;
}


int indice_colonne(int* h, int n, int synd) {
  for (int i = 0; i < n; i++) {
    if (h[i] == synd)
      return n-i;
  }
  return -1;
}

int bruite_bit(int target, int i) {
  return target ^ (1<<i);
}

int correct(int v, int* H, int n) {
  int synd = control(v, H, n);
  if (synd != 0) {
    int index = indice_colonne(H, n, synd);
    v = bruite_bit(v, index);
  }
  return v;
}

int * transpose(int * h, int n) {

  for (int i )
}

/* int * decode (int *v, int k, int n) { */
/*   assert(k<=n); */
/*   int * res = calloc(k, sizeof(int)); */
/*   for(int i = 0; i < k; i++){ */
/*     res[i] = v[i]; */
/*   } */
/*   return res; */
/* } */


void test_bruite_bit() {
  int b = 31;
  print_bits(b, 10, true);
  print_bits(bruite_bit(b, 2), 10, true);
  print_bits(bruite_bit(b, 3), 10, true);
  print_bits(bruite_bit(b, 4), 10, true);
  print_bits(bruite_bit(b, 5), 10, true);
  print_bits(bruite_bit(b, 6), 10, true);
}

int main(){
  srand(time(NULL));
  /* int G[N] = {13, 10, 8, 7, 4, 2, 1}; */
  /* int H[N] = {1, 2, 3, 4, 5, 6, 7}; */
  /* int HL[N] = {15, 51, 85}; */

  int G[N] = {8, 4, 2, 1, 14, 7, 13};
  int H[N] = {5, 7, 6, 3, 4, 2, 1};
  int HL[N] = {116, 58, 105};
  printf("<mot a encoder> -> <vecteur original> - <syndrome original> -> <vecteur bruité> - <syndrome>\n");
  for(int i = 0; i<pow(2, K); i++) {
      int v = i;
      printf("<");
      print_bits(i, K, false);
      printf("> - ");
      int encoded = encode(v, G, N);
      int syndrome = control(encoded, HL, N-K);
      int bruited = bruite_bit(encoded, rand()%N);
      int syndrome_bruited = control(bruited, HL, N-K);
      int corrected = correct(bruited, HL, N-K);
      printf("<");
      print_bits(encoded, N, false);
      printf("> - <");
      print_bits(syndrome, N-K, false);
      printf("> - <");
      print_bits(bruited, N, false);
      printf("> - <");
      print_bits(syndrome_bruited, N-K, false);
      printf("> - <");
      print_bits(corrected, N, true);
  }
  /* test_bruite_bit(); */
}
