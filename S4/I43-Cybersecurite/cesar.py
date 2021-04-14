alphabet = []
for _ in range(26):
    alphabet.append(chr(97+_));

def cypher_cesar(m, k):
    k = alphabet.index(k)
    msg = ""
    for letter in m:
        num_letter = alphabet.index(letter);
        msg += alphabet[(num_letter + k) % 26]
    return msg


def decypher_cesar(m, k):
    k = alphabet.index(k)
    msg_decyphered = ""
    for letter in m:
        num_letter = alphabet.index(letter);
        msg_decyphered += alphabet[(num_letter - k) % 26]
    return msg_decyphered

def frequent_letter(m):
    dico = {}
    for letter in m:
        if dico.get(letter):
            dico[letter] += 1
        else:
            dico[letter] = 1

    max_l = m[0]
    max_f = dico[m[0]]
    list_letters = []

    for letter, frequency in dico.items():
        if frequency > max_f:
            max_f = frequency
            max_l = letter
    list_letters.append(max_l)

    for letter, frequency in dico.items():
        if frequency == max_f and letter not in list_letters:
            list_letters.append(letter)

    return list_letters



"""
m = "olgtoylaldqlterclyonszdptwlufdepncppfypxmcjzyopaczrclxxpxltdnpaczrclxxpdpdeopgpwzaapwftxpxpnzxxpwzcotylepfcopolgtoypeltealddfqqtdlyetwlfetwtdpwpcpdplfazfcdtydelwwpcdfcwpdlfecpdzcotylepfcdtwlrclyotlwzcdopxlytpcppiazypyetpwwppewpgztwlacpwfopnzyypneplezfdwpdzcotylepfcdpenlalmwpopwpfcozyypcwpdzcocpdbftwgpfe"
print(m)
list_letter = frequent_letter(m)
print(list_letter)
for letter in list_letter:
    possible_key = alphabet[(alphabet.index(letter) - alphabet.index('e')) % 26]
    print(decypher(m,possible_key))

print(alphabet, '\n', m,'\n',cypher(m,'h'), '\n', decypher(cypher(m, 'h'), 'h'), '\n')
"""
