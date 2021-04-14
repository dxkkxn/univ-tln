def factorielle(n):
    res = 1
    i = 1
    while n > 1:
        res *= n
        n -= 1
    return res

def triangle_pascal(n):
    res = [0]*(n+1)
    res[0] = 1
    i = 0
    for i in range(1, len(res)):
        for k in range(i):
            print(f"i = {i} k={k}")
            res[i-k] = res[i-k] + res[i-k-1]
    return res

def phoque(n):
    if (n == 0):
        return []
    elif (n == 1):
        return ['.']
    elif (n == 2):
        return ["..", '_']
    else:
        return ['.' + x for x in phoque(n-1)] + ['_' + x for x in phoque(n-2)]


def phoqueit(n):
    L = []
    A = ['.']
    B = ['..', '_']
    if n == 1:
        return A
    if n == 2:
        return B
    else:
        for i in range(3, n+1):
            L = ['.' + x for x in B] + ['_' + x for x in A]
            A = B
            B = L
    return L

def fibonacci(n):
    res = [0,1]
    for i in range(1, n):
        res.append(res[i-1]+res[i])
    return tuple(res)

def genuplet(n, m, nuplet):
    if n == 0:
        print(nuplet)
    else:
        for i in range(1, m+1):
            genuplet(n-1, m, nuplet+(i,))

genuplet(3,5,())


