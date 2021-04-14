def somme(u,v):
    
    i=0
    sommev=[]
    while i<len(u): 
       t=u[i]+v[i]
       sommev += [t]
       i=i+1
    sommev=tuple(sommev)
    return sommev
def mult(a,u):
    i=0
    multpli = []
    while i<len(u):
        multpli += [a*u[i]]
        i=i+1
    multpli = tuple(multpli)
    return multpli
#u = (1, 2, 1, 3)
#v = (4, 1, 0, 2)
#a=int(input())
#b=int(input())
#h=somme(mult(a,u),mult(b,v))
#print(h)
def produit_scalaire(u,v):
    i=0
    psca=0
    while i<len(u) and len(u)==len(v):
        psca= psca + u[i]*v[i]
        i=i+1
    return psca
def norme(u):
    modul=0
    i=0
    while i<len(u):
        modul = modul + u[i]**2
        i=i+1
    modul = modul**0.5
    return modul
def cosinus(u,v):
    ps=produit_scalaire(u,v)
    nu=norme(u)
    nv=norme(v)
    cos=(ps/nu*nv)
    return cos
def saisit_vecteur(n):
    vect=[]
    i=0
    while i<n:
        vect += [float(input())]
        i=i+1
    return vect

u=saisit_vecteur(3)
print(u)
v=saisit_vecteur(3)
print(v)
print(norme(u))
print(norme(v))
print(produit_scalaire(u,v))
print(cosinus(u,v))

