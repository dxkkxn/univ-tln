#I11 BENJELLOUN 11/12/2019
from math import *
from vecteur import *
def math_rotation_3dx(theta):
    tpx= [(1,0,0),(0,(cos(theta)),-sin(theta)),(0,sin(theta),cos(theta))]
    tpx=tuple(tpx)
    return tpx
def math_rotation_3dy(theta):
    tpy= [(cos(theta),0,-sin(theta)),(0,1,0),(sin(theta),0,cos(theta))]
    tpy=tuple(tpy)
    return tpy
def math_rotation_3dz(theta):
    tpz= [((cos(theta)),-sin(theta),0),(sin(theta),cos(theta),0),(0,0,1)]
    tpz=tuple(tpz)
    return tpz
def rotation_point_3dx(p,c,theta):
    cp=[p[0]-c[0],p[1]-c[1],p[2]-c[2]]
    op=cp
    rotation=math_rotation_3dx(theta)
    p1=prod_mat_vec(op,rotation)
    p2=somme_vec(p1,c)
    return p2
    
    
