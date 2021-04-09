from math import gcd
from cesar import cypher_cesar, decypher_cesar, frequent_letter

alphabet = []
for i in range(26):
    alphabet.append(chr(97+i));

def cypher_vigenere(msg, key):
    cyphered_msg = ""
    for i in range(len(msg)):
        key_int = alphabet.index(key[i % len(key)])
        char_int = alphabet.index(msg[i])
        cyphered_msg += alphabet[(char_int + key_int) % 26]
    return cyphered_msg



def decypher_vigenere(msg, key):
    decyphered_msg = ""
    for i in range(len(msg)):
        key_int = alphabet.index(key[i % len(key)])
        char_int = alphabet.index(msg[i])
        decyphered_msg += alphabet[(char_int - key_int) % 26]
    return decyphered_msg

"""
m = "uyhxcwtsohwzsfayiezvlduqejgomxtvekpjjgstgdkyjvcgdhbtvfwyhldgvudwogepcylocirtnzciitvfjytrwqceysijrswltikelhuqpvfpllpmkgcdyhmehzjgpxzqykujrvxtlyhwvlleuxwrvewccxvvzmmaijqcvccekgfjmtrvvlaycxvsfajtwcgnjypxvwcgzumtkpdfthiuewqpvkflnchrvvlanqmvpdmleejcfuijvrpevyaegtpkycgvfphltplfpvucwjqyhldnvvajyayuglnuxxjkxhftqvpekovkvtpdyviigxwhielfcwhbsukqaucxcgrwltqvpekyhhfefeycxj"
k = "supercl"
"""
#print(frequent_letter(m))
#print(decypher(m, k))
#print(cypher(decypher(m, k), k) == m)


def len_key(l, msg):
    dico = {}
    max_nplet = 0
    for i in range(len(msg)-l+1):
        if dico.get(msg[i:i+l]):
            dico[msg[i:i+l]] += 1
            if dico[msg[i:i+l]] > max_nplet:
                max_nuplet = dico[msg[i:i+l]]
                max_pattern = msg[i:i+l]
        else:
            dico[msg[i:i+l]] = 1

    l_index = []
    i = 0
    while i < len(msg)-l+1:
        if max_pattern == msg[i:i+l]:
            l_index.append(i)
            i = i+l
        else:
            i += 1

    gcd1 = l_index[0]
    for i in range(1,len(l_index)):
        gcd1 = gcd(gcd1, l_index[i])
    return gcd1




    #print(dico, max_pattern, l_index)

def kasiski(l,m):
    key_l = len_key(l,m)
    print(key_l)
    sub_str = [""]*(len(m)//key_l-1)
    for i in range(len(m)):
        sub_str[i%key_l] += m[i]
    sub_str_dec = []
    for i in range(len(sub_str)):
        print('----',sub_str)
        l_freq = frequent_letter(sub_str[i])
        key = alphabet.index(l_freq)
        e = alphabet.index('e')
        possible_key = alphabet[(key - e) % 26]
        sub_str_dec.append(decypher_cesar(sub_str[i], possible_key))
    print(sub_str_dec)

m = "pbcjbjcrgwisiixrbrgxwquplcptgfiaeeamcftxqbnvisiyceteadxxfqwxgbsvnrzhkyjoeoxrqpckwrbummquvbskmcbwrngfijenxxqrgwyjeuledeeeefrrxyqswbzxnvlemoubxfopweksexpriebiqrgkijpntgbertvaeueiqttxwaihyioepmipcqgxoakkijepmernurwqeoxhbcjbjcrgfiktohrlanilxbgmmnugvsjmgeizhkyjoefxgbsckurinnxflklizerxraapmglmoxglmrhwxnvnraeetpxgg"
m1 = "mbtgmrgylrmbtntynfsydskxdmbtzfk"
print(len_key(2,m))

print(len_key(2,m1))
#kasiski(2,m)
