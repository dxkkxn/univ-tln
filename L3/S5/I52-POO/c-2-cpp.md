# C++ 
## Const Keyword
Examples:

**Pointeur sur une constante**
```c
const char * pc="abcde";// rend l’objet pointé constant mais pas le pointeur
pc[3]=’a’ //KO l’objet pointe n’est pas modifiable
pc="efgh" //OK le pointeur peut changer de valeur, il va pointer sur une nouvelle constante
```
**Pointeur constante**
```c
char * const pc="abcde";// pointeur constant, mais pas l’objet pointe
pc[3]=’a’ //OK on peut modifier l’objet pointé
pc="efgh" //KO le pointeur ne peut changer de valeur
```
**Pointeur constant sur une constante**
```c
const char * const pc="abcde";// pointeur constant sur une constante
```

## Pointers
Example utile:
```cpp
int i = 2;
cout <<"valeur de i = "<<i<<" valeur de &i = "<< &i<< endl;
int* j;
*j= i; // impossible car par d’allocation de l’espace (segmentation fault)
j=&i;//affectation d’un espace memoire existant
cout <<"valeur de j = "<<j<<" valeur de *j = "<< *j<< endl;
j= new int;// allocation dynamique de l’espace d’un int dans le tas
*j=4;
cout <<"valeur de j = "<<j<<" valeur de *j = "<< *j<< endl;
```
```bash
valeur de i = 2 valeur de &i = 0x7fff1fce11b4
valeur de j = 0x7fff1fce11b4 valeur de *j = 2
valeur de j = 0xae2030 valeur de *j = 4
```

## Référence

Une référence est la creation d'un alias de l'objet. Example:
```c
int a = 90, b = 78, c;
int &x = a; // declaration de la reference x sur la variable a
c = x + 5; // equivaut : c = a + 5;
int &y = b; // declaration de la reference y sur la variable b
y = a + 10; // equivaut : b = a + 10;
cout << "La variable b vaut : " << b << endl;
cout << "La variable c vaut : " << c << endl;
```
```bash
La variable b vaut : 100
La variable c vaut : 95
```
L'affectation d'une référence 
* effectue une copie intégrale de l’objet référencé
* ce n’est pas une affectation d’adresse
* l’objet et la référence partage le même espace mémoire
* une référence ne peut être initialisée qu’une seule fois : à la déclaration.
Toute autre affectation modifie en fait la variable référencée.
* une référence ne peut référencer qu’une seule variable tout au long de sa
durée de vie.
```cpp
int x=5; y = 10, z=15;
int& ref1 = x;
int& ref2 = y;
ref1 = ref2; // equivaux x=y;
ref1 = &z; // KO referencement d’un seul objet pendant sa duree de vie
```
### Pointer vs reference
```cpp
int x = 10;
int* p =&x; //& operateur d’adresse
*p = 7; //on utilise *p pour affecter une valeur x par l’intermediaire de p
int x2 = *p; //on lit x par l’intermediaire de p, equivaut a x2=x
int* p2 = &x2 //on obtient un pointeur vers un autre int x2
p2 = p; //p2 et p pointent sur x
p = &x2; // p pointe sur un autre objet x2
```
Passage d'arguments par référence dans une fonction
* permet un gain d’espace mémoire
* a les avantages de la transmission par adresse du C
* évite la manipulation de pointeurs comme en C
Example 
```c
void permuter(int& a, int& b) {
    int t;
    t = a; a = b; b = t;
}
int main() {
    int x = 2, y = 3;
    cout << x << y << endl; // 2 3
    permuter(x, y)
    cout << x << y << endl; // 3 2
    return 0;
}
```

