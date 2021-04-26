#!/usr/bin/python3
from sys import argv
def ordre(u, v):
    i = 0
    while (i < len(u) and i < len(v) and u[i] == v[i]):
        i += 1

    if(i == len(u) and i == len(v)):
        return 0
    elif(i == len(u) or (i<len(v) and v[i] > u[i])):
        return -1
    else:
        return 1

print(argv[0])

d = ordre(argv[1], argv[2])
if (d == -1):
    print(argv[1],"<",argv[2]);
if (d == 0):
    print(argv[1],"==",argv[2]);
if (d == 1):
    print(argv[1],">",argv[2]);
