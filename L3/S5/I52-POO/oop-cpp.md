# C++ et POO 
# RESUME CHAPITRE 2
## Information génerale
Deux étapes :

**La compilation** : traduction du programme en C++ en langage machine, le fichier produit se termine par .o.
Exemple :
```bash 
g++ -c hello.cc
# g++ de GNU Compiler Collection (GCC)
# -c -> génere le fichier .o
```
**L’édition de lien** : réunion des fichiers en langage machine pour produire un exécutable
Les fichiers sources (en C++) s’appellent les modules

**main()** est la première appelée par le système d’exploitation. 
**Un seul appel** à la fonction main dans le cas de plusieurs modules

## Préprocesseur
Sont des commandes effectuées dans la phase de
précompilation. Sont en charge de:
* élimination de commentaires
* inclusion de fichier source
* substitution de texte
* définition de macros
* compilation conditionnelle
### La commande #if
```
#if T1 I1 #elif T2 I2 #else I3 #endif
T1,T2 bool | I1,I2,I3 commandes
```
```c
// Exemples de #if
#if SYSTEM == SYSV
#define HDR "sysv.h"
#elif SYSTEM == BSD
#define HDR "bsd.h"
#else
#define HDR "default.h"
#endif
#include HDR
```

### La commande #ifndef
```c 
#ifdef ident #endif
#ifndef ident #endif
permettent de tester si ident est défini ou non
```
```c
//Exemple de #ifdef
#ifdef _DEBUG
cerr << "verification : " << x << endl;
#endif
L’affichage du message ne sera activé que si l’on compile le programme avec
l’option -D_DEBUG
``` 


## Fichiers .h
Ces fichiers regroupent l’ensemble des déclarations communes (types, structures,
classes,...) et séparés des fichiers .cc
* les prototypes de fonctions
* définition de types et constantes
* des directives de compilation nécessaires
* déclaration de variables externes

### Declaration vs definition
* La **déclaration** ne fait qu’indiquer l’existence d’une entité informatique sans la
créer,
* la **définition** l’instancie, c’est-à-dire qu’elle la crée.

**Déclaration**
```c 
// variables
extern int Var;
//extern permet de declarer la variable sans la definir
// fonctions
int Somme(int Var1, int Var2 );
```
**Définition**
```c 
// variables
int Var;
// Pour les fonctions en C déclaration définition
int Somme (int Var1, int Var2) {
    return Var1 + Var2;
}
```
En C et C++, la définition inclut la déclaration, la présence de la définition dans
une unité (module) d’un programme permet d’y omettre la déclaration.



### Visibilité inter-fichiers des identificateurs
**global** : Tout identificateur global est visible dans tout le module et peut être utilisé dans
d’autres modules

**static** : L’utilisation de static restreint la visibilité de l’identificateur. Pour un
identificateur global, la visibilité est limitée au module, pour un local sa visibilité
est locale mais sa durée de vie le temps d’exécution du programme.
```c
static int i = 1;
static void afficher();
```

**extern** : Le qualifieur extern permet de déclarer un identificateur sans le définir.
```c
extern int i = n;
extern int f(int n, char c);
```

### Option de g++
* -c permet de générer le fichier objet dont l’extention est .o
* -o permet de nommer le fichier exécutable de sortie
* -I ajoute un chemin non standard d’accès aux fichiers d’en-tête
* -L ajoute un chemin non standard d’accès aux bibliothèques
* -g permet de produire un code exploitable pour le déverminage

### Bibliothèques 
Est une ensemble de fonctions en langage machine avec une table de ces
fonctions.

L’éditeur de lien n’inclut que celles utilisées par le programme ou celles
demandées ou celles spécifiées extern.

A une bibliothèque correspond un fichier en-tête d’extension .h.

L’option -lNomBiblio permet d’inclure les fonctions d’une bibliothèque si son
archive libNomBiblio.a existe.
```c
#include <math.h> // a inclure dans le fichier qui utilise les fonctions de la bibliotheque
gcc monprog.c -lm //Le fichier correspondant a la bibliotheque de mathematique est libm.a
```
La création d’une bibliothèque statique regroupant se fait à l’aide de deux commandes:

ar cr libNomBiblio.a listeDesObjets : pour créer la bibliothèque

ranlib libNomBiblio.a : pour effectuer une indexation pour un accès plus rapide

```bash
ar cr libmath.a sqrt.o cos.o sin.o exp.o log.o // creation de libmath.a
ranlib libmath.a // indexation
g++ calcul.cc -lmath // utilisation de libmath.a
```
## Makefile
| keybind | meaning |
| --------| -------------- |
|$@ | Le nom de la cible
|$< | Le nom de la première dépendance
|$^ | La liste des dépendances
|$? | La liste des dépendances plus récentes que la cible
|$* | Le nom du fichier sans suffixe
**Definition des macros examples**
```make
# fichier makefile
CC= g++
OBJ=principal.o calcul.o
LIB_PATH=/usr/local/lib /usr/local/lib/X11 $HOME/lib
essai: $(OBJ)
    $(CC) $(OBJ) -o essai
```
