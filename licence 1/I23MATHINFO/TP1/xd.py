#Question1
expression="!(p + q) * (!p + r) + (p * q)"
def ListerVariables(expression):
	Lc=[]
	L=sorted(expression)
	i=0
	alphabet="abcdefghijklmnopqrstuvwxyz"
	while i<len(L):
		if L[i] in alphabet and not(L[i]in Lc):
			Lc += L[i]
		i=i+1
	return Lc


#Question2
def DicoVariables(L):
	i=0
	dico={}
	while i<len(L):
		dico[L[i]]=i
		i=i+1
	return dico


#Question3
def Int2Bin(entier,n):    
    binaire=bin(entier)
    binaire=binaire[2:]
    if len(binaire)>n:
        return "error"
    elif len(binaire)==n:
        return binaire
    else:
        i=len(binaire)
        while i<n:
            binaire="0"+binaire
            i=i+1
        return binaire


#Question4
def Bin2Bool(bits):
	L=()
	i=0 
	while i<len(bits):
		if bits[i]=="0":
			L+=(False,)
		elif bits[i]=="1":
			L+=(True,)
		i=i+1
	return L
	

#Question5
def Math2Python(expression,vecteur,dicovar):
	i=0
	extrans=""
	while i<len(expression):
		if expression[i]=="!":
			extrans+="not "
		elif expression[i]=="*":
			extrans+="and"
		elif expression[i]=="+":
			extrans+="or"
		elif expression[i] in dicovar:
			extrans+=str(vecteur[dicovar[expression[i]]])
		else:
			extrans+= expression[i]
		i=i+1
	return extrans


#Question6
def TableVerite(expression,dicovar):
    i=0
    L=[]
    while i<2**len(dicovar):
        vecteur=Bin2Bool(Int2Bin(i,len(dicovar)))
        val=eval(Math2Python(expression,vecteur,dicovar))
        if val==False:	
            L+="0"
        else:
            L+="1"
        i+=1
    return L


#Question7
def AllTableVerite(expression,dicovar):
    i=0
    L=[]
    while i<2**len(dicovar):
        vectBin=Int2Bin(i,len(dicovar))
        vecteur=Bin2Bool(Int2Bin(i,len(dicovar)))
        val=eval(Math2Python(expression,vecteur,dicovar))
        if val==False:	
            L+=[[vectBin,0]]
        else:
            L+=[[vectBin,1]]
        i+=1
    return L


#Question8
def FND(TV,ListerVariables):
    i=0 
    str=""
    while i<len(TV):
        if TV[i][1]==1:
            j=0
            while j<len(TV[i][0]):
                print(TV[i][0][j])
                if TV[i][0][j]=="0":
                    str+=ListerVariables[j]+"\u0304"
                else:
                    str+=ListerVariables[j]
                j=j+1
            str+=" + "
        i=i+1
    return str[0:-2]

def FNC(TV,ListerVariables):
	i=0
	str=""
	while i<len(TV):
		if TV[i][1]==0:
			j=0
			while j<len(TV[i][0]):
				if TV[i][0][j]=="1":
					str+=ListerVariables[j]+"\u0304"
				else:
					str+=ListerVariables[j]
				j=j+1
				if j<len(TV[i][0]):
					str+= "+"
			
			str+=" * "
		i=i+1
	
	return str[0:-2]
print(FNC([['000', 1], ['001', 1], ['010', 0], ['011', 0], ['100', 0], ['101', 0], ['110', 1], ['111', 1]],["p","q","r"]))
#print(Int2Bin(0,3))
#print(AllTableVerite("!(p + q) * (!p + r) + (p * q)",{"p":0,"q":1,"r":2}))		
#print (Math2Python("!(p + q) * (!p + r) + (p * q)",(False,False,True),{"p":0,"q":1,"r":2}))
#print(Bin2Bool(Int2Bin(5,5)))
#print(DicoVariables(ListerVariables(expression)))
		
