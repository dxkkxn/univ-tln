a = int(input())
somme_im = 0
somme_p = 0
while a != 0:
    
    if a%2 != 0:
        somme_im = somme_im + a
    else:
        somme_p = somme_p + a
    a = int(input())
print("Somme des Impaires = ", somme_im)
print("Somme des paires = ", somme_p)


        
            
