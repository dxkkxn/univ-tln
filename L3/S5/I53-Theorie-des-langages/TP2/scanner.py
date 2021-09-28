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

def expr():
    global i
    if terme() and reste_e():
        print("Chaine valide")
        return 1


def reste_e():
    global i

    if i >= len(l):
        return 1;

    elif l[i][1] == '+' or l[i][1] == '-':
        op = l[i][1]
        i += 1
        if terme() and reste_e():
            print(op, end='')
            return 1
    return 1

def terme() :
    global i
    if fact() and reste_t():
        return 1;

def reste_t():
    global i
    if i > (len(l)-1):
        return 1
    elif l[i][1] == '*' or l[i][1] == '/':
        op = l[i][1]
        i += 1
        if fact() and reste_t():
            print(op, end='')
            return 1
        elif fact():
            print(op, end='')
            return 1
    return 1

def fact():
    global i

    if l[i][0] == 'NB':
        print(l[i][1], end='')
        i += 1
        return 1

    elif l[i][1] == '(':
        i += 1
        if expr() and l[i][1] == ')':
            i += 1
            return 1;
    else:
        print(f" here Chaine invalide near character {l[i][1]}")
        return 0




if __name__ == '__main__':
    tests = [('123+-',[('NB',1),('NB',2),('NB',3),('OP','+'),('OP','-')]),
             ('(1111+22)',[('PO','('),('NB',1111),('OP','+'),('NB',22),('PF',')')])]
    for cas, resultat in tests:
        if scanner(cas) != resultat:
            print("Erreur cas: {}\n    sortie: {}\n  resultat: {}".format(cas, scanner(cas),resultat))
        else:
            print("ok")
    #l = scanner(sys.argv[1:][0])
    l = scanner("5+33-44")
    i = 0
    print(l)
    print(expr()==1)
