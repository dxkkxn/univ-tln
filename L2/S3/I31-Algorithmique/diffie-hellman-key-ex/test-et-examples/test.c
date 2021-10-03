#include <gmp.h>
#include <stdio.h>
#include <assert.h>



int main(){
  mpz_t number;
  mpz_init_set_ui(number, 7);
  gmp_printf("number = %Zd\n", number);
  mpz_setbit(number, 4);
  gmp_printf("number = %Zd\n", number);
  mpz_clrbit(number, 0);
  gmp_printf("number = %Zd\n", number);
}











// int main(){
//   mpz_t n, m, res, q;
//   mpz_inits(res, q, NULL);
//   mpz_init_set_ui(n,1);
//   mpz_init_set_ui(m,7);
//   mpz_and(res,n,m);
//   gmp_printf ("n = %Zd\n\n", n);
//   // mpz_out_str(stdout, m, 10);
//   gmp_printf ("m = %Zd\n\n", m);
//   // printf("n&m = ");
//   // mpz_out_str(stdout, res, 10);
//   gmp_printf ("res = %Zd\n\n", res);
//   printf("comp = %d\n", mpz_cmp(res,n));
//   if (mpz_cmp(res,n) == 0)
//     printf("OK\n");
//   while (mpz_cmp_d(m,0))
//   {
//     mpz_fdiv_q_ui(m,m,2);
//     gmp_printf ("m = %Zd\n", m);
//   }
//   mpz_clears(n,m,res, NULL);
// }

// int main(){
//
//   char inputStr[1024];
//   /*
//      mpz_t is the type defined for GMP integers.
//      It is a pointer to the internals of the GMP integer data structure
//    */
//   mpz_t n;
//   int flag;
//
//   printf ("Enter your number: ");
//   scanf("%1023s" , inputStr); /* NOTE: never every write a call scanf ("%s", inputStr);
//                                   You are leaving a security hole in your code. */
//
//   /* 1. Initialize the number */
//   mpz_init(n);
//   mpz_set_ui(n,0);
//
//   /* 2. Parse the input string as a base 10 number */
//   flag = mpz_set_str(n,inputStr, 10);
//   assert (flag == 0); /* If flag is not 0 then the operation failed */
//
//   /* Print n */
//   printf ("n = ");
//   mpz_out_str(stdout,10,n);
//   printf ("\n");
//
//   /* 3. Add one to the number */
//
//   mpz_add_ui(n,n,1); /* n = n + 1 */
//
//   /* 4. Print the result */
//
//   printf (" n +1 = ");
//   mpz_out_str(stdout,10,n);
//   printf ("\n");
//
//
//   /* 5. Square n+1 */
//
//   mpz_mul(n,n,n); /* n = n * n */
//
//
//   printf (" (n +1)^2 = ");
//   mpz_out_str(stdout,10,n);
//   printf ("\n");
//
//
//   /* 6. Clean up the mpz_t handles or else we will leak memory */
//   mpz_clear(n);
//
// }
