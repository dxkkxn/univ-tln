#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

// Implementation de l'exponentiation modulaire
void exp_mod(mpz_t result, const mpz_t base, const mpz_t exp, const mpz_t mod)
{
  mpz_t base_copy, exp_copy;
  mpz_init_set(base_copy, base);          // Creation des copies des parametres
  mpz_init_set(exp_copy, exp);            // pour eviter sa modification
  mpz_init_set_ui(result, 1);
  while (mpz_cmp_d(exp_copy, 0))
  {
    if (mpz_tstbit(exp_copy, 0))          //Verification du bit de poids faible
    {
      mpz_mul(result, result, base_copy);
      mpz_mod(result,result,mod);
    }
    mpz_mul(base_copy, base_copy, base_copy);  //Incrementation de la puissance
    mpz_mod(base_copy, base_copy, mod);

    mpz_fdiv_q_ui(exp_copy, exp_copy, 2);    // Decalage ver la droite d'un bit

  }
  mpz_clears(base_copy, exp_copy, NULL);  //Liberation des copies des parametres
}


// generation aleatoire de p et g

void generation_of_p_and_g(mpz_t p, mpz_t g, int n)
{
  unsigned long seed;
  mpz_t p_moins1;
  mpz_init(p_moins1);
  gmp_randstate_t r;
  seed = time(NULL);
  gmp_randinit_default(r);
  gmp_randseed_ui(r, seed);

  //Calcul du noombre premier (p) du groupe Zp/Z

  while (mpz_sizeinbase(p,2) != n)
  {
    mpz_urandomb(p, r, n);
    mpz_setbit(p, n-1);
    mpz_nextprime(p, p);
  }

  //Calcul de generateur (g) != (0, 1, p-1)

  mpz_sub_ui(p_moins1, p, 1);       //p - 1
  do{
    //nombre aleatoire pris dans l'intervalle [0,p-2]
    mpz_urandomm(g, r, p_moins1);
  }while(mpz_cmp_d(g, 0) == 0 || mpz_cmp_d(g, 1) == 0);
  mpz_clear(p_moins1);
}


// Simulation le protocole d’échange de clés Diffie-Hellman
// entre un nombre m d’entités.
void key_exchange(int m, const mpz_t p, const mpz_t g)
{

  int seed, n;
  gmp_randstate_t r;
  seed = time(NULL);
  gmp_randinit_default(r);
  gmp_randseed_ui(r, seed);
  n = mpz_sizeinbase(p, 2);      //n = taille en bits de p

  // Génération d'un tableau des mpz de taille m
  mpz_t *tab;
  tab = (mpz_t *)malloc(sizeof(mpz_t)*m);

  // Génération des clés privés aléatoires à n bits et stockage sur le tableau
  for(int i = 0; i <= m; i++)
  {
    mpz_t a;
    mpz_init(a);

    do {
      mpz_urandomm(a, r, p);
      mpz_setbit(a, n-1);
    }while(mpz_cmp(a,p) >= 0);

    mpz_init_set(tab[i], a);
    mpz_clear(a);
  }

  // Simulation des changementes des clés (cyclique)
  mpz_t result, result_pre;
  mpz_inits(result, result_pre, NULL);

  for (int i = 0; i<m ; i++)
  {
    int j = i;
    mpz_set(result, g);
    printf("|        L'ENTITE %d OBTIENT LA CLÉ COMMUNE          |", (m-1+i)%m + 1);
    printf("\n=====================================================\n");
    for (int k = 0; k < m-1; k++)
    {
      mpz_set(result_pre, result);
      exp_mod(result, result, tab[j], p);
      gmp_printf("Entité %d envoie (%Zd^%Zd =) %Zd a Entité %d \n",
                    j+1, result_pre, tab[j], result, (j+1)%m + 1);
      j = (j + 1) % m;

    }
    mpz_set(result_pre, result);
    exp_mod(result, result, tab[j], p);
    gmp_printf("Entité %d effectue %Zd^%Zd et obtient la clé commune %Zd\n",
                j%m + 1, result_pre, tab[j], result );
    printf("\n=====================================================\n");
  }
  printf("\n=====================================================\n");
  mpz_clears(result, result_pre, NULL);

  for (int j = 0; j < m ; j++)
  {
    gmp_printf("La clé privée de l'entité %d = %Zd\n", j+1, tab[j]);
  }
  printf("=====================================================\n");
}


int main(){
  mpz_t p, g;
  mpz_inits(p, g, NULL);
  int n, m;
  printf("=====================================================\n");
  printf("|          ECHANGE DES CLES DIFFIE-HELLMAN          |");
  printf("\n=====================================================\n\n");
  printf("Saisissez la taille (en bits) du secret : ");
  scanf(" %d", &n);
  printf("Saisissez le nombre d'entités impliquées : ");
  scanf(" %d", &m);
  generation_of_p_and_g(p, g, n);
  gmp_printf("\nLes paramètres publics sont le générateur g = %Zd et le groupe Zp/Z, p = %Zd\n",
              g,p);
  printf("\n=====================================================\n");
  key_exchange(m, p, g);
  mpz_clears(p, g, NULL);

}
