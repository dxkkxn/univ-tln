###############################################
# Scanner.py
# ----------
#
# Analyseur lexical d'expression arithmetique
#
# BENJELLOUN Youssef et LEAL Andre
# I53 - Compilation et theorie des langages
# 10/10/2021
###############################################


"""
On utilise le lexique suivant:

NB --> [0-9]+
OP --> + | - | * | /
PAR_OUV  --> (
PAR_FER  --> )
"""

def scanner(s):
    """
    La fonction scanner prend en entree une chaine de caracteres <s>
    et renvoie une liste d'unites lexicales de la forme (<type>, <valeur>).
    Retourne None en cas d'erreur et affiche le caractere fautif
    """
    list_ul = []
    OP = {'+', '-', '*', '/'}
    i = 0
    while i < len(s):
        if s[i].isdigit():
            nb = 0
            while i < len(s) and s[i].isdigit():
                nb *= 10
                nb += int(s[i])
                i += 1
            i -= 1 #decrement de i pour mantenir le bon indice
            list_ul.append(('NOMBRE', nb))

        elif s[i] in OP:
            list_ul.append(('OP', s[i]))
        elif s[i] == '(':
            list_ul.append(('PAR_OUV', s[i]))
        elif s[i] == ')':
            list_ul.append(('PAR_FER', s[i]))
        elif s[i] == ' ' or s[i] == '\n' :
            pass
        else:
            error(s,i)
            return None

        i += 1
    return list_ul

def error(s,i):
    """
    Affiche la chaine de caracteres en soulignant en rouge le
    caractere fautif
    """

    HEADER = '\033[95m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

    print(f"{HEADER}{FAIL}{BOLD}ERREUR LEXICALE{ENDC}")
    print(f"{WARNING}Erreur lexicale pres du caractere{ENDC} \'{FAIL}{s[i]}{ENDC}\' -> ",end = "")
    print(f"{s[0:i]}{BOLD}{FAIL}{s[i]}{ENDC}{s[i+1:]}")



