###############################################
# Parser.py
# ----------
#
# Analyseur syntaxique d'expression arithmetique
#
# BENJELLOUN Youssef et LEAL Andre
# I53 - Compilation et theorie des langages
# 10/10/2021
##############################################

"""
On utilise la grammaire suivante:

Expr -> Terme Reste_E

Reste_E -> + Terme Reste_e
        |  - Terme Reste_e
        | None

Terme   -> Fact Reste_t

Reste_t -> * Fact Reste_t
        |  / Fact Reste_t
        |  None

Fact    -> NB
        | (Exp)

"""

i = 0
postfixed_l = []
l = []
def parser(unilex) :
    global i, l
    l = unilex
    if (expr_val:=expr()) and i == len(l):
        print('\033[92m'+"Chaine valide"+'\033[0m')
        return postfixed_l
    else:
        error(expr_val, i)
        return None

def expr():
    return (terme() and reste_e())

def reste_e():
    global i
    if i < len(l) and (l[i][1] == '+' or l[i][1] == '-'):
        op = l[i][1]
        i += 1
        if terme():
            postfixed_l.append(op)
            return reste_e()
        else:
            return False
    return True

def terme() :
    return (fact() and reste_t())

def reste_t():
    global i
    if i < len(l) and (l[i][1] == '*' or l[i][1] == '/'):
        op = l[i][1]
        i += 1
        if fact():
            postfixed_l.append(op)
            return reste_t()
        else:
            return False
    return True

def fact():
    global i

    if i < len(l) and l[i][0] == 'NOMBRE':
        postfixed_l.append(l[i][1])
        i += 1
        return True
    elif i < len(l) and l[i][1] == '(':
        i += 1
        if expr():
            if i < len(l) and l[i][1] == ')':
                i += 1
                return True;
    return False


def error(expr_val,i):
    """
    Affiche le caractere fautif en ajoutant plus d'information si possible
    """

    HEADER = '\033[95m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'

    print(f"{HEADER}{FAIL}{BOLD}ERREUR SYNTAXIQUE{ENDC}")
    if expr_val:
        print(f"{WARNING}Erreur syntaxique, la chaine n'a pas ete parcouru en entier.Erreur pres du caractere {ENDC}\'{FAIL}{l[i][1]}{ENDC}\'")
    elif i == len(l):
        print(f"{WARNING}Erreur syntaxique pres du caractere {ENDC}\'{FAIL}{l[-1][1]}{ENDC}\'")
    else:
        print(f"{WARNING}Erreur syntaxique pres du caractere {ENDC}\'{FAIL}{l[i][1]}{ENDC}\'")


