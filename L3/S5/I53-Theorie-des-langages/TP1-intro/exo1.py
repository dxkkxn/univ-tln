import dis
import time

def hello():
    print('Hello World')

#dis.dis(hello)

#dis.dis("x = 3 +int('2')")
"""
print("+")
dis.dis("x=3+int('3')")
print("-")
dis.dis("x=3-int('3')")
print("-")
dis.dis("x-int('3')")
print("*")
dis.dis("x=3*int('3')")
print("/")
dis.dis("x=3/int('3')")
print("//")
dis.dis("x=3//int('3')")
print("%")
dis.dis("x=3%int('3')")
print("**")
dis.dis("x=3**int('3')")
print("^")
dis.dis("x=3^int('3')")
print("&")
dis.dis("x=3&int('3')")
print("|")
dis.dis("x=3|int('3')")
print("==")
dis.dis("x=(3==int('3'))")
print("<")
dis.dis("x=(3<int('3'))")
"""
#exo1.2
"""
def if_elif_else():
    if False:
        print("a")
    elif False:
        print("b")
    else:
        print("c")

def if_else_2():
    if False:
        pass
    else:
        if False:
            pass
        else:
            print("c")


dis.dis(if_elif_else)
dis.dis(if_else_2)
"""

#exo1.3
"""
def for_f():
    x = 0
    for i in range(100_000_000):
        x += 1

def while_f():
    x = 0
    while(x<100_000_000):
        x += 1

dis.dis(while_f)
print("\n")
dis.dis(for_f)
print("\n")

start = time.time()
for_f()
end = time.time()
print("for toke",end-start,"seconds")

start = time.time()
while_f()
end = time.time()
print("while toke",end-start,"seconds")
"""

#exo1.4

def liste_1(n):
    l=[]
    for i in range(n):
        l = l + [i]

def liste_2(n):
    l=[]
    for i in range(n):
        l += [i]

def liste_3(n):
    l=[]
    for i in range(n):
        l.append(i)

def liste_4(n):
    l=[i for i in range(n)]


print("liste_1")
dis.dis(liste_1)

print("liste_2")
dis.dis(liste_2)

print("liste_3")
dis.dis(liste_3)

print("liste_4")
dis.dis(liste_4)

start = time.time()
liste_1(100_000)
end = time.time()
print("liste_1 toke", end-start, "seconds")

start = time.time()
liste_2(100_000)
end = time.time()
print("liste_2 toke", end-start, "seconds")

start = time.time()
liste_3(100_000)
end = time.time()
print("liste_3 toke", end-start, "seconds")

start = time.time()
liste_4(100_000)
end = time.time()
print("liste_4 toke", end-start, "seconds")
