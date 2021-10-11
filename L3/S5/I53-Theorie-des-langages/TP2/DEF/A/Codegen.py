###############################################
# Codegen.py
# ----------
#
# Production du code à trois adresses
#
# BENJELLOUN Youssef et LEAL Andre
# I53 - Compilation et theorie des langages
# 10/10/2021
###############################################


def codegen(postfixed_l):
    """
    Prend en entrée une expression postfixée et produit un fichier python
    contenant un code à trois adresses traduisant l'évaluation de l'expression
    avec un pile
    """
    f = open("a.out", "w")
    f.write("#!/usr/bin/python3\n")
    stack_level = 0
    for element in postfixed_l:
        if isinstance(element,int):
            f.write(f"t{stack_level} = {element}\n")
            stack_level += 1
        else:
            f.write(f"t{stack_level-2} = t{stack_level-2} {element} t{stack_level-1}\n")
            stack_level -= 1
    f.write("print(t0)\n")
    f.close()
    print('\033[92m'+"Compilé avec succès"+'\033[0m')
