def somme_pair(L):
    i=0
    sum=0
    while i < len(L):
        if L[i]%2 == 0:
            sum+= L[i]
        i+=1
    return sum
def somme_ind_pair(L):
    i=0
    sum=0
    while i < len(L):
        sum+= L[i]
        i+=2
    return sum

def minimum(L):
    i = 0
    min = L[i]
    while i < len(L):
        if L[i] < min :
            min = L[i]
        i+=1
    return min
def minimum2(L):
    i = 0
    min= L[i]
    min2 = L[i+1]
    while i < len(L) :
        if L[i] < min :
            min2 = min
            min = L[i]

        if L[i] < min2 and L[i] != min :
            min2 = L[i]
        i+=1
    return min2

def minimum_posi(L):
    min= L[0]
    lindc = [0]
    i = 0
    while i < len(L) :
        if L[i] < min:
            min = L[i]
            lindc = [i]
        if L[i] == min and i != lindc[0]:
            lindc += [i]

        i+=1
    return lindc

def som_div_propres(n):
    if n == 1:
        return 0
    i=1
    som_propres = 0
    while i <= (n **0.5 ):
        if (n % i) == 0 :
            if i == n/i:
                som_propres += i
            elif i == 1:
                som_propres += 1
            else:
                som_propres += i + n/i
        i += 1
    return int(som_propres)

def amicaux(n) :
    i = 2
    Lamicaux=[]
    while i < 2 ** n:
        m = som_div_propres(i)
        if som_div_propres(m) ==  i  and m != i and ((m,i) not in Lamicaux) :
            Lamicaux += [(i,m)]
        i +=1
    return Lamicaux

def minpos(L):
    min = L[0]
    pos = 0
    i = 1
    while i < len(L):
        if L[i] < min:
            min = L[i]
            pos = i
        i += 1
    return (min,pos)

def tri(L):
    i = 0
    while i<len(L):
        (min,pos) = minpos(L[i:])
        tmp = L[i]
        L[i] = L[pos]
        L[pos] = tmp
        i +=1
    return L
print(minpos([12,13,5,2,3,7,4,1,5,8,9,3,-5]))
print(tri([-11,12,13,5,2,3,7,4,1,5,8,9,3,-5]))
