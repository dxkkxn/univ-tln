###############################################
# Scanner.py
# ----------
#
# Analyseur lexical d'expressions booléennes
#
# BENJELLOUN Youssef et LEAL Andre
# I53 - Compilation et theorie des langages
# 10/10/2021
###############################################




"""
On utilise le lexique suivant:

BOOL --> VRAI
        | FAUX
OP --> OU | ET | NON
PO  --> (
PF  --> )
"""

def scanner(s):
    """
    Convertit la chaîne de caractères <s> en une liste d'unités
    lexicales de la forme (<type>, <valeur>). Retourne None en cas
    d'erreur et affiche le caractère fautif
    """
    list_ul = []
    i = 0
    while i < len(s):
        if i <= len(s)-4 and s[i:i+4] == "VRAI":
            list_ul.append(("BOOL", True))
            i += 4

        elif i <= len(s)-4 and s[i:i+4] == "FAUX":
            list_ul.append(("BOOL", False))
            i += 4

        elif i <= len(s)-2 and s[i:i+2] == "OU":
            list_ul.append(("OP", "OU"))
            i += 2

        elif i <= len(s)-2 and s[i:i+2] == "ET":
            list_ul.append(("OP", "ET"))
            i += 2

        elif i <= len(s)-3 and s[i:i+3] == "NON":
            list_ul.append(("OP", "NON"))
            i += 3

        elif s[i] == '(':
            list_ul.append(("PO",'('))
            i += 1

        elif s[i] == ')':
            list_ul.append(("PF",')'))
            i += 1

        elif s[i] == ' ' or s[i] == '\n':
            i += 1

        else:
            error(s,i)
            return None

    return list_ul

def error(s,i):
    """
    Affiche la chaîne de caractères en soulignant en rouge le
    caractère fautif
    """

    HEADER = '\033[95m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'

    print(f"{HEADER}{FAIL}{BOLD}ERREUR LEXICALE{ENDC}")
    print(f"{WARNING}Erreur lexicale près de l'unité lexicale{ENDC} \'{FAIL}{s[i]}{ENDC}\' -> ",end = "")
    print(f"{s[0:i]}{BOLD}{FAIL}{s[i]}{ENDC}{s[i+1:]}")
