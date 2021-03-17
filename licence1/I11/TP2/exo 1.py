note = int(input())
if note < 10 :
    print("Vous avez raté le examen")
elif note >= 12 and note < 14 :
    print("Vous avez reussi votre examen avec une mention Assez bien")
elif note >= 14 and note < 16 :
    print("Vous avez reussi votre examen avec une mention Bien")
else :
    print("Vous avez reussi votre examen avec une mention Tres Bien")
