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
    OP = {'+', '-', '*', '/'}
    i = 0
    while i < len(s):
        if s[i].isdigit():
            nb = 0
            while i < len(s) and s[i].isdigit():
                nb *= 10
                nb += int(s[i])
                i += 1
            i -= 1 #decrease of i to keep it in the good index after later increase
            list_ul.append(('NB', nb))

        elif s[i] in OP:
            list_ul.append(('OP', s[i]))
        elif s[i] == '(':
            list_ul.append(('PO', s[i]))
        elif s[i] == ')':
            list_ul.append(('PF', s[i]))
        else:
            print(f"Error near character {s[i]}")
            return None
        i += 1
    return list_ul

"""
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

    if i < len(l) and (l[i][1] == '+' or l[i][1] == '-'):
        op = l[i][1]
        i += 1
        if terme():
            postfixed_l.append(op)
            if reste_e():
                return 1
            else:
                return False
        else:
            return False
    return 1

def terme() :
    global i
    if fact() and reste_t():
        return True
    return False

def reste_t():
    global i
    if i < len(l) and (l[i][1] == '*' or l[i][1] == '/'):
        op = l[i][1]
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

    if i < len(l) and l[i][0] == 'NB':
        postfixed_l.append(l[i][1])
        i += 1
        return 1

    elif i < len(l) and l[i][1] == '(':
        i += 1
        if expr() :
            if i < len(l) and l[i][1] == ')':
                i += 1
                return True;
    else:
        if i >= len(l):
            print(f"Chaine invalide near character {l[-1][1]} index out")
        else:
            print(f"Chaine invalide near character {l[i][1]}")
        return False




if __name__ == '__main__':
    """
    tests = [('123+-',[('NB',1),('NB',2),('NB',3),('OP','+'),('OP','-')]),
             ('(1111+22)',[('PO','('),('NB',1111),('OP','+'),('NB',22),('PF',')')])]
    for cas, resultat in tests:
        if scanner(cas) != resultat:
            print("Erreur cas: {}\n    sortie: {}\n  resultat: {}".format(cas, scanner(cas),resultat))
        else:
            print("ok")
    """
    l = scanner(sys.argv[1:][0])
    postfixed_l = []
    i = 0
    if first():
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
        f.write("print(t0)")
        f.close()




