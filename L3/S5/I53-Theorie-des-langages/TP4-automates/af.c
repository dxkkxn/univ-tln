/*
  I53 Compilation et théorie des langages
  Nicolas Méloni
  28 - 10 -2019
 */
#include <stdio.h>
#include "afd.h"
#include "afn.h"

int main(int argc, char *argv[])
{
  /*
  afd A, B;
  char alphabet[] = "ab";
  uint finals[2] = {1,4};
  
  afd_init(&A, 5, alphabet, 2, 1, finals);
  
  afd_add_trans(&A, 1, 'a', 2);
  afd_add_trans(&A, 1, 'b', 1);
  afd_add_trans(&A, 2, 'a', 3);
  afd_add_trans(&A, 2, 'b', 1);
  afd_add_trans(&A, 3, 'a', 4);
  afd_add_trans(&A, 3, 'b', 1);
  afd_add_trans(&A, 4, 'a', 4);
  afd_add_trans(&A, 4, 'b', 4);

  afd_print(A);


  printf("%d\n", afd_simul(argv[1],B)); 
  afd_free(&B);
  afd_free(&A);

  afn A;
  afn_char(&A,'a');
  afn B;
  afn_char(&B, 'b');

  afn C;
  afn_union(&C, A, B);

  printf("A - > \n");
  afn_print(A);
  printf("B - > \n");
  afn_print(B);
  printf("A U B - > \n");
  afn_print(C);

  afn D;
  afn_char(&D, 'd');
  printf("D - > \n");
  afn_print(D);
  
  afn res;
  afn_union(&res, D, C);
  printf("D U A U B");
  afn_print(res);
  afn A;
  afn_char(&A, 'a');
  afn B;
  afn_char(&B, 'b');
  afn C;
  afn_concat(&C, A, B);
  afn_print(C);
  */
  
  // test
  afn A;
  afn_finit(&A, "test2.afn");
  afn C;
  afn_kleene(&C, A);
  afn_print(A);
  afn_print(C);
  afn_free(&A);
  afn_free(&C);

  /* afn A; */
  /* afd D; */
  /* afn_finit(&A, "example-2pown.afn"); */
  /* afn_determinisation(A, &D); */
  /* afd_print(D); */
  /* afn_free(&A); */
  /* afd_free(&D); */

  /* afd B; */
  /* printf("\n"); */
  /* afd_finit(&B, "exemple.afd"); */
  /* afd_print(B); */
  return 0;
}


