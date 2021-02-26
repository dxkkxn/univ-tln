from random import *
def randomde():
    l=[0,0,0,0,0,0]
    b=0
    while b<1000 :
        a=randrange(0,6)
        l[a] = l[a] + 1
        b = b +1
    return(l)
l1 = randomde()
l2 = randomde()
from pocketgl import *
init_window("histogramme",500,500)

i=0
a=40
while i<len(l1):
    current_color(randrange(0,256),randrange(0,256),randrange(0,256))
    box(a,0,a+75,l1[i]+l2[i])
    i=i+1
    a=a+70
    
    
    
    
    


