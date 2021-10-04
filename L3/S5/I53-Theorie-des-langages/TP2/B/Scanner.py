"""
Convertit la chaine de caracteres <s> en une liste d'unités
léxicales de la forme (<type>, <valeur>). Retourne None en cas
d'erreur et affiche le caractere fautif
"""
def scanner(s):
    list_ul = []
    i = 0
    while i < len(s):
        if i <= len(s)-4 and s[i:i+4] == "VRAI":
            list_ul.append(("BOOL", True))
            i += 4

        elif i <= len(s)-4 and s[i:i+4] == "FAUX":
            list_ul.append(("BOOL", False))
            i += 4

        elif i <= len(s)-2 and s[i:i+2] == "OU":
            list_ul.append(("OP", "OU"))
            i += 2

        elif i <= len(s)-2 and s[i:i+2] == "ET":
            list_ul.append(("OP", "ET"))
            i += 2

        elif i <= len(s)-3 and s[i:i+3] == "NON":
            list_ul.append(("OP", "NON"))
            i += 3

        elif s[i] == '(':
            list_ul.append(("PO",'('))
            i += 1

        elif s[i] == ')':
            list_ul.append(("PF",')'))
            i += 1

        elif s[i] == ' ' or s[i] == '\n':
            i += 1

        else:
            print(f"Lexical error near char {s[i]}")
            return None

    return list_ul

