nombre = 1
np = 0
t = nombre - 1
sp = 0
while nombre < 10000:
    t = nombre - 1
    sp = 0
    while t > 0 :
        if nombre % t == 0:
            sp = sp + t
        t = t - 1
        #else :
        #    t = t - 1
    if sp == nombre:
        print(sp)
    nombre = nombre + 1
    #else :
     #   nombre = nombre + 1    
