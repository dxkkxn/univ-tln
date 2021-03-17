#############################################
# Jeu du Puissance 4                        #
# Cours d'algorithmique                     #
# Licence Informatique - 1ere année         #
# Université de Toulon                      #
#                                           #
# Version du 01/03/2019                     #
#############################################


def init_jeu():
    """Renvoie une grille de jeu 6x7 sous forme d'une
    liste de listes remplie de 0"""
    return [[0]*7 for i in range(6)]

def dessine_grille(grille):
    """Retourne sous forme de chaine de caracteres l'état de la grille de jeu 
    ainsi que le numéro des colonnes:
       -O pour le joueur 1
       -X pour le joueur 2
       
    """
    return

def coups_legaux(grille):
    """Renvoie la liste des colonnes dans lesquelles il est possible de
    jouer un jeton

    """
    return

def jouer_coup(joueur, coup, grille):
    """Ajoute un jeton pour le joueur <joueur> dans la colonne <coup> dans
    la grille et renvoie la ligne où celui-ci a été joué

    """
    return
    

def gagnant_colonne(lig, col, grille):
    """Renvoie True si le coup joué (lig,col) forme une colonne de 4 jetons
    False sinon
    """
    return 

def gagnant_ligne(lig, col, grille):
    """Renvoie True si le coup joué (lig,col) forme une ligne de 4 jetons
    False sinon
    """
    return

def gagnant_diagonale(lig, col, grille):
    """Renvoie True si le coup joué (lig,col) forme une diagonale de 4 jetons
    False sinon
    """
    return

def gagnant_antidiagonale(lig, col, grille):
    """Renvoie True si le coup joué (lig,col) forme une antidiagonale de 4 jetons
    False sinon
    """
    return

def gagner(lig, col, grille):
    """Renvoie True si le coup joué est un coup gagnant
    False sinon
    """
    return

def main():
    """Programme principal:
    A chaque itération de la boucle de jeu il faut:
      - afficher l'état du jeu
      - calculer les coups légaux
      - stopper la partie si la liste est vide
      - demander un coup legal au joueur actif
      - ajouter son jeton dans la grille
      - arreter la partie si le coup est gagnant
      - changer le joueur actif et recommencer

    """
    pass
    
if __name__=='__main__':
    main()
