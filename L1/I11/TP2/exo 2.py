a = float(input())
b = float(input())
c = float(input())
moyenne = (a+b+c)/3
if moyenne > 10 :
    if a < 10 or b < 10 or c < 10:
        print("La moyenne est :",moyenne,"par compesation")
    else:
        print("La moyenne est :",moyenne)
else:
    print("La moyenne est :",moyenne,"sesion de ratrapage")
    
