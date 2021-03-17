print("a = ",end="")
a = float(input())
print("b = ",end="")
b = float(input())
print("c = ",end="")
c = float(input())
d = 2*a
r2 = (b**2)*-4*a*c
if a == 0 and b == 0 and c == 0:
    print("Solution tous les nombres")
elif d == 0:
    print("Pas de solution reél")
elif r2 < 0:
    print("Pas de solution reél")
else:
    x1 = (-b + r2**0.5)/d
    x2 = (-b - r2**0.5)/d
    print("Solution 1 =",x1,"Solution 2=",x2)
