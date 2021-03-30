alphabet = []
for i in range(26):
    alphabet.append(chr(97+i));


def decypher(msg, key):
    msg_decyphered = ""
    for i in range(len(msg)):
        key_int = alphabet.index(key[i % len(key)])
        char_int = alphabet.index(msg[i])
        msg_decyphered += alphabet[(char_int - key_int) % 26]
    return msg_decyphered
print(decypher("ykscetktgipiwvkopriosxurmcjezwqe", "exofacile"))


