import copy
import random
from math import gcd
alphabet = []
for i in range(26):
    alphabet.append(chr(97+i))
alphabet.append(",")
alphabet.append(" ")
alphabet.append(".")

#decoupage du msg en taille size et conversion de int to char
def chr2int_m(msg, size):
    format_msg = []
    for i in range(0,len(msg)-size+1, size):
        tmp_arr = []
        for letter in msg[i:i+size]:
            tmp_arr.append(alphabet.index(letter))
        format_msg.append(tmp_arr)
    return format_msg

#conversion du msg de int to str
def int2chr_m(msg):
    formated_msg = ""
    for i in range(len(msg)):
        for j in range(len(msg[0])):
            formated_msg += alphabet[msg[i][j]]
    return formated_msg

def is_inv(num, n):
    return gcd(num,n) == 1

def mult_matrix_vect(matrix, vect, n):
    matrix_l = len(matrix)
    matrix_c = len(matrix[0])
    assert(matrix_l == len(vect))
    res = [0]*matrix_l
    for i in range(matrix_l):
        for j in range(matrix_c):
            res[i] += matrix[i][j] * vect[j]
            res[i] %= n
    return res

def crypt_hill(msg, k, n):
    formated_msg = chr2int_m(msg, len(k[0]))
    cyphered_msg = []
    for part_m in formated_msg:
        cyphered_msg.append(mult_matrix_vect(k, part_m, n))
    cyphered_msg_chr = int2chr_m(cyphered_msg)
    return cyphered_msg_chr

def decrypt_hill(msg, k, n):
    formated_msg = chr2int_m(msg, len(k[0]))
    cyphered_msg = []
    for part_m in formated_msg:
        cyphered_msg.append(mult_matrix_vect(k, part_m, n))
    cyphered_msg_chr = int2chr_m(cyphered_msg)
    return cyphered_msg_chr

def print_matrice(M):
    for i in range(len(M)):
        print(M[i])

def inverse(a,p):
    u0 = 1
    u1 = 0
    v0 = 0
    v1 = 1
    tmpp=p
    while a%p != 0:
        q = a//p
        a, p = p, a % p
        tmpu1 = u1
        tmpv1 = v1
        u1, v1 = u0-q*u1, v0-q*v1
        u0,v0 = tmpu1,tmpv1
    return u1%tmpp
def matmat(A, B, n):
    assert(len(A) == len(B))
    C = []
    for i in range(len(A)):
        L = []
        for j in range(len(B[0])):
            res = 0
            for k in range(len(B)):
                res += A[i][k]*B[k][j]
                res %= n
            L.append(res)
        C.append(L)
    return C

def inversion(M,n):
    assert(len(M) == len(M[0]))
    length = len(M)
    M1 = copy.deepcopy(M)
    INV = []
    for i in range(length):
        INV.append([0]*i+[1]+[0]*(length-i-1))

    # matrix triang inf
    for i in range(length):
        #calcul de pivot et permutation
        main_pivot = M1[i][i];
        i_piv = i
        while i_piv < length and not is_inv(main_pivot,n):
            i_piv += 1
            main_pivot = M1[i_piv][i]
        if i_piv == length:
            print("La matrice n'est pas inversible")
            return [];
        else:
            M1[i], M1[i_piv] = M1[i_piv],M1[i]
            INV[i], INV[i_piv] = INV[i_piv],INV[i]

        for j in range(i+1,length):
            pivot_sup = M1[j][i]
            for k in range(length):
                M1[j][k] = main_pivot*(M1[j][k]) - pivot_sup*(M1[i][k]);
                INV[j][k] = main_pivot*(INV[j][k]) - pivot_sup*(INV[i][k]);
                M1[j][k] %= n
                INV[j][k] %= n

    # matrix triang sup
    for i in range(length-1,0,-1):
        main_pivot = M1[i][i];
        for j in range(i-1,-1,-1):
            pivot_sup = M1[j][i]
            for k in range(length):
                M1[j][k] = main_pivot*(M1[j][k]) - pivot_sup*(M1[i][k]);
                INV[j][k] = main_pivot*(INV[j][k]) - pivot_sup*(INV[i][k]);
                M1[j][k] %= n
                INV[j][k] %= n

    for i in range(length):
        pivot = inverse(M1[i][i], n)
        for k in range(length):
            M1[i][k] = (pivot*M1[i][k]) % n
            INV[i][k] = (pivot*INV[i][k]) % n

    assert(matmat(INV,M,n) == M1)
    return INV

def cryptoanalysis(C,M,n):
    inv = inversion(M,n)
    K = matmat(C,inv,n)
    return K

"""
#1 exo
m = "pfjgflgpbvlhxiimynolvztxvsgodmcusqkhuksgumnzktdhuqlqkhmhfujuapdsahthmmtpjjjgtuoxzuignqecqzunkgaikhxervuksoyxuqlfhgnnljnrjlimelnfsugvuclpldproiurmwbbdrmxtoepsgfmhfetoerwqzbbjxjxjiehrhjzzyxvicavizqoyiunkesvakmkcqqujqkhaozqzbbdrgdznyewkwguzqkhhbgofrtjgsjlhdyzrllzuxiibnegczvbxuksslaapdgcejgizvggwhobjdcz"
m1 = "touslesdixmetresunepancarteindiquaitquecegrillageetaitelectrifieunpetitcheminlongeaitlesgrillagesdechaquecoteetlonpouvaityvoirdetempsentempsdeuxgardesarmesfaireleurrondelaroutesemblaitinterminablecaillouteuseasouhaitaudeladesgrillagescetaitlaforetuneforetbienentretenuepresqueartificiellepensadavidzz"
M = [ ['h','g','m'], ['l','d','c'], ['t','f','b']]
C = [ ['b','a','a'], ['a','b','a'], ['a','a','b']]
for i in range(len(C)):
    for j in range(len(C)):
        C[i][j] = alphabet.index(C[i][j])
        M[i][j] = alphabet.index(M[i][j])
print_matrice(C)
print('m')
print_matrice(M)
print('K')
K = cryptoanalysis(C,M,26)
print('inv')
print_matrice(K)
print(decrypt_hill(m,K,26))
# la matrice cle est
[23, 12, 12]
[19, 13, 6]
[14, 19, 3]
# le msg est
touslesdixmetresunepancarteindiquaitquecegrillageetaitelectrifieunpetitcheminlongeaitlesgrillagesdechaquecoteetlonpouvaityvoirdetempsentempsdeuxgardesarmesfaireleurrondelaroutesemblaitinterminablecaillouteuseasouhaitaudeladesgrillagescetaitlaforetuneforetbienentretenuepresqueartificiellepensadavidzz
"""

#EXO 2
def gentrianginf_inv(n, t):
    L = []
    for i in range(n):
      sous_liste = [0]*n
      for j in range(i):
        sous_liste[j] = random.randrange(0,t)
      sous_liste[i] = random.randrange(1,t)
      L.append(sous_liste)
    return L

def transpose(M):
    L = []
    for i in range(len(M[0])):
        sous_liste = []
        for j in range(len(M)):
            sous_liste.append(M[j][i])
        L.append(sous_liste)
    return L

#une condition suffisante pour que une matrice soit inversible est que le det soit inversible dans l'ensemble
#le produit de 2 matrice inv la matrice resultant est inv
def genmatrix_inv(n):
  m = gentrianginf_inv(n, 29)
  b = gentrianginf_inv(n, 29)
  b_t = transpose(b)
  C = matmat(m,b_t,29)
  return C

def gen_cle_hill(n):
    M = genmatrix_inv(3)
    b = []
    for i in range(n):
        b.append(random.randrange(29))
    M.append(b)
    return M

#exo 3
def hill_affine_chiffre(texte, cle):
    texte_int = chr2int_m(texte, len(cle[0]))
    for i in range(len(texte_int)):
        texte_int[i] = mult_matrix_vect(cle[:-1], texte_int[i], 29)
        assert(len(texte_int[i]) == len(cle[-1]))
        for j in range(len(cle[-1])):
            texte_int[i][j] += cle[-1][j]
            texte_int[i][j] %= 29
    texte_str = int2chr_m(texte_int)
    return texte_str

#exo4
def hill_affine_dechiffre(texte, cle):
    texte_int = chr2int_m(texte, len(cle)-1)
    print(texte_int)
    for i in range(len(texte_int)):
        assert(len(texte_int[i]) == len(cle[-1]))
        #soustraction
        for j in range(len(cle[-1])):
            texte_int[i][j] -= cle[-1][j]
            texte_int[i][j] %= 29
        #multiplication
        texte_int[i] = mult_matrix_vect(cle[:-1], texte_int[i], 29)
    texte_str = int2chr_m(texte_int)
    return texte_str

### main
K = gen_cle_hill(3)
K = K[:-1]
INV = inversion(K,29)
print(K, INV, matmat(K,INV,29))

"""
### main
K = gen_cle_hill(3)
K1 = copy.deepcopy(K)
K_inv = inversion(K1[:-1], 29)
print("K=")
print_matrice(K)
K_inv.append(K[-1])
print('\n')

print("Kinv=")
print_matrice(K_inv)
m = "abcdefghijklmnopqrs"
m_chiffre = hill_affine_chiffre(m,K)
print(m_chiffre)
m_dechiffre = hill_affine_dechiffre(m_chiffre,K_inv)
print(m_dechiffre)
"""


#exo5
def hill_affine_chiffre_en_chaine(texte, cle):
    #generation du vect aleatoire
    random_vect = []
    for i in range(len(cle[0])):
        random_vect.append(random.randrange(29))
    texte_int = chr2int_m(texte, len(cle[0]))
    texte_int.insert(0,random_vect)
    #exor
    for i in range(1,len(texte_int)):
        for j in range(len(texte_int[i])):
            texte_int[i][j] ^= texte_int[i-1][j]
            texte_int[i][j] %= 29
        texte_int[i] = mult_matrix_vect(cle[:-1], texte_int[i], 29)
        assert(len(texte_int[i]) == len(cle[-1]))
        for j in range(len(cle[-1])):
            texte_int[i][j] += cle[-1][j]
            texte_int[i][j] %= 29
    texte_str = int2chr_m(texte_int)
    return texte_str

#exo6
def hill_affine_dechiffre_en_chaine(texte, cle):
    texte_int = chr2int_m(texte,len(cle[0]))
    #dechiffrement clasique
    for i in range(len(texte_int)-1, 0, -1):
        for j in range(len(cle[-1])):
            texte_int[i][j] -= cle[-1][j]
            texte_int[i][j] %= 29
        texte_int[i] = mult_matrix_vect(cle[:-1], texte_int[i], 29)
        #exor du bloc precedant
        for j in range(len(cle[-1])):
            texte_int[i][j] ^= texte_int[i-1][j]
            texte_int[i][j] %= 29
    texte_str = int2chr_m(texte_int)
    return texte_str[len(cle[0]):]

"""
### main
K = gen_cle_hill(3)
K1 = copy.deepcopy(K)
K_inv = inversion(K1[:-1], 29)
print("K=")
print_matrice(K)
K_inv.append(K[-1])
print('\n')

print("Kinv=")
print_matrice(K_inv)
m = "abcdefghijklmnopqrs"
m_chiffre = hill_affine_chiffre_en_chaine(m,K)
print(m_chiffre)
m_dechiffre = hill_affine_dechiffre_en_chaine(m_chiffre,K_inv)
print(m_dechiffre)
"""
