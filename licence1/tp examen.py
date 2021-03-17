##prenom1=input("prenom1 ? ")
##prenom2=input("prenom2 ? ")
##print("Bonjour",prenom1,"moi",prenom2,"toi bonjour?")

##n=int(input("Entrez une note: "))
##if 10>=n>8:
##    print("Note module: A module valide")
##elif 8>=n>6:
##    print("Note module: B module valide")
##elif 6>=n>=5:
##    print("Note module: C module valide")
##else:
##    print("Note module: C")


##a=int(input("a = "))
##m=int(input("m = "))
##i=1
##while i<m:
##    print("U(",i,") =",i*a)
##    i=i+1
##    
##L=["Rouge","bleu","orange","rose","vert","violet"]
##c1=input("c1 = ")
##c2=input("c2 = ")
##Lc1=[]
##Lc2=[]
##Lc3=[]
##i=0
##while i<len(L):
##    j=True
##    while j:
##        if L[i][0]==c1:
##            Lc1+=[L[i]]
##            j=False
##        elif L[i][-1]==c2:
##            Lc2+=[L[i]]
##            j=False
##        else:
##            Lc3+=[L[i]]
##            j=False
##    i=i+1
##print("Chaines commencant par un",c1,":",Lc1)
##print("Chaines finissant par un",c2,":",Lc2)
##print("Chaines restantes :",Lc3)


##L = ["erreur","sys","echec"]
##if L[0]<L[1]:
##    max1=len(L[1])
##    nommax1=L[1]
##    max2=len(L[0])
##    nommax2=L[0]
##else:
##    max1=len(L[0])
##    nommax1=L[0]
##    max2=len(L[1])
##    nommax2=L[1]
##for e in L:
##    if len(e)>max1:
##        max2=max1
##        nommax2=nommax1
##        max1=len(e)
##        nommax1=e
##    elif max2<len(e)<=max1:
##        max2=len(e)
##        nommax2=e
##print("max1 =",nommax1)
##print("max2 =",nommax2)

def list_div_propre(n):
    i=1
    L=[]
    while i<=n:
        if n%i==0:
            L+=[i]
        i=i+1
    return L

def est_semi_premier(n):
    L=list_div_propre(n)
    i=0
    spr=True
    if len(L)-2<=1:
        spr=False
    else:
        while i < len(L)-1 and spr :
            if len(list_div_propre((L[i])))<=2:
                spr
            else:
                spr=False
            i=i+1
    return spr
        
def affiche_semi_premier(n):
    i=1
    while i<2**n:
        if est_semi_premier(i):
            print(i)
        i=i+1

def est_decalage(l1,l2):
    i=0
    pos1="h"
    condition=True
    while i<len(l1) and condition:
        if l1[0]==l2[i]:
            pos1=i
            condition=False
        i=i+1
    if pos1=="h":
        return False
    i=pos1
    j=0
    cond=True
    cpt=0
    while cpt<=len(l2) and cond:
        if i>=len(l2):
            i=i-len(l2)
        if j>=len(l2):
            j=j-len(l2)    
        if l1[j]==l2[i]:
            cpt=cpt+1
            i=i+1
            j=j+1
        else:
            cond=False
    return cond































