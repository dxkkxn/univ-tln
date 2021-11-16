# Classes
## Constructeurs
```cpp 
// file point.h
class Point{
private :
// attributs
int x,y;
public :
// methodes
//constructeur par defaut
Point();
//constructeur avec parametres
Point(int,int);
//constructeur par copie
Point(const Point &);
...
};
```
```c
// file point.cc 
Point::Point(){
    x=0;
    y=0;
}
Point::Point(int a, int b) {
    x=a;
    y=b;
}
Point::Point(const Point &P) {
    x=P.x;
    y=P.y;
}
```
## Destructeur
Dans la cas d’attributs alloués dynamiquement, la restitution de la mémoire se
fait par le destructeur qui doit être explicitement défini par le concepteur de la
classe. Il y a rien à faire si pas d'allocation dynamique

## Forme canonique de Coplien
* La forme canonique de Coplien est définie par
* Le constructeur par défaut
* Le constructeur par copie
* Le destructeur
* La surcharge de l’opérateur d’affectation

Example 
```cpp
class A{
private :
//attributs
public:
A(); // constructeur par defaut
A(const A&); // constructeur par copie
~A(); // destructeur
A& operator = (const A&);// surcharge de l’oprateur d’affectation

```

## Attribut static
```c 
class Exemple {
private :
static int n;
float x;
};
```
```cpp
int main() {
Exemple A,B;
return 0;
}
// &A.n == &B.n
// &A.x != &B.x
```

## Visibilité
Un attribut privé d’un objet n’est accessible/visible que par les méthodes de la classe.

### Variable locale appelée comme variable globale 
```c
int x = 10;// x global
void f() {
    int x = 1; // local qui masque le global
    x++; // incrementation du local
    ::x++; // incrementation de x global
}
```
### Visibilité dans un module
* La visibilité est possible dans les autres modules s'elle est a été déclaré extern
* Visibilité limitée au module s’il est déclaré static

## Fonctions amies
* Est membre de la classe a le droit d’accéder aux membres privés
(méthodes ou attributs)
* elle est déclarée dans la classe avec le qualificatif friend
* elle est définie sans le qualificatif friend

Example:
```c
// point.h
class Point{
    private :
        // attributs
        int x,y;
    public :
        friend bool coincide (Point, Point)
        friend void Affiche(Point);
};
```
```c
// point.cc
bool coincide(Point P, Point Q) {
    return (P.x==Q.x)&&(P.y==Q.y);
}
void Affiche(Point P) {
    cout<<"("<<P.x<<","<<P.y<<")";
}
```
```cpp
// main. cc
int main() {
    Point P(2,3), Q(4,5);
    cout<<coincide(P,Q); // appel comme fonction standard
    Affiche(P);
    return 0:
}
```
## Classes amies
```cpp

class A {
public:
    //Constructeur de A avec en argument une  instance de B
    A(B b){b.i = 0;}
    // la relation d’amitie autorise l’acces aux membres de B
};
class B {
friend class A;
// A est une amie de B
    private:
    int i;
};
```
* La relation d’amitié n’est pas symétrique : “si A est une amie de B, B n’est
pas automatiquement une amie de A”
* La relation d’amitié n’est pas transitive : “les amies de mes amies ne sont
pas mes amies”
* La relation d’amitié ne peut être héritée

## Agregation
```c
class A {
    private:
        B x;
    public:
        A(int);// constructeur de A 
        // commment initialiser x???
};
```
```cpp
// Solution 1
A::A(int n):x(n) {
    ...
}
```
```cpp
// Solution 2
//Appel du constructeur par défaut de B puis affectation
A::A(int n) {
    x=n;
}
```
## Opérateurs
La surcharge de l’opérateur ♣ se fait par la définition d’une fonction
```c
 type operator ♣(arguments)
```
* Soit par une fonction membre (méthode)
* Soit par une fonction non membre
* Opérateur unaire : ♣obj ou obj♣ est équivalent à obj.operator♣()
* Opérateur binaire : obj1 ♣ obj2 est équivalent à obj1.operator♣(obj2)

Fonction ami de la classe
* On ne peut définir les deux surcharges (membre et non membre) en même
temps, P+Q serait ambiguë pour le compilateur
* La surcharge d’un opérateur binaire par une fonction non membre est
obligatoire, si le premier opérande n’est pas une instance de la classe.

### Examples
```cpp
class TabEntier{
    private :
        int taille;
        int* tab;
    public:
        TabEntier();
        TabEntier(int,int*);
        TabEntier(const TabEntier &);
        ~TabEntier();
        //surcharge de l’affectaion
        TabEntier & operator=(const TabEntier&);
};
```
```cpp
TabEntier & TabEntier::operator=(const TabEntier& T){
    if (this != &T){
        //desallocation de l’objet courant
        delete [] tab;
        //allocation de l’objet courant
        taille = T. taille;
        tab = new int[taille];
        //copie de T dans obj courant
        for(int i=0; i<taille ; i++)
            tab[i]= T.tab[i];
    }
    //retour objet courant modifie
    return (*this);
}
```
```cpp
// point.h
class Point{
    private :
        // attributs
        int x,y;
    public :
        Point()
        {x=0,y=0;}
        Point(int a, int b)
        {x=a; y=b;}
        //surcharge de << par une amie
        friend ostream& operator<<(ostream &, const Point &);
        friend istream& operator>>(istream &, 
Point &)
 };
```
```cpp
// point.cc
ostream& operator<<(ostream & o, const Point & P) {
    o << "(" << P.x << "," << P.y << ")";
    return o;
}
istream& operator>>(istream & i, const Point & P) {
    i >> P.x;
    i >> P.y; 
}
```
```cpp
// tabreel.h
class TabReel{
    private :
        int taille;
        float* tab;
    public:
        TabReel(int n){
        taille=n;
        tab = new float[taille];}
        //surcharge de l’indexation
        // modification autorisee
        float & operator[](int i)
        {return tab[i];}
        // consultation
        float operator[](int i)const
        {return tab[i];} // ne permet pas la modif
    };
```
# Héritage
A partir d’une classe A, on crée une classe B telle que la classe B a toutes les caractéristiques de A
et on lui ajoute des méthodes et attributs spécifiques
```cpp
class A{
    //classe mere
};
class B : <type heritage> A {
    //classe fille
};
```
L’héritage est défini par les mots réservés d’accès qui définissent les droits
d’accès aux membres (attributs ou méthodes) de la classe de base.
1. **public** : les membres de la classe A conservent leur droit d’accès
1. **protected** : les membres publics de A deviennent protégés
1. **private** : les membres publics et protégés de A deviennent privés.

Les méthodes d’une classe dérivée
* ont accès aux membres publics de la classe de base
* n’ont pas accès aux membres privés de la classe de base
Les objets de la classe dérivée ont accès 
* à ses propres membres publics
* aux membres publics de la classe de base

**Statut membre** : statut du membre dans la définition de la classe de base

**Statut hérité** : statut du membre de la classe de base dans la classe dérivée

**Accès classe de base** : droit d’accès aux membres de la classe de base pour les méthodes et fonctions amies de la classe de base

**Accès utilisateur** : droit d’accès aux membres de la classe de base en dehors des méthodes et fonctions amies de la classe de base
### Heritage public
| Statut membre | Statut hérité | Accès classe dérivée | Accèes Utilisateru |
|---------------|---------------|----------------------|--------------------|
public|public|O|O
protected|protected|O|N
private|private|N|N

### Heritage protected
| Statut membre | Statut hérité | Accès classe dérivée | Accèes Utilisateru |
|---------------|---------------|----------------------|--------------------|
public|protected|O|N
protected|protected|O|N
private|private|N|N

### Heritage private
| Statut membre | Statut hérité | Accès classe dérivée | Accèes Utilisateru |
|---------------|---------------|----------------------|--------------------|
public|private|N|N
protected|private|N|N
private|private|N|N

## Compatibilité entre objets
```cpp
// classes.h
class Point{
    protected :
        int x, y
    public :
        Point();
        Point(int,int);
        void Affiche();
};
class PointCol : public Point{
    private :
        short couleur;
    public :
        PointCol();
        PointCol(int,int,short);
        void Affiche();
};
```
```cpp
// main.cc
Point A;
PointCol B;
A=B;// OK
B=A;//KO
Point* pA;
PointCol* pB;
pA=pB;//OK
pB=pA;//KO
```
## Méthode virtuelle
Une méthode virtuelle est une méthode définie dans une classe qui est destinée à être redéfinie dans les classes qui en héritent.

**Typage dynamique**

La déclaration d’une méthode virtuelle indique au compilateur que le choix de
l’appel se fera en fonction du type de l’objet appelant au moment de l’exécution :
c’est le typage dynamique
```cpp
// *.h
class Point{
...
virtual void Affiche()
{cout<<"Point"<<x<<y<<endl;}
};
class PointCol : public Point{
...
void Affiche()
{cout<<"PointCol"<<couleur<<
endl;}
};
```
```cpp
// main.cc
Point C(3,5);
Point* pC=&C;
PointCol D(8,6,1);
PointCol* pD=&D;
pC->Affiche();// Affiche de Point
pD->Affiche();// Affiche de PointCol
pC=pD;
pC->Affiche();// Affiche de PointCol
//grace au typage dynamique
pD->Affiche();// Affiche de PointCol
```