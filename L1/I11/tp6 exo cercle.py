from random import *
from pocketgl import *
init_window("cercle",1000,1000)
circle(0,0,1000)
n=0
N=0
while N<=100:
    x,y=random(),random()
    print(x, y)
    
    dis=(x**2+y**2)**0.5
    if dis<1:
        n=n+1
        current_color("green")
        #print(x*500)
        #print(y*500)
        point(x*1000,y*1000)
    else:
        current_color("red")
        #print(x*500)
        #print(y*500)
        point(x*1000,y*1000)
    N=N+1
pi=4*n/N
print(pi)
