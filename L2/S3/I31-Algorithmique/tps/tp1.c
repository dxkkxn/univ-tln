#include <stdio.h>

// EXO 1
/*
void main() {
  printf("Hello world \n");
}
*/


// EXO 2

// 12
/*
#define PRINT(int) printf("%d\n", int)
int main() {
  int x, y, z;
  x = 2; y = 1; z = 0;
  x = x && y || z ; PRINT (x);
  PRINT(x || !y&&z);

  x = y = 1;
  z = x ++ -1; PRINT(x); PRINT(z);
  z += -x++ + ++y; PRINT(x); PRINT(z);
  z = x / ++x; PRINT(z);PRINT(x);
}
*/

//14
/*
 main ()
 {
   int x;
   x = -3+4*5-6; printf("%d\n",x);
   x = 3+4%5-6; printf("%d\n",x);
   x = -3*4%-6/5; printf("%d\n",x);
   x = (7+6)%5/2; printf("%d\n",x);

 }
*/

//16
/*
#define PRINTX printf("%d\n", x)
int main() {  ++x && ++y || ++z; PRINT3(x,y,z);

  int x=2, y, z ;
  x *= 3+2; PRINTX;
  x *= y = z = 4; PRINTX;
  x = y == z; PRINTX;
  x == (y = z); PRINTX;
}
*/

//17
/*
#define PRINT(int) printf("%d\n", int)
int main() {
  int x = 1; int y = 1; int z = 1;
  x += y += z;
  PRINT(x < y ? y : x);
  PRINT( x < y ? x++ : y++);
  PRINT(x); PRINT(y);
  PRINT(z += x < y ? x++ : y++);
  PRINT(y); PRINT(z);

  x = 3; y = z = 4;
  PRINT( (z >= y >= x) ? 1 : 0);
  PRINT( z >= y && y >= x);
}
*/

//19
/*
#define PRINT(int) printf("int = %d\n", int)
int main() {
  int x, y, z;
  x = 03; y = 02; z=01;
  PRINT(x | y & z);
  PRINT(x | y & ~z);
  PRINT(x ^ y & ~z);
  PRINT(x & y && z);
  x = 1; y = -1;
  PRINT(!x | x);
  PRINT( ~x | x );
  PRINT(x^x);
  x <<= 3; PRINT(x);
  y <<= 3; PRINT(y);
  y >>=3; PRINT(y);
}
*/

//20
/*

#define PRINT3(x,y,z) \
printf("x=%d\ty=%d\tz=%d\n", x, y, z)
int main() {
  int x, y, z;
  x = y = z = 1;
  ++x || ++y && ++z; PRINT3(x,y,z);
  x = y = z = 1;
  ++x && ++y || ++z; PRINT3(x,y,z);
  x = y = z = 1;
  ++x && ++y && ++z; PRINT3(x,y,z);
  x = y = z = -1;
  ++x && ++y || ++z; PRINT3(x,y,z);
  x = y = z = -1;
  ++x || ++y && ++z; PRINT3(x,y,z);
  x = y = z = -1;
  ++x && ++y && ++z; PRINT3(x,y,z);
}

*/
//25

/*
int integer = 5;
char character = '5';
char *string = "5";
int main() {
  //PRINT(d,string); PRINT(d,character);
  printf("x = %d \n", string); printf("x = %d \n", character);
  //PRINT(d,integer);
  printf("x = %d \n", integer);
  //PRINT(s, string); PRINT(c , character);
  printf("x = %s \n", string); printf("x = %c \n", character);
  //PRINT(c, integer = 53);
  printf("x = %c \n", integer);
  //PRINT (d , ("5"> 5));
  {
    int sx = -8;
    unsigned ux = -8;
    //PRINT(o, sx); PRINT(o, ux);
    printf("x = %o \n", sx); printf("x = %o \n", ux);
    //PRINT(o, sx>>3 ); PRINT(o , ux>>3 );
    printf("x = %o \n", sx>>3);printf("x = %o \n", ux>>3);
    //PRINT(d, ux>>3 ); PRINT(d, ux>>3 );
    printf("x = %d \n", ux);
  }
}
*/


//26
/*
#define PR(x) \
printf("x=%.8g\t", (double)x)
#define NL putchar("\n")
#define PRINT4(x1, x2, x3, x4)\
PR(x1); PR(x2) ; PR(x3); PR(x4);
void main(){
  double d;
  float f;
  long l;
  int i;
  i = l = f = d = 100/3; PRINT4(i, l, f, d);
  printf("\n");
  d = f = l = i = 100/3; PRINT4(i, l, f, d);
  printf("\n");
  d = f = l = i = (double) printf("\n");100/3; PRINT4(i, l, f, d);
  printf("\n");
  d = (double) 100/3;
  printf("%lf\n", d);
  printf("\n");
  i = l = f = d = (double)(100000/3);PRINT4(i, l, f, d);
  printf("\n");
  d = f = l = i = 100000/3; PRINT4(i, l, f, d);
  printf("\n");
}
*/

// EXO 3
/*
void main(){
  char a;
  //a = getchar();
  scanf("%c",&a);
  printf("%d\n",a );
  printf("On a fait \"l'exercice 3\"\n" );
}
*/


// EXO 4
/*
void main () {
  int x ,y , m;
  printf( "Entrez 2 nombres = ");
  scanf("%d %d", &x, &y);
  (x >= y) ? (m = x) : (m = y);
  printf("%d\n", m);

}
*/



//EXO 5
