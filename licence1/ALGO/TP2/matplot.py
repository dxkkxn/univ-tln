import matplotlib.pyplot as plt
# On cree la liste des abscisses des point que l ’ on veut tracer
abscisse = []
for i in range(10):
    abscisse += [ i ]
# On cree la liste des ordonnees des points que l ’ on veut tracer :
carre = []
for i in range( len ( abscisse )):
    carre += [ abscisse [ i ]**2]
cube = []
for i in range ( len ( abscisse )):
    cube += [ abscisse [ i ]**3]
# plot () trace les courbes correspondantes et show () les affiche
# a l ’ ecran .
plt.plot( abscisse , carre , abscisse , cube )
plt.show()
