#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>

void exp_mod(mpz_t result, const mpz_t base, const mpz_t exp, const mpz_t mod)
{
  // mpz_init(result);
  // mpz_set_ui(result,1)
  mpz_t base_copy, exp_copy;
  mpz_init_set(base_copy, base);
  mpz_init_set(exp_copy, exp);
  mpz_init_set_ui(result, 1);
  while (mpz_cmp_d(exp_copy, 0))
  {
    // if (exp & 1)
    // mpz_and()
    // flag = mpz_cmp_d(exp,1);
    if (mpz_tstbit(exp_copy, 0))
    {
      // result = (result * g) % mod;
      mpz_mul(result, result, base_copy);
      mpz_mod(result,result,mod);
    }
    // g *= g % mod;
    mpz_mul(base_copy, base_copy, base_copy);
    mpz_mod(base_copy, base_copy, mod);
    // exp >>= 1 ;
    mpz_fdiv_q_ui(exp_copy, exp_copy, 2);

  }
  mpz_clears(base_copy, exp_copy, NULL);
}

int main(){
  mpz_t a, b, mod, result;
  mpz_init_set_ui(a,84684654546);
  mpz_init_set_ui(b,54564456465465);
  mpz_init_set_ui(mod,8797);
  mpz_inits(result);
  mpz_powm(result, a, b, mod);
  gmp_printf ("%Zd exp %Zd mod %Zd %Zd\n", a, b, mod, result);
  exp_mod(result, a, b, mod);
  gmp_printf ("%Zd exp %Zd mod %Zd %Zd\n", a, b, mod, result);

}
