// #include <stdio.h>
// #include <stdlib.h>
//  typedef struct NbrRationnel{
//    int Num;
//    int Den;
//  }NbrRationnel;
//
//  void afficher_rationnel( NbrRationnel r)
//  {
//    printf("%d / %d\n", r.Num, r.Den);
//  }
//  int comparer_rationnel( NbrRationnel r1, NbrRationnel r2)
//  {
//    float num1 = (float) r1.Num/r1.Den;
//    float num2 = (float) r2.Num/r2.Den;
//    if(num1 > num2)
//     return 1;
//   else if (num1 == num2)
//     return 0;
//   else
//     return -1;
//  }
//  void somme_rationnel( NbrRationnel r1, NbrRationnel r2)
//  {
//    if (r1.Den == r2.Den)
//    {
//      int num = r1.Num + r2.Num;
//      printf("La somme de %d / %d + %d / %d = %d / %d",
//                   r1.Num, r1.Den, r2.Num, r2.Den, num, r1.Den);
//    }
//    else
//    {
//      int num = (r1.Num * r2.Den) + (r2.Num * r1.Den);
//      int den = r1.Den * r2.Den;
//      printf("La somme de %d / %d + %d / %d = %d / %d",
//                   r1.Num, r1.Den, r2.Num, r2.Den, num, den);
//    }
//  }
// void plus_grand_rationnel( NbrRationnel tab[], int taille_tab)
// {
//   NbrRationnel max = tab[0];
//   for (int i = 0; i < taille_tab; i++)
//   {
//     if (comparer_rationnel(max,tab[i]) == -1)
//       max = tab[i];
//   }
//   afficher_rationnel(max);
// }
//
// void main(){
//   NbrRationnel num1 = {12, 7}, num2 = {8, 13}, num3 = {14, 2}, num4 = {1,9},
//     num5 = {2,3};
//   //
//   // afficher_rationnel(num1);
//   // afficher_rationnel(num2);
//   // afficher_rationnel(num3);
//   // afficher_rationnel(num4);
//   // afficher_rationnel(num5);
//   NbrRationnel tab [5] = { num1, num2, num3, num4, num5};
//   plus_grand_rationnel(tab, 5);
// }


// EXO 8

// #include <stdlib.h>
// #include <stdio.h>
// void print_tab(int tab[], int size_tab)
// {
//   printf("[ ");
//   for(int i = 0; i < size_tab; i++)
//   {#include <stdlib.h>
// #include <stdio.h>
// void print_tab(int tab[], int size_tab)
// {
//   printf("[ ");
//   for(int i = 0; i < size_tab; i++)
//   {
//     printf("%d ",tab[i]);
//   }
//   printf("]\n");
// }
//
// void occupation_memoire(int a, int b, int tab[])
// {
//   printf("a      : %p %d\n", &a, a);
//   printf("b      : %p %d\n", &b, b);
//   printf("tab[0] : %p %d\n", &tab[0], tab[0]);
//   printf("tab[1] : %p %d\n", &tab[1], tab[1]);
//   printf("tab[2] : %p %d\n", &tab[2], tab[2]);
// }
//
// int main()
// {
//   int a = 10;
//   int b = 5;
//   int tab[3] = {1, 2, 3};
//   int *p_int;
//   occupation_memoire(a, b, tab);
//   tab[0] = a;
//   *(tab + 1) = b;
//   p_int = tab + 2;
//   occupation_memoire(a, b, tab);
//   *p_int = *(p_int-1);
//   p_int = p_int - 1;
//   *p_int = *(p_int - 1);
//   p_int = p_int - 1;
//   *p_int = *(p_int + 2);
//   occupation_memoire(a, b, tab);
//   printf("%d\t %d\t %d\t %d\t %d\n", a, b, tab[0], tab[1], tab[2]);
//   return EXIT_SUCCESS;
// }

//     printf("%d ",tab[i]);
//   }
//   printf("]\n");
// }
//
// void occupation_memoire(int a, int b, int tab[])
// {
//   printf("a      : %p %d\n", &a, a);
//   printf("b      : %p %d\n", &b, b);
//   printf("tab[0] : %p %d\n", &tab[0], tab[0]);
//   printf("tab[1] : %p %d\n", &tab[1], tab[1]);
//   printf("tab[2] : %p %d\n", &tab[2], tab[2]);
// }
//
// int main()
// {
//   int a = 10;
//   int b = 5;
//   int tab[3] = {1, 2, 3};
//   int *p_int;
//   occupation_memoire(a, b, tab);
//   tab[0] = a;
//   *(tab + 1) = b;
//   p_int = tab + 2;
//   occupation_memoire(a, b, tab);
//   *p_int = *(p_int-1);
//   p_int = p_int - 1;
//   *p_int = *(p_int - 1);
//   p_int = p_int - 1;
//   *p_int = *(p_int + 2);
//   occupation_memoire(a, b, tab);
//   printf("%d\t %d\t %d\t %d\t %d\n", a, b, tab[0], tab[1], tab[2]);
//   return EXIT_SUCCESS;
// }

// EXO 9
// #include <stdio.h>
// #include <stdlib.h>
//
// void recherche_entier(int tab[], int size_tab)
// {
//   int a;
//   int cpt = 0;
//   printf("Quel entier cherchez vous? ");
//   scanf("%d", &a);
//   for (int i = 0; i < size_tab; i++)
//   {
//     if (tab[i] == a)
//       cpt +=1;
//   }
//   printf("L'entier %d se repete %d fois \n", a, cpt);
// }
// void recherche_entier2(int tab[], int size_tab)
// {
//   int a;
//   int cpt = 0;
//   printf("Quel entier cherchez vous? ");
//   scanf("%d", &a);
//   for (int i = 0; i < size_tab; i++)
//   {
//     if (*(tab + i) == a)
//       cpt +=1;
//   }
//   printf("L'entier %d se repete %d fois \n", a, cpt);
// }
//
//
// int main()
// {
//   int tab[10] = {1, 2, 3, 4, 5, 1, 1, 1, 2, 1 };
//   recherche_entier2(tab, 10);
// }

//EXO 10

#include <stdio.h>
#include <stdlib.h>
#define LG 10
#define NBNOTES 5
#define MAX 3

typedef struct Etudiant {
  char nom[LG];
  char prenom[LG];
  int notes[NBNOTES];
} Etudiant;

Etudiant* creation()
{
  Etudiant* etu = (Etudiant*)malloc(sizeof(Etudiant));
  char nom[10];
  char prenom[10];
  int note;
  scanf(" %s", etu->nom );
  scanf(" %s", etu->prenom);
  for(int i = 0;  i < NBNOTES; i++)
  {
    scanf(" %d", &note );
    etu->notes[i] = note;
  }
  return etu;
}

Etudiant** creation_tab_etud(Etudiant* tab[], int size_tab)
{
  for(int i = 0;  i < size_tab; i++)
  {
    tab[i] = creation();
  }
  return tab;
}

void affiche_etud( Etudiant* etud)
{
  printf("%s %s ", etud->nom, etud->prenom);
  for (int i = 0; i < NBNOTES; i++)
    printf("%d",etud->notes[i]);
}

void affiche_tab_etud(Etudiant* tab[], int size_tab)
{
  for(int i = 0; i < MAX; i++)
    affiche_etud(tab[i]);
}

int main()
{
  Etudiant* tabetu[MAX];
  creation_tab_etud(tabetu, MAX);
  affiche_tab_etud(tabetu, MAX);
}
