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






msg_chiffre = crypt_hill("texteachiffrer", [[1,1],[3,4]])
print(msg_chiffre)
msg_dechiffre = decrypt_hill(msg_chiffre, [[4,-1],[-3,1]])
print(msg_dechiffre)


