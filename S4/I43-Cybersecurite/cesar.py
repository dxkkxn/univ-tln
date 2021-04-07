alphabet = []
for _ in range(26):
    alphabet.append(chr(97+_));


def decypher(m, k):
    msg_decyphered = ""
    for i in range(len(m)):
        num_lettre = alphabet.index(m[i]);
        msg_decyphered += alphabet[(num_lettre - k) % 26]
    return msg_decyphered

print(decypher("mrmydmk", alphabet.index('m') - alphabet.index('e')))
print(decypher("bgbnsb",alphabet.index('b') - alphabet.index('e')))
print(decypher("tytfkt", alphabet.index('t') - alphabet.index('e')))
print(decypher("glnsxz", 5))
print(decypher("mrtydf", 5))
