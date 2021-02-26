def Affiche(c):
    print("X = ",str(c[0]).replace("'",''))
    print("G = ",str(c[1]).replace("'",''))
    print("Y = ",str(c[2]).replace("'",''),end='\n\n')





def Lecture(nomfichier):
  fichier = open(nomfichier,"r")
  liste = fichier.readlines()
  i=0
  liste1=[]
  while i<len(liste):
    liste1+=[liste[i].rstrip().split("\n")]
    i=i+1
  X=set()
  G={}
  Y=set()
  for i in liste1:
    if len(i[0])==3:

      X=X|set(i[0][0])
      Y=Y|set(i[0][2])
      if not(i[0][0] in G):
        G[i[0][0]]=set(i[0][2])
      else:
        G[i[0][0]]=G[i[0][0]]|set(i[0][2])
    elif i[0][0].isalpha():
        X=X|set(i[0][0])
    else:
      Y=Y|set(i[0][1])

  return (X,G,Y)


#Renvoie la cor­res­pon­dan­ce réciproque de celle passée en paramètre.
def Reciproque(C):
  print(C)
  recidic={}
  for (cle,val) in C[1].items():
    for i in val:
      if i in recidic:
        recidic[i]=recidic[i]|set(cle)
      else:
        recidic[i]=set(cle)

  return (C[2],recidic,C[0])


#Renvoie l'image directe d'une partie A de l'ensemble de départ de la cor­res­pon­dan­ce C passée en paramètre.
def ImageDirecte(C,A):
    id=set()
    for i in A:
        if i in C[1]:
            id= id|C[1][i]
    return id
#Renvoie l'image réciproque d'une partie B de l'ensemble d'arrivée de la cor­res­pon­dan­ce C passée en paramètre.
def ImageReciproque(C,B):
    Cre=Reciproque(C)
    print(Cre)
    ir=set()
    for i in B:
        if i in Cre:
            ir= ir|Cre[i]
    return ir

def composer(g,f):
    print(g,f)
    dic={}
    for (clef,valf) in g[1].items:
        for valf in f[1]:
            dic[clef]=valf
    return(g[0],dic,f[2])


def EstFonction(C):
    for i in C[1]:
        if len(C[1][i])>=2:
            return False
        else:
            return True
def EstApplication(C):
    bool=True
    for i in C[0]:
        if not(i in C[1]):
            bool=False
    return bool

print(composer(Lecture("test"),Reciproque(Lecture("test"))))
#print(EstFonction(Lecture("test")))
#print(Affiche(Lecture("test")))
#print(ImageReciproque(Lecture("test"),{"4","2","3"}))
#print(ImageDirecte(Lecture("test"),{"a","b"}))
#print(Reciproque(Lecture("test")))
