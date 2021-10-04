##############################################
#
# scanner.py
# ----------
#
# Analyseur lexical d'expression arithmétique
#
# Nicolas Méloni
# I53 - Compilation et théorie des langages
# 02-10-2019
###############################################

import sys

'''
On utilise le lexique suivant:

NB --> [0-9]+
OP --> + | - | * | /
PO  --> (
PF  --> )
'''

"""
Convertit la chaine de caracteres <s> en une liste d'unités
léxicales de la forme (<type>, <valeur>). Retourne None en cas
d'erreur et affiche le caractere fautif
"""
def scanner(s):
    list_ul = []
    i = 0
    while i < len(s):
        if (i+4) <= len(s) and s[i:i+4] == "VRAI":
            list_ul.append(("BOOL", True))
            i += 4

        elif (i+4) <= len(s) and s[i:i+4] == "FAUX":
            list_ul.append(("BOOL", False))
            i += 4

        elif (i+2) <= len(s) and s[i:i+2] == "OU":
            list_ul.append(("OP", "OU"))
            i += 2
        elif (i+2) <= len(s) and s[i:i+2] == "ET":
            list_ul.append(("OP", "ET"))
            i += 2

        elif (i+3) <= len(s) and s[i:i+3] == "NON":
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
            print(f"Lexical error near char {s[i]}")
            return None

    return list_ul

"""
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

"""

def first() :
    global i
    if expr() and i == len(l):
        print("Chaine valide")
        return postfixed_l
    else:
        if i >= len(l):
            print(f"Chaine invalide near character {l[-1][1]} index out")
        else:
            print(f"Chaine invalide near character {l[i][1]}")

def expr():
    global i
    if terme() and reste_e():
        return True
    return False


def reste_e():
    global i

    if i < len(l) and l[i][1] == "OU" :
        op = "or"
        i += 1
        if terme():
            postfixed_l.append(op)
            if reste_e():
                return 1
            else:
                return False
        else:
            return False
    return True

def terme() :
    global i
    if fact() and reste_t():
        return True
    return False

def reste_t():
    global i
    if i < len(l) and l[i][1] == "ET":
        op = "and"
        i += 1
        if fact():
            postfixed_l.append(op)
            if reste_t():
                return True
            else:
                return False
        else:
            return False
    return True

def fact():
    global i
    if i < len(l) and l[i][1] == "NON":
        op = "not"
        i += 1
        if fact():
            postfixed_l.append(op)
        else:
            return False

    elif i < len(l) and l[i][0] == "BOOL":
        postfixed_l.append(l[i][1])
        i += 1

    elif i < len(l) and l[i][1] == '(':
        i += 1
        if expr() :
            if i < len(l) and l[i][1] == ')':
                i += 1
                return True;
            else:
                return False
        else:
            return False
    else:
        if i >= len(l):
            print(f"Chaine invalide near character {l[-1][1]} index out")
        else:
            print(f"Chaine invalide near character {l[i][1]}")
        return False

    return True



if __name__ == '__main__':
    l = scanner(sys.argv[1])
    postfixed_l = []
    i = 0
    if first():
        f = open("a.out", "w")
        f.write("#!/usr/bin/python3\n")
        stack_level = 0
        print(postfixed_l)
        for element in postfixed_l:
            if isinstance(element, bool):
                f.write(f"t{stack_level} = {element}\n")
                stack_level += 1
            elif element == "not":
                f.write(f"t{stack_level-1} = not t{stack_level-1}\n")
            else:
                f.write(f"t{stack_level-2} = t{stack_level-2} {element} t{stack_level-1}\n")
                stack_level -= 1
        f.write("print(t0)")
        f.close()




