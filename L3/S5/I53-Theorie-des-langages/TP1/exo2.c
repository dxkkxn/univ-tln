#include <stdio.h>
#define CARRE(X) ((X)*(X))
#define CUBE(X) (CARRE(X)*(X))
#define DIX 10

int main(int argc, char *argv[])
{ 
    int a=2,b=1,c,i;
    for(i=0; i<DIX; i++) a++;
    a = a+1;
    b = a+b;
    c = CARRE(a+b) + CUBE(a-b);
    return c;
}

// -E affiche le code apres les preprocesseur
