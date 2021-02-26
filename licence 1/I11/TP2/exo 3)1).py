t = "y"
while t == "y" :
    print("Valeur de a = ",end="")
    a = int(input())
    print("Choix d'operateur parmi (+,-,*,/) = ",end="")
    op = input()
    print("Valeur de b = ",end="")
    b = int(input())
    if op == "+":
      s = a + b
      print("Le resultat est", a , op , b ,"=",s)
      print("Cette expression est de type", type(s))
    elif op == "-":
      s = a - b
      print("Le resultat est", a , op , b ,"=",s)
      print("Cette expression est de type", type(s))
    elif op == "*":
      s = a * b
      print("Le resultat est", a , op , b ,"=",s)
      print("Cette expression est de type", type(s))
    else :
      s = a / b
      print("Le resultat est", a , op , b ,"=",s)
      print("Cette expression est de type", type(s))
      
    print("Vous voulez relancer la calculatrice ? [y/n] = ",end="")
    t = input()
