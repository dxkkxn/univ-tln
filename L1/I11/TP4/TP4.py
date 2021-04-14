
u = (1.0,2.0,-1.0,0.5)
v = (2.0,5.0,9.5,-2.0)
i=0
r2v = 0
r2u = 0
pe = 0
while i<len(u):
    pe = pe + (u[i]*v[i])
    i = i+1
i=0
while i<len(u):
    r2u = r2u + (u[i])**2
    i = i+1
i=0
while i<len(v):
    r2v = r2v + (v[i]**2)
    i = i+1

print(pe/(r2u*r2v))
