import random

def genmatrix(n,p,t):
    L = []
    for i in range(n):
        sousListe = []
        for j in range(p):
            sousListe.append(random.randrange(0,t))
        L.append(sousListe)
    return L
#print(genmatrix(2,3,7))

def gendiag(n, t):
    L = []
    for i in range(n):
        sousListe = [0]*n
        sousListe[i] = random.randrange(0,t)
        L.append(sousListe)
    return L
#print(gendiag(4,10))

def gentrianginf(n, t):
    L = []
    for i in range(n):
        sousListe = [0]*n
        for j in range(i+1):
            sousListe[j] = random.randrange(0,t)
        L.append(sousListe)
    return L
 #print(gentrianginf(4,7))

def gensym(n, t):
    L = gentrianginf(n,t)
    for i in range(n):
        for j in range(i+1):
            L[j][i] = L[i][j]
    return L
#print(gensym(4,10))

def genasym(n, t):
    L = gentrianginf(n,t)
    for i in range(n):
        for j in range(i+1):
            L[j][i] = -L[i][j]
    return L
#print(genasym(3,10))

def transpose(M):
    L = []
    for i in range(len(M[0])):
        sous_liste = []
        for j in range(len(M)):
            sous_liste.append(M[j][i])
        L.append(sous_liste)
    return L
#print(transpose([[1, 2, 3],[4,5,6]]))

import copy

def gencirculante(L):
    M = []
    for i in range(len(L)):
        #ligne = copy.copy(ligne)
        ligne = L[len(L)-i:] + L[:len(L)-i]
        M.append(ligne)
    return M

#print(gencirculante([1,2,3,4]))


def gencirculante2(k, n):
    L = [k]
    new_k = k
    for i in range(n-1):
        a = (new_k&1)<<(n-1)
        b = new_k>>1
        L.append(a|b)
        new_k = a|b
    return L
