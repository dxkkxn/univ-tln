#I11 BENJELLOUN 11/12/2019
def somme_vect(u,v):
    i=0
    somme=[]
    while i<len(u):
        somme+= [u[i]+v[i]]
        i=i+1
    somme=tuple(somme)
    return somme
def diff_vect(u,v):
    i=0
    diff=[]
    while i<len(u):
        diff+= [u[i]-v[i]]
        i=i+1
    diff=tuple(diff)
    return diff

def prod_scal(u,v):
    i=0
    prod=0
    while i<len(u):
        prod = prod + (u[i]*v[i])
        i=i+1
    return prod
def prod_mat_vec(u,m):
    pmv=[]
    i=0
    while i<len(m):
        pmv += [prod_scal(u,m[i])]
        i=i+1
    pmv=tuple(pmv)
    return pmv
#I11 BENJELLOUN 11/12/2019
