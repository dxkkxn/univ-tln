#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <gmp.h>

int main(void){
  int n;
  unsigned long seed;
  mpz_t a, b, c, p;
  gmp_randstate_t r;
  mpz_inits( a,  b,  c,  p, NULL);
  seed = time(NULL);

  printf("1 %lu\n", seed );
  gmp_randinit_default(r) ;
  // gmp_printf("2 %Zd", r);
  gmp_randseed_ui(r, seed);
  // gmp_printf("3 %Zd", r);
  printf("4 %lu\n", seed );
  // n = 256;
  // // generation d’un nombre premier de nbits
  // do{
  //   mpz_urandomb (p, r, n);
  //   mpz_setbit(p,n-1);
  //   mpz_nextprime (p, p);
  // } while (mpz_sizeinbase(p, 2) != n ) ;
  // // generation de deux nombres aleatoires inferieurs a p
  // mpz_urandomm(a, r, p);
  // mpz_urandomm(b, r, p);
  // gmp_printf ("\na = %Zd\n\n", a);
  // gmp_printf ("b = %Zd\n\n", b);
  // gmp_printf ("p = %Zd\n\n", p);
  // // addition
  // mpz_add (c, a, b);
  // gmp_printf ("addition, c = %Zd\n\n", c);
  // // soustraction
  // mpz_sub( c, a, b);
  // gmp_printf ( "soustraction, c = %Zd\n\n", c );
  // // multiplication puis reduction modulaire
  // mpz_mul ( c, a, b);
  // mpz_mod ( c, c, p);
  // gmp_printf ( " multiplication modulaire, c = %Zd\n\n" , c);
  // // exponentiation modulaire
  // mpz_powm ( c, a, b, p);
  // gmp_printf ( " exponentiation modulaire , c = %Zd\n\n", c);
  // mpz_clears ( a, b, c, p, NULL);
  // gmp_randclear ( r ) ;
  // return 0 ;
}
