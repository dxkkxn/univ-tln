import copy
alphabet = []
for i in range(26):
    alphabet.append(chr(97+i))

def chr2int_m(msg, size):
    format_msg = []
    for i in range(0,len(msg)-size+1, size):
        tmp_arr = []
        for letter in msg[i:i+size]:
            tmp_arr.append(alphabet.index(letter))
        format_msg.append(tmp_arr)
    return format_msg

def int2chr_m(msg):
    formated_msg = ""
    print(msg)
    for i in range(len(msg)):
        for j in range(len(msg[0])):
            formated_msg += alphabet[msg[i][j]]
    print(formated_msg)
    return formated_msg


def mult_matrix_vect(matrix, vect):
    matrix_l = len(matrix)
    matrix_c = len(matrix[0])
    assert(matrix_l == len(vect))
    res = [0]*matrix_l
    for i in range(matrix_l):
        for j in range(matrix_c):
            res[i] += matrix[i][j] * vect[j]
            res[i] %= 26
    return res

def crypt_hill(msg, k):
    formated_msg = chr2int_m(msg, len(k[0]))
    cyphered_msg = []
    for part_m in formated_msg:
        cyphered_msg.append(mult_matrix_vect(k, part_m))
    cyphered_msg_chr = int2chr_m(cyphered_msg)
    return cyphered_msg_chr

def decrypt_hill(msg, k):
    formated_msg = chr2int_m(msg, len(k[0]))
    cyphered_msg = []
    for part_m in formated_msg:
        cyphered_msg.append(mult_matrix_vect(k, part_m))
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
    length = len(M[0])
    M1 = deep_copy(M[:]

    for i in range(len(M)):
        M[i].extend([0]*i+[1]+[0]*(length-i-1))

    # matrix triang inf
    for i in range(length-1):
        main_pivot = M[i][i];
        for j in range(i+1,length):
            pivot_sup = M[j][i]
            for k in range(len(M[0])):
                M[j][k] = main_pivot*(M[j][k]) - pivot_sup*(M[i][k]);
                M[j][k] %= n


    # matrix triang sup
    for i in range(length-1,0,-1):
        main_pivot = M[i][i];
        for j in range(i-1,-1,-1):
            pivot_sup = M[j][i]
            for k in range(len(M[0])):
                M[j][k] = main_pivot*(M[j][k]) - pivot_sup*(M[i][k]);
                M[j][k] %= n

    for i in range(length):
        pivot = inverse(M[i][i], n)
        for k in range(len(M[0])):
            M[i][k] *= pivot
            M[i][k] %= n

    m_inv = []
    for i in range(len(M)):
        m_inv.append(M[i][length:])

    #assert(m_inv,
    print_matrice(M1)
    print_matrice(m_inv)

    return m_inv


#def known_key_attack(M, C):







#msg_chiffre = crypt_hill("texteachiffrer", [[1,1],[3,4]])
#print(msg_chiffre)
#msg_dechiffre = decrypt_hill(msg_chiffre, [[4,-1],[-3,1]])
#print(msg_dechiffre)

inv = inversion([[9,4],[5,7]], 29)
m = [[9,4],[5,7]]
print_matrice(matmat(m, inv, 29))


