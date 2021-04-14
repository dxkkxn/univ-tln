i = 0
t = 0
N = list(input())
while i < len(N) :
    t = t +in N[i]
    i = i + 1
str(t)
while len(t) > 2:
    h = 0
    i = 0
    while i < len(t):
        h = h + N[i]
        i = i + 1    
if h % 3 == 0:
    print("Divisible par 3")
else:
    print("N est pas divisible par 3")
