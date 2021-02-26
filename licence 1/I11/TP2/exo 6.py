t = 0
n = 0
r = 0
while r != 100:
    if t <= 10:
        r = n*t
        print(t ,"*",n,"=",r)
        t = t + 1
    else:
        n = n + 1
        t = 0
        print("La table de",n)
    
