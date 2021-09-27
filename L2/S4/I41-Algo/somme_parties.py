def fact(n) :
    res = 1
    for i in range(1,n+1):
        res *= i
    return res

def binome_newton(n,p):
    return (fact(n)/(fact(n-p)*fact(p)))

res = 0
for i in range(1,11):
    res += binome_newton(10,i)

print(res)

