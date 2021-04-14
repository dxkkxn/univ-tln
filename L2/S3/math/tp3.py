import random

def genmatrix(n,p,t):
    L = []
    for i in range(n):
        sousListe = []
        for j in range(p):
            sousListe.append(random.randrage(0,t))
        L.append(sousListe)
    return L
print(genmatrix(2,3,7))            
