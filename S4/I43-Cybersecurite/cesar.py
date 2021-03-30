alphabet = []
for _ in range(26):
    alphabet.append(chr(97+_));

msg = "hjhnjxyzsywjxgjfzyjcyj"

def decypher(m, k):
    msg_decyphered = ""
    for i in range(len(m)):
        num_lettre = alphabet.index(m[i]);
        msg_decyphered += alphabet[(num_lettre - k) % 26]
    return msg_decyphered
print(decypher(msg, 5))
