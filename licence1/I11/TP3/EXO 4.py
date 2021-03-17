ch = input("La phrase : ")
i = 0
mots = 0
num = 0
while i<len(ch):
    if 48<=ord(ch[i])<=57:
        #i = i+1
        while i<len(ch) and 48<=ord(ch[i])<=57:
            i = i+1
        num = num + 1
    elif 97<=ord(ch[i])<=122:
        #i = i + 1
        while i<len(ch) and 97<=ord(ch[i])<=122:
            i = i + 1
        mots = mots + 1
    else :
        i = i + 1    
print(mots,num)
