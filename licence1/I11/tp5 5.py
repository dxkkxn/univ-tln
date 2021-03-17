from math import exp
def factorielle(n):
    facto=1
    while n >= 1:
        facto = facto * (n)
        n=n-1
    return(facto)
def puissance(x,n):
    pui=x**n
    return(pui)
def serie_exp(x,n):
    i=1
    somme=0
    while i<=n:
        somme= somme+(puissance(x,i)/factorielle(i))
        i=i+1
    return somme

x=float(input())
p=float(input())
n=1
while n < 10**-p:
    if abs(serie_exp(x,n))-exp(x)<10**-p:
        print(n)
        i=10**-p
    n=n+1
    
        
        
