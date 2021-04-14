s = int (input())
print("Nombre de secondes :", s)
h = s//3600
s = s%3600
m = s//60
s = s%60
print("Heures/minutes/secondes =",h,"h ",m,"m ",s,"s ")
