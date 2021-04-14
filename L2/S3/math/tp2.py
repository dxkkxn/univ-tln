def pgcd(a,b):
    if a < b :
        a,b = b,a
    while b != 0:
        a,b = b, a % b
    return a
#print(pgcd(5, 45))

def euclide_e(a, n):
    u0 = 1
    u1 = 0
    v0 = 0
    v1 = 1

    while a%n != 0:
        q = a//n
        a, n = n, a % n
        tmpu1 = u1
        tmpv1 = v1
        u1, v1 = u0-q*u1, v0-q*v1
        u0,v0 = tmpu1,tmpv1
    return[n,u1,v1]
#print(euclide_e(7, 2))

def inverse(a,p):
    u0 = 1
    u1 = 0
    v0 = 0
    v1 = 1
    tmpp=p
    while a%p != 0:
        q = a//p
        a, p = p, a % p
        tmpu1 = u1
        tmpv1 = v1
        u1, v1 = u0-q*u1, v0-q*v1
        u0,v0 = tmpu1,tmpv1
    return u1%tmpp

#print(inverse(2,7))

def euler_phi(n):
    i=1
    cpt = 0
    while i < n:
        oldi = i
        oldn = n
        while oldn != 0:
            oldi, oldn = oldn, oldi % oldn
        if oldi == 1:
            cpt += 1
        i += 1
    return cpt

#print(euler_phi(6))

def decompose(n,b):
    L=[]
    while n > 0:
        L= [n%b] + L
        n = n//b

    return L
#print(decompose(25, 3))
#print(decompose(25, 2))

def valeur(L, b):
    sum = L[-1]
    n = len(L)
    j= -2
    while j >= -n:
        i = 0
        pow = 1
        while i < -j:
            pow = b 
            i += 1
        sum += L[j]*b
        j -= 1
    return sum

print(valeur([3, 2, 1], 5))
