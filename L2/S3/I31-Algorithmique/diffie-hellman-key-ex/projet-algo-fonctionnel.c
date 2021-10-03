#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

//Prend en paramètre un entier n et génère aléatoirement un nombre premier p de
//n bits ainsi qu’un élément g dans (Z/pZ)\{0, 1, p − 1}.
//Remarque : Comme expliqué plus haut, g devrait être une racine primitive modulo p.
//Pour ce projet, on se contentera d’un élément g différent de 0, 1 et p − 1.

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

void generation_of_p_and_g(mpz_t p, mpz_t g, int n)
{
  unsigned long seed;
  mpz_t p_moins1;
  mpz_init(p_moins1);
  gmp_randstate_t r;
  seed = time(NULL);
  gmp_randinit_default(r);
  gmp_randseed_ui(r, seed);
  //Calcul de p
  while (mpz_sizeinbase(p,2) != n)
  {
    mpz_urandomb(p, r, n);
    mpz_setbit(p, n-1);
    mpz_nextprime(p, p);
  }
  //Calcul de g != (0, 1, p-1)

  mpz_sub_ui(p_moins1, p, 2); //p - 1
  do{
    mpz_urandomm(g, r, p_moins1);
  }while(mpz_cmp_d(g, 0) == 0 || mpz_cmp_d(g, 1) == 0);
  mpz_clear(p_moins1);
}


// Simulation le protocole d’échange de clés Diffie-Hellman entre un nombre m
// d’entités. Par exemple : Entité_1 envoie X à Entité_2.
void echange_des_cles(int m, const mpz_t p, const mpz_t g)
{

  int seed, n;
  mpz_t* tab =(mpz_t *)malloc(sizeof(mpz_t)*m);
  gmp_randstate_t r;
  seed = time(NULL);
  gmp_randinit_default(r);
  gmp_randseed_ui(r, seed);
  n = mpz_sizeinbase(p, 2);
  for(int i = 0; i <= m; i++)
  {
    // generation des cles prives dans le groupe Zp/Z
    mpz_t a;
    mpz_init(a);
    do {
      mpz_urandomm(a, r, p);
      mpz_setbit(a, n-1);
    }while(mpz_cmp(a,p) >= 0);
    mpz_init_set(tab[i], a);
    mpz_clear(a);
  }
  mpz_t result, result_pre;
  mpz_inits(result, result_pre, NULL);
  for (int i = 0; i<m ; i++)
  {
    int j = i;
    mpz_set(result, g);
    for (int k = 0; k < m-1; k++)
    {
      mpz_set(result_pre, result);
      exp_mod(result, result, tab[j], p);
      gmp_printf("Entite %d envoie (%Zd^%Zd =) %Zd a Entite %d \n",
                    j+1, result_pre, tab[j], result, (j+1)%m + 1);
      j = (j + 1) % m;

    }
    mpz_set(result_pre, result);
    exp_mod(result, result, tab[j], p);
    gmp_printf("Entite %d effectue %Zd^%Zd et obtient a la cle commune %Zd\n",
                j%m + 1, result_pre, tab[j], result );
  }
  mpz_clears(result, result_pre, NULL);
  for (int j = 0; j < m ; j++)
  {
    gmp_printf("%d = %Zd\n", j+1, tab[j]);
    mpz_clear(tab[j]);
  }
  // free(tab);
}


int main(){
  // mpz_t a, b, mod, result;
  // mpz_init_set_ui(a,84684654546);
  // mpz_init_set_ui(b,54564456465465);
  // mpz_init_set_ui(mod,8797);
  // mpz_inits(result);
  // mpz_powm(result, a, b, mod);
  // gmp_printf ("%Zd exp %Zd mod %Zd %Zd\n", a, b, mod, result);
  // exp_mod(result, a, b, mod);
  // gmp_printf ("%Zd exp %Zd mod %Zd %Zd\n", a, b, mod, result);
  // mpz_t premier, gener;
  // mpz_inits(premier, gener, NULL);
  // generation_of_p_and_g(premier, gener, 8);
  // gmp_printf("premier = %Zd\ngener = %Zd \n", premier, gener);
  // echange_des_cles(3, premier, gener);
  mpz_t p, g;
  mpz_inits(p, g, NULL);
  int n, m;
  printf("Saisissez la taille (en bits) du secret : ");
  scanf(" %d", &n);
  printf("Saisissez les nombre d'entites impliquees : ");
  scanf(" %d", &m);
  generation_of_p_and_g(p, g, n);
  echange_des_cles(m, p, g);
  mpz_clears(p, g, NULL);

}
