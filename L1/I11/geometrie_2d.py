#I11 BENJELLOUN 11/12/2019
from math import *
from vecteur import *
from pocketgl import *
def mat_rotation_2d(theta):
    tup=[(cos(theta),-sin(theta)),(sin(theta),cos(theta))]
    tup=tuple(tup)
    return tup
def rotation_point_2d(p,c,theta):
    vec=(p[0]-c[0],p[1]-c[1])
    ox=vec
    tup=mat_rotation_2d(theta)
    oxrotation= prod_mat_vec(ox,tup)
    p=[oxrotation[0]+c[0],oxrotation[1]+c[1]]
    return p

def dessine_polygone_2d(pol):
    line(pol[0][0],pol[0][1],pol[1][0],pol[1][1])
    line(pol[1][0],pol[1][1],pol[2][0],pol[2][1])
    line(pol[2][0],pol[2][1],pol[3][0],pol[3][1])
    line(pol[3][0],pol[3][1],pol[0][0],pol[0][1])
def rotation_polygone_2d(p,c,theta):
    i=0
    p_rotes=[]
    print(type(p))
    while i<len(p):
        t=rotation_point_2d(p[i],c,theta)
        p_rotes += [t]
        i=i+1
    p_rotes = tuple(p_rotes)
    return p_rotes


from geometrie_2d import rotation_polygone_2d , dessine_polygone_2d
from math import pi
from time import sleep
theta = pi /32
C =(250 ,250)
P =[(300 ,300) ,(200 ,300) ,(200 ,200) ,(300 ,200)]
init_window ("Rotation 2D", 500 , 500)

while True :
    P=rotation_polygone_2d(P,C,theta)
    dessine_polygone_2d(P)
    refresh()
    sleep(0.05)
    clear_screen()
main_loop()
