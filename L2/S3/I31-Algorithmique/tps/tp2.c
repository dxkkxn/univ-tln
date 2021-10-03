#include <stdio.h>

// EXO 1

/*
void main()
{
  printf("Entrez 2 nombres et un operateur (+,-,*,/,%) \n");

  int a, b, opnum;
  scanf("%d", &a);
  char op=getchar();
  scanf("%d", &b);
  rewind(stdin);
  do {
  switch (op)
    {
      case '+' :
        printf("%d\n",a+b);
        break;
      case '-' :
        printf("%d\n",a-b);
        break;
      case '*' :
        printf("%d\n",a*b);
        break;
      case '/' :
        printf("%d\n",a/b);
        break;
      case '%' :
        printf("%d\n",a%b);
        break;
      } while (x)
    }
}

*/
//EXO 2

/*
void main()
{
  int a, carre;
  carre = 0;
  printf("Entier un nombre : ");
  scanf("%d", &a);
  for(int i=1; carre <= a; i++)
    carre = i*i;
  printf("Le plus petit carre superieur a %d est %d \n", a, carre);
}
*/

//EXO3
/*
void main ()
{
  int n, cpt, nbou;
  printf("Entrez un nombre : ");
  scanf("%d",&n);
  nbou = n;
  cpt = 1;
  do {
      nbou = nbou/10;
      printf("%d\n", nbou);
      cpt += 1;
  } while ((nbou/10)!=0);
  printf("Le nombre des chiffres de %d est %d\n",n,cpt );
}
*/

//EXO4
/*
void main()
{
  int n, som_carre;
  printf("Entrez un nombre : ");
  scanf("%d",&n);
  som_carre = 1;
  if (n<0){
    printf("Erreur bg\n");
  }
  else
  {
    for(int i=1; i < n; i++)
    {
    som_carre += i * i;
    }
  }
  printf("La somme des carres jusqu a %d est egal %d \n", n, som_carre);
}
*/

//EXO 5

int main()
{
  int continuer, n, value, sommoyenne, sommevariance, varianceempirique;
  char c;
  continuer = 1;
  while (continuer)
  {
    scanf("%d", &value);
    cpt +=1;
    sommoyennemoy += value;
    sommevariance +=   




    printf("Ajouter des valeurs Y/N?\n");
    scanf("%c",&c);
    if (c == 'N')
      continuer = 0;
  }
}
