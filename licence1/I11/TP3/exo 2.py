ch = input ("saisir une chaine de caracteres : ")
i = 0
copie  = ""
j = -1
sansespace = ""
while -j <= len(ch):
    if ch[j] == " ":
        copie = copie
        if ch[i] == " ":
            sansespace = sansespace
        else:
            sansespace = sansespace + ch[i]
        
    else:
        if ch[i] == " ":
            sansespace = sansespace
        else:
            sansespace = sansespace + ch[i]
        copie = copie + ch[j]
    i = i + 1
    j = j - 1
if copie == sansespace:
    print("Palindrome",sansespace,copie)
else:
    print("Pas palindrome",sansespace,copie)
        


     
     
