##############################################
#
# I53 - Compilation et théorie des langages
# ----------
#
# TP2 - Traducteurs simples
#
# BENJELLOUN Youssef / LEAL André / Groupe 1.A
# 11-10-21
###############################################



Les deux traducteurs se composent de 4 fichiers que nous allons détailler dans chaque cas :

- Scanner.py : L'analyseur lexical.

- Parser.py : L'analyseur syntaxique qui transforme la chaine en postfixe.

- Codegen.py : Chargé de générér un code à 3 adresses de part la simulation de la pile.

- Compilo.py : Chargé de faire appel aux 3 modules précédents.



------------------ A/ Traducteur d'expressions arithmétiques -------------------


Nous avons établis la grammaire suivante, qui respècte l'associativité à gauche
des opérateurs arithmétiques et supprime la récursivité à gauche:


Expression -> Terme Reste_E

Reste_E -> +Terme Reste_E
         | -Terme Reste_E
         | NULL

Terme -> Facteur Reste_T

Reste_T -> *Facteur Reste_T
         | /Facteur Reste_T
         | NULL

Facteur -> NB
         | (Expression)

NB -> |0,1,...,9|


################################## COMPILO.PY ##################################


--> La version de python recommandée est python 3.8.10 pour pouvoir tout
éxecuter correctement.

--> La ligne de commande pour lancer le fichier est :

$ python3 compilo.py <"NomFichier"> <"Expression">

--> Il prend en entrée un fichier ou une expression arithmétique.

--> Si le premier argument n'est pas un fichier, il suppose que c'est une chaine
de caractères (Expression).

--> Les sauts de lignes et les espaces sont ignorés.

--> Le fichier est lu en entier.

--> Il y'a également une vérification de l'existance de l'argument :
Si le fichier est vide / aucune expression arithmétique n'est entrée,
une erreur est retournée explicitant que le fichier ou l'expression n'ont pas
été trouvés.

--> Nous avons rajouté un code en commentaire permettant de tester le
compilateur de manière plus rapide, en affichant le résultat théorique ainsi que
le vrai résultat obtenu.

EX : de compilation d'un fichier nommé exemple1 :

Le fichier contient : "(3  + 12   ) /    (5 -2    )"

On lance le fichier avec ligne de commande "$ python3 compilo.py exemple1"

L'expression considérée sera "3+12/5-2" puisque les espaces sont ignorés.

La commande va créer un fichier ./a.out contenant le code à 3 adresses.
Un print affichera alors la valeur calculée de l'expression arithmétique si
$ ./a.out est exécuté.

Dans notre cas, la valeur "5" sera affichée.


################################## SCANNER.PY ##################################


Il va analyser la chaîne de caractères et renvoyer une liste d'unité lexicales
se distinguant dans 4 catégories parmis le lexique suivant :

NB --> [0,1,...,9]
OP --> {'*','/','+','-'}
PO  --> '('
PF  --> ')'

- Les nombres de taille quelconque : identifiés par la fonction "isdigit".

- Les opérateurs : spécifiés dans la liste OP en suivant l'ordre de priorité.

- Les parenthèses ouvrantes "PAR_OUV" : identifiées en tant que caractère.

- Les parenthèses fermantes "PAR_FER" : identifiées en tant que caractère.

Si un caractère est reconnu, il est ajouté à la liste d'unité lexicales
"liste_ul" qui sera renvoyée à la fin de la fonction.

Sinon, une erreur est explicitée avec le caractère fautif en question.

--> Les sauts de lignes et les espaces sont ignorés.


################################## PARSER.PY ###################################


Il va prendre en entrée la liste d'unités lexicales "liste_ul" générée par la
fonction scanner et réaliser les actions suivantes :

- Si la chaîne en entrée est une expression de taille conforme :
---> Elle est déroulée selon la grammaire pré-établie jusqu'à avoir sa structure
 finale.
---> Elle est retournée en notation polonaise inversée (postfixe)

- Sinon il affiche deux erreurs possibles :
1/ La chaîne n'a pas été lue en entier
2/ Erreur syntaxique


EX : (3+14)/(5-2)  -->  3 14 + 5 2 - /
	INFIXE             POSTFIXE


################################## CODEGEN.PY ##################################


Il prend en entrée une expression postfixee et produit un fichier python qui
contient un code à trois adresses pour traduire l'évaluation de l'expressionrangés
avec une pile.

Affiche également le message "compilé avec succès" si la simulation de la pile
est un succès.



-------------------- B/ Traducteur d'expressions booléennes --------------------


Nous avons établis la grammaire suivante, qui respècte l'associativité à gauche
des opérateurs booléens et supprime la récursivité à gauche:

Expr -> Terme Reste_E

Reste_E -> OU Terme Reste_e
        | None

Terme   -> Fact Reste_t

Reste_t -> ET Fact Reste_t
        |  None

Fact    -> BOOL
        |  ! BOOL
        | (Exp)

BOOL    -> VRAI | FAUX


################################## COMPILO.PY ##################################


--> La version de python recommandée est python 3.8.10 pour pouvoir tout
éxecuter correctement.

--> La ligne de commande pour lancer le fichier est :

$ python3 compilo.py <NomFichier> <"Expression">

--> Il prend en entrée un fichier ou une expression booléenne

--> Si le premier argument n'est pas un fichier, il suppose que c'est une chaine
de caractères (Expression).

--> En cas d'ambiguité (EX : un fichier appelé 1+2+3), c'est le fichier qui sera
pris en compte dans la ligne de commande et non l'expression.

--> Les sauts de lignes et les espaces sont ignorés.

--> Le fichier est lu en entier.

--> Il y'a également une vérification de l'existance de l'argument :
Si le fichier est vide / aucune expression arithmétique n'est entrée,
une erreur est retournée explicitant que le fichier ou l'expression n'ont pas
été trouvés.

--> Nous avons rajouté un code en commentaire permettant de tester le
compilateur de manière plus rapide, en affichant le résultat théorique ainsi que
le vrai résultat obtenu.

EX : de compilation d'un fichier nommé exemple2 :

Le fichier contient : "(VRAI    OU FAUX ) ET ( FAUX  OU   FAUX )"

On lance le fichier avec ligne de commande "$ python3 compilo.py exemple2"

L'expression considérée sera "(VRAI OU FAUX) ET (FAUX OU FAUX)"
puisque les espaces sont ignorés.

La commande va créer un fichier ./a.out contenant le code à 3 adresses.
Un print affichera alors la valeur calculée de l'expression booléenne si
$ ./a.out est exécuté.

Dans notre cas, la valeur "FAUX" sera affichée.


################################## SCANNER.PY ##################################


Il va analyser la chaîne de caractères et renvoyer une liste d'unité lexicales
se distinguant dans 4 catégories parmisIl prend en entrée une expression postfixee et produit un fichier python qui
contient un code à trois adresses pour traduire l'évaluation de l'expression
avec une pile.

Affiche également le message "compilé avec succès" si la simulation de la pile
est un succès. le lexique suivant :

BOOL --> {'VRAI','FAUX'}
OP --> {'NON','ET','OU'}
PO  --> '('
PF  --> ')'

- Les booléens : spécifiés dans la liste BOOL

- Les opérateurs : spécifiés dans la liste OP en suivant l'ordre de priorité.

- Les parenthèses ouvrantes "PAR_OUV" : identifiées en tant que caractère.

- Les parenthèses fermantes "PAR_FER" : identifiées en tant que caractère.

Si un caractère est reconnu, il est ajouté à la liste d'unité lexicales
"liste_ul" qui sera renvoyée à la fin de la fonction.

Sinon, une erreur est explicitée avec le caractère fautif en question.

--> Les sauts de lignes et les espaces sont ignorés.


################################## PARSER.PY ###################################


Il va prendre en entrée la liste d'unités lexicales "liste_ul" générée par la
fonction scanner et réaliser les actions suivantes :

- Si la chaîne en entrée est une expression de taille conforme :
---> Elle est déroulée selon la grammaire pré-établie jusqu'à avoir sa structure
finale
---> Elle est retournée en notation polonaise inversée (postfixe)

- Sinon il affiche deux erreurs possibles :
1/ La chaîne n'a pas été lue en entier
2/ Erreur syntaxique

EX : (VRAI OU FAUX) ET (FAUX OU FAUX)  -->  VRAI FAUX OU FAUX FAUX OU ET
	                INFIXE                              POSTFIXE


################################## CODEGEN.PY ##################################


Il prend en entrée une expression postfixee et produit un fichier python qui
contient un code à trois adresses pour traduire l'évaluation de l'expression
avec une pile.

Affiche également le message "compilé avec succès" si la simulation de la pile
est un succès.
