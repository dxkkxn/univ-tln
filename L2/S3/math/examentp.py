def table_alpha(P):
    degree_poly = len(bin(P))-3
    nbr_elements = (1<<degree_poly) -1
    L     = [0]*nbr_elements
    L[0]  = 1
    alpha = 1
    i     = 1
    while i < nbr_elements:
        alpha = multbyalpha(alpha,2,P)
        L[i] = alpha
        i+=1
    return L
def multiplie(b, c, f):
  res = 0
  t = b
  k = c
  while t != 0:
    if (t & 1) != 0:
      res ^= k
    k = multbyalpha(k,f)
    t = t >> 1
  return res

def multbyalpha(b, f):
  t = b << 1
  n = len(bin(f)) - 3
  if t & (1<<n) != 0:
    return t^f
  else:
    return t
def table_log(P):
  liste_log = [-1,0,1]
  r = len(bin(P))-3
  elements = 1 << r
  j = 0
  while j < elements - 3:
    liste_log.append(0)
    j += 1
  i = 1
  exp = 1
  while i < elements -1 :
    exp = multbyalpha(exp,P)
    liste_log[exp] = i
    i += 1
  return liste_log
print(table_log(13))

def evalue(Q,y,P):
    res = Q[0]
    for i in range(1,len(Q)):
        res = multiplie(res,y,P)^Q[i]
    return res
print(evalue([4,3,6], 2, 13))

def inverse(x,P):
    degree_poly = len(bin(P))-3
    nbr_elements = (1<<degree_poly) -1
    alpha = log_table[x]
    alpha = alpha<<(nbr_elements-1)
    return alpha_table[alpha]

def decompose(n):
    listePremier = []
    cpt = 0
    if n%2 == 0:
        while n%2 == 0:
            n = n//2
            cpt +=1
        listePremier += [[2,cpt]]
    i = 3
    while n != 1 :
        if n%i == 0 :
            cpt = 0
            while n % i == 0 :
                n = n // i
                cpt+=1
            listePremier += [[i,cpt]]
        i += 2
    return listePremier

def decomposebin(n):
    L = []
    while n != 0:
        L.insert(0,n&1)
        n = n >> 1
    return L
print(decomposebin(23))
