#import matplotlib.pyplot as plt
#abscisse=[]
#for i in range(10):
  #abscisse += [i]

#carre = []
#for i in range(len(abscisse)):
  #carre += [abscisse[i]**2]

#cube=[]
#for i in range(len(abscisse)):
  #cube += [abscisse[i]**3]

#plt.plot(abscisse,carre,abscisse,cube)
#plt.show()
import math
def intervalle (a,b,inc):
    l=[]
    while a<=b:
        l+=[a]
        a=a+inc
    return l

def valeur_sin(t):
    i=0
    l=[]
    while i<len(t):
        l+=[math.sin(t[i])]
        i+=1
    return l
def valeur_cos(t):
    i=0
    l=[]
    while i<len(t):
        l+=[math.cos(t[i])]
        i+=1
    return l
##courbe sin/cos
#import matplotlib.pyplot as plt
#abscisse=[]
#i=-2*math.pi
#abscisse=intervalle(-2*math.pi,2*math.pi,0.1)
#cos=valeur_cos(abscisse)
#sin=valeur_sin(abscisse)
#plt.plot(abscisse,cos,abscisse,sin)
#plt.show()
#print(intervalle(0,1,0.2))

def multiplication(n1,n2):
    r=[]
    i=0
    while i<(len(n1)+len(n2)):
        r+=[0]
        i=i+1
    rchaquemembre=[]
    i=0
    n=0
    while i<len(n1):
        retenue=0
        rchaquemembre=[]
        for j in range(len(n2)):
            p=n1[i]*n2[j]+retenue
            membre=p%10
            retenue=p//10
            rchaquemembre+=[membre]
        indice=n
        indice2=0
        while indice<len(rchaquemembre):
            if r[i]+rchaquemembre[i]=>10:
                r[i]=rchaquemembre[i]%10
                r[i+1]=r[i+1]+(rchaquemembre[i]//10)
            else:
                r[i]=r[i]+rchaquemembre[i]
            indice+=1
            indice2+=1
        print(r)
        i=i+1
        n+=1
    print(357*125)
    return r, rchaquemembre
print(multiplication([7,5,3],[5,2,1]))
