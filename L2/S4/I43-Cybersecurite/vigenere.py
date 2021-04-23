from math import gcd, sqrt
from time import sleep
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

def search_pattern(msg, l):
    dico = {}
    max_nplet = 1
    prec_pattern = msg[0:l]

    for i in range(len(msg)-l+1):
        if dico.get(msg[i:i+l]) and msg[i:i+l] != prec_pattern:
            dico[msg[i:i+l]] += 1
            if dico[msg[i:i+l]] > max_nplet:
                max_nuplet = dico[msg[i:i+l]]
                max_pattern = msg[i:i+l]
        else:
            dico[msg[i:i+l]] = 1
        prec_pattern = msg[i:i+l]

    list_patterns = [max_pattern]
    for key, val in dico.items():
        if val == max_nuplet and key not in list_patterns:
            list_patterns.append(key)
    print(list_patterns)
    return list_patterns

def prime_div(num):
    prime_factors = []
    add2 = False
    while num % 2 == 0:
        num /= 2
        add2 = True
    if add2:
        prime_factors.append(2)

    for i in range(3, int(sqrt(num))+1, 2):
        add  = False
        while num % i == 0:
            num /= i
            add = True
        if add:
            prime_factors.append(int(i))
    if num > 2:
        prime_factors.append(int(num))
    return prime_factors


def len_key(msg, l):
    list_patterns = search_pattern(msg, l)
    l_index = []
    i = 0
    pos_key_len = set()
    for pattern in list_patterns:
        while i < len(msg)-l+1:
            if pattern == msg[i:i+l]:
                l_index.append(i)
                i = i+l
            else:
                i += 1

        dist = []
        for i in range(1,len(l_index)):
            while (i > 0):
                dist.append(l_index[i]-l_index[i-1])
                i -= 1
        gcd1 = dist[0]
        for i in range(1,len(dist)):
            gcd1 = gcd(gcd1, dist[i])
        divisors = prime_div(gcd1)
        for div in divisors:
            pos_key_len.add(div)
    return list(pos_key_len)




    #print(dico, max_pattern, l_index)

def kasiski(m, l):
    possible_keys = len_key(m, l)
    all_pos_keys = []
    for key_l in possible_keys:
        sub_str = [""]*key_l
        for i in range(len(m)):
            sub_str[i%key_l] += m[i]
        sub_str_dec = []
        key_res = [""]
        for i in range(len(sub_str)):
            list_l_freq = frequent_letter(sub_str[i])
            key_res *= len(list_l_freq)
            for i in range(len(list_l_freq)):
                key = alphabet.index(list_l_freq[i])
                e = alphabet.index('e')
                res =  alphabet[(key - e) % 26]
                if len(list_l_freq) == len(key_res):
                    key_res[i] += res
                else:
                    j = i*len(list_l_freq)
                    for _ in range(len(list_l_freq)):
                        key_res[j] += res
                        j+=1
        all_pos_keys.extend(key_res)
        all_pos_keys = list(set(all_pos_keys))
    return all_pos_keys

m_ = "pbcjbjcrgwisiixrbrgxwquplcptgfiaeeamcftxqbnvisiyceteadxxfqwxgbsvnrzhkyjoeoxrqpckwrbummquvbskmcbwrngfijenxxqrgwyjeuledeeeefrrxyqswbzxnvlemoubxfopweksexpriebiqrgkijpntgbertvaeueiqttxwaihyioepmipcqgxoakkijepmernurwqeoxhbcjbjcrgfiktohrlanilxbgmmnugvsjmgeizhkyjoefxgbsckurinnxflklizerxraapmglmoxglmrhwxnvnraeetpxgg"
m1 = "mbtgmrgylrmbtntynfsydskxdmbtzfk"
m2 = "uyhxcwtsohwzsfayiezvlduqejgomxtvekpjjgstgdkyjvcgdhbtvfwyhldgvudwogepcylocirtnzciitvfjytrwqceysijrswltikelhuqpvfpllpmkgcdyhmehzjgpxzqykujrvxtlyhwvlleuxwrvewccxvvzmmaijqcvccekgfjmtrvvlaycxvsfajtwcgnjypxvwcgzumtkpdfthiuewqpvkflnchrvvlanqmvpdmleejcfuijvrpevyaegtpkycgvfphltplfpvucwjqyhldnvvajyayuglnuxxjkxhftqvpekovkvtpdyviigxwhielfcwhbsukqaucxcgrwltqvpekyhhfefeycxj"

m ="cyttprimnwcnshbrvgxtqcrhgaeucrvuomayewfppnpeiuoirutebtrjmqiecediawnpttcqwfpqjmpspyenmfepnixwbqopmquvqgomwyrrhlmyfntnftflghgdpnpeiuyssnweolmxygiqfzjlgwnpwuucmgcwxiaxrzywfntnftflghgdrtnrwrcmxyfwwcpjpvjfptzcfpcnlfnqiepxyyfeezgmyrxuzryjyyuavtwuiuoiquqiezquifmvtssgnmuaewzbmutprygpgyiexrhcywjnfeofwjxnzqtvzhwswcizxrwkoijmnyudmlyamcwixoaixzmyoeixprfcghccvnprvfppfogvgnsyyqinlfflemgcizhrtgcwthaiuzvycgypxmqcgekcinfrxctxhizqgoesmyiuqmqgfhgryjleirprxuqexthqyfhgnswugmqywwyztntwxuvipepfpnrvoixuiiueinfferavtwuefppfpbmvfvjihwgevtoiekehfpvhnpgmuhjhpywihzttxqusippxwypinlvjmfiompfcgewikwifstomsugiwcwvorhcgmiuieketzpbmtoesmqiuqmqgfhgdgnyaggqmhnvspmifopswahjjrxkeixfhqkpvjmvrftuzuvipeuzcyivlmyyajqygycbrcwegufiwyixiexgoevonvkfqfpnmvpxjcawvlpqygsweeznbytniwnnmppqjhgpgdcxnrqgoiwysvqthnmfioprywnvfpwgoypgdqthgekprymnrunixmrttpyaydygwiforxctxjhrfwwpnnvspdszxnmpoeacqvgdxfvbyesigyryppztckgcgiwhryupwtlgmgoixypvcywtoiiplmyxrwcqjnwuitwirigttppzxrpcdgjhfiwchjgnvtlxtogwgfpfjeiubyjfntqcxjmrwqtxkyeqgpmqxrwepriuvxkwrfleivlmyjnwfphjmpipovjjhmutpxuevgeejhsmpweuiexgdszpemvpxiuimfpyyfnwvftjoehgdeacrhggesnyykdiiycpqjennhrezqufrbgtrkieqcemvoryppznhtxctrjxrtgcwthaiudiiycpcnenyaxffruifxglpfogvgciluehcyxfoceudelyyiupgwuawipesnfqwcezrfmvfixuhjqyhiyyeulpqyvpalzfcgfkprzhrgkyuzuaxctrjxbvftrfnrytdgnhdiecesmticyxxygwkeyjyaxtppjmrgtlrxarepewjnyiuzvicaevpywmhrgxehbvrgcmjczttpwxcbrplryyyeunismrytoiruevcesznfiwweulrwsfiqucsteixyfskejjlzigtpiyfggyhfcgmnyewlrxctxuufhgoixwrrfciuovwkwwfleivliszvrnlttlgiuzyalvxgehfpvhgfxqufxwaizlqiulznyqixlryfhmuphjjysalmyoagqxtqykikyjtlzevtuzyhrggmsagekyiiycitdsshrwuphjjyeelmjhghwyttmgicwezneitpkflqepeezjnwulkjfrwgnvfhfkglrymzytlycmvxwpwfosspohjfnwcwpjcyccgennomgyysypmpbyfhgekyiiiehkyeyyhvunmskrgtlrxarepewjnfmvfijhgvgwixypvcywlynrvdiyfrwqchnhnxgfvxoaiolgmcaittingcvgdwniarcyxj"
#print(kasiski(m1,3))
for key in kasiski(m_, 3):
    print(key)
    print(decypher_vigenere(m_, key))

print("----------------------------------")
#for key in kasiski(m1, 3):
#    print(key)
#    print(decypher_vigenere(m1, key))
#print(decypher_vigenere(m, "exact"))
