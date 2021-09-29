def scanner(s):
    list_ul = []
    OP = {'+', '-', '*', '/'}
    i = 0
    while i < len(s):
        if s[i].isdigit():
            nb = 0
            while i < len(s) and s[i].isdigit():
                nb *= 10
                nb += int(s[i])
                i += 1
            i -= 1 #decrease i to keep it in the good index after later increase
            list_ul.append(('NB', nb))

        elif s[i] in OP:
            list_ul.append(('OP', s[i]))
        elif s[i] == '(':
            list_ul.append(('PO', s[i]))
        elif s[i] == ')':
            list_ul.append(('PF', s[i]))
        elif s[i] == ' ' or s[i] == '\n' :
            pass
        else:
            print(f"Error near character {s[i]} i = {i}")
            return None
        i += 1
    return list_ul
