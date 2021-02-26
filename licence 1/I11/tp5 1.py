def som_div_propres(n):
    i=1
    somme=0
    while i<n:
        if n%i==0:
            somme=somme+i
        i=i+1
    return somme

def est_parfait(n):
    somme = som_div_propres(n)
    if somme==n:
        nomparfaite=True
    else:
        nomparfaite=False
    return nomparfaite

def affiche_parfait(k):
    i=1
    while i<2**k:
        if est_parfait(i)==True:
            print(i)
        i=i+1
        
def est_presque_parfait(n):
    somme = som_div_propres(n) 
    if somme == n - 1:
        presqueparfait=True
    else:
        presqueparfait=False
    return presqueparfait

def affiche_presque_parfait(k):
    i=1
    while i<2**k:
        if est_presque_parfait(i)==True:
            print(i)
        i=i+1
        
def amicaux(n,m):
    divn = som_div_propres(n)
    divm = som_div_propres(m)
    if divn==m and divm==n:
        potes=True
    else:
        potes=False
    return potes

def affiche_amicaux(k):
    i=1
    l=[]
    j=1
    while i<2**k:
        j=1
        while j<2**k :
            if amicaux(i,j)==True and i!=j:
                l=l+[i,j]
            j=j+1
        i=i+1
    return(l)           
 
