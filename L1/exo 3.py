ch = input("Entrer une heure : ")
h = int(ch[:2])
m = int(ch[3:])
htp = 16
mtp = 15
if h > htp:
    print("Vous etes en retard")
elif h == htp and m<mtp:
    print("Vous etes en retard")
elif h == htp and m == mtp:
    print("Vous etes a l heure")
else:
    print("Vous etes en avance")

