#include <stdio.h>
#include <stdlib.h>

#define ERREUR_ARGUMENTS 1
#define True 1
#define False 0

/////////////////////////////////////////////////////
//  LES DECLARATIONS DE TYPES
/////////////////////////////////////////////////////

// --------------------------------------------
// Un entier non-signé
// --------------------------------------------
typedef unsigned int uint;

// --------------------------------------------
// Structure pour les jetons. Selon le type
// (operateur unaire/binaire ou nombre), c'est
// le champ <op> ou <nombre> qui sera exploité
// --------------------------------------------
typedef struct{
  float nombre;
  char op;
  enum{OPUNR,OPBIN,NOMBRE} type;
} TJETON;

//---------------------------------------------
// Une expression postfixe est définie comme
// un tableau de jetons.
//---------------------------------------------
typedef TJETON *TEXPR;

// --------------------------------------------
// Structure de cellule pour définir la
// structure de pile qui suit sous forme de
// liste chaînée. Contient deux champs:
// 1. le <nombre> sur la pile
// 2. le pointeur <suiv> vers la cellule suiv.
// --------------------------------------------
typedef struct tcell{
  float nombre;
  struct tcell *suiv;
} TCELL;

typedef TCELL *TPILE;


/////////////////////////////////////////////////////
//  LES FONCTIONS
/////////////////////////////////////////////////////

//---------------------------------------------
// Renvoie la pile après y avoir empilé une
// nouvelle cellule contenant le <nombre>.
//---------------------------------------------
TPILE Empiler(TPILE pile, float nombre){
    TCELL *new_cell = malloc(sizeof(TCELL));
    new_cell->nombre = nombre;
    new_cell->suiv = pile;
    return new_cell;
}

//---------------------------------------------
// Renvoie la pile étêtée. Le <nombre> présent
// sommet de la pile est traité par "adresse"
// pour être récupéré.
//---------------------------------------------
TPILE Depiler(TPILE pile, float *nombre){
    TCELL *ancien_tete = pile;
    *nombre = pile->nombre;
    pile = pile->suiv;
    free(ancien_tete);
    return pile;
}

// Retourne vrai si la chaine passe' en parametre 
// est un op, ie chaine appartient {'_', '*', '/', '-', '+'}
int est_op(char *chaine) {
    char tab_op[5] = {'_', 'x', '/', '-', '+'}; 
    int on_continue = True;
    for(int i = 0; i < 5 && on_continue; i++) {
        if (chaine[0] == tab_op[i])
            on_continue = False;
    }
    return (on_continue == False);
}
    
//---------------------------------------------
// Convertit une chaîne de caracteres en jeton
//---------------------------------------------

TJETON Chaine2Jeton(char *chaine){
    TJETON new_jeton;

    if(est_op(chaine)) {
        if(chaine[0] == '_') {
            new_jeton.op = chaine[0];
            new_jeton.type = OPUNR;
        } else {
            new_jeton.op = chaine[0];
            new_jeton.type = OPBIN;
        }

    } else {
        new_jeton.type = NOMBRE;
        sscanf(chaine, "%f", &new_jeton.nombre);
    }
    return new_jeton;
}

//---------------------------------------------
// Convertit les arguments (tableau de chaînes
// de caractères) en expression (tableau de
// jetons).
//---------------------------------------------
TEXPR Arg2Expr(char *arguments[], int n){
    TEXPR tab_jetons = malloc(sizeof(TJETON)*n); 
    for (int i = 0; i<n; i++) 
        tab_jetons[i] = Chaine2Jeton(arguments[i]);
    return tab_jetons;
}

//----------------------------------------------
// Affiche les jetons d'une expression postfixe
//----------------------------------------------
void AfficherExpr(TEXPR expr, uint n){
  printf("JETONS : |");
  for (int i = 0; i < n; i++)
    {
      TJETON jeton = expr[i];
      if ((jeton.type == OPUNR) || (jeton.type == OPBIN))
	printf(" %1c |", jeton.op);
      else
	printf(" %3.2f |",jeton.nombre);
    }
  printf("\n");
}

//---------------------------------------------
// Renvoie (x <op> y) si <op> est binaire
// ou (<op> x) si <op> est unaire
//---------------------------------------------
float Operer(float x, float y, char op){
    float res;
    switch (op){
        case 'x':
            res = x * y;
            break;
        case '/':
            res = x/y;
            break;
        case '-':
            res = x-y;
            break;
        case '_':
            res = x*-1;
            break;
        case '+':
            res = x+y;
            break;
    }
    return res;
}


//---------------------------------------------
// Affiche le contenu de la pile
//---------------------------------------------
void AfficherPile(TPILE pile){
    TCELL *curr = pile;
    printf("[");
    while (curr->suiv != NULL) {
        printf("%f->", curr->nombre);
        curr = curr->suiv;
    }
    printf("%f]\n", curr->nombre);
}

//---------------------------------------------
// Renvoie l'évaluation d'une expression
// postfixe <expr> calculée à l'aide d'une pile
//---------------------------------------------
float Evaluer(TEXPR expr, uint n){
    TPILE pile = NULL;
    TJETON curr_jeton;
    float x,y, res;
    for(int i = 0; i < n; i++) {
        curr_jeton = expr[i];
        if(curr_jeton.type == NOMBRE) {
            // si le jeton current est un nombre on empile
            pile = Empiler(pile, curr_jeton.nombre);
        } else if(curr_jeton.type == OPUNR) {
            // si le jeton current est un op unaire on depile
            // la derniere valeur et on opere seulement sur elle;
            pile = Depiler(pile, &x);
            res = Operer(x, 0, curr_jeton.op);
            pile = Empiler(pile, res);
        } else {
            //Sinon l'operateur est forcement un operateur binaire
            // on depile les 2 derniers valeurs et on opere en faisant
            // attention `a l'ordre.
             pile = Depiler(pile, &y);
             pile = Depiler(pile, &x);
             res = Operer(x, y, curr_jeton.op);
             pile = Empiler(pile, res);
        }
    }
    Depiler(pile, &res);
    return res;
}

/////////////////////////////////////////////////////
// FONCTION MAIN
/////////////////////////////////////////////////////
int main(int argc, char* argv[]){
  uint n = argc - 1;  // Le nombre de jetons
  TEXPR expr = NULL;

  if (n < 1)
    // Si aucun argument sur la ligne de commande: arrêt
    {
      printf("Syntaxe: %s expr\n",argv[0]);
      return ERREUR_ARGUMENTS;
    }
  else
    // Sinon: on convertit les arguments en tableau de jetons
    expr = Arg2Expr(argv + 1, n);

  AfficherExpr(expr, n);
  printf("\n%f\n", Evaluer(expr, n));
  return 0;
}
