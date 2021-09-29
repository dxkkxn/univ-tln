i = 0
postfixed_l = []
l = []
def parser(unilex) :
    global i
    global l
    l = unilex
    if expr() and i == len(l):
        print("Chaine valide")
        return postfixed_l
    else:
        if i >= len(l):
            print(f"Chaine invalide near character {l[-1][1]} index out")
        else:
            print(f"Chaine invalide near character {l[i][1]}")

def expr():
    global i
    if terme() and reste_e():
        return True
    return False


def reste_e():
    global i

    if i < len(l) and (l[i][1] == '+' or l[i][1] == '-'):
        op = l[i][1]
        i += 1
        if terme():
            postfixed_l.append(op)
            if reste_e():
                return 1
            else:
                return False
        else:
            return False
    return 1

def terme() :
    global i
    if fact() and reste_t():
        return True
    return False

def reste_t():
    global i
    if i < len(l) and (l[i][1] == '*' or l[i][1] == '/'):
        op = l[i][1]
        i += 1
        if fact():
            postfixed_l.append(op)
            if reste_t():
                return True
            else:
                return False
        else:
            return False
    return True

def fact():
    global i

    if i < len(l) and l[i][0] == 'NB':
        postfixed_l.append(l[i][1])
        i += 1
        return 1

    elif i < len(l) and l[i][1] == '(':
        i += 1
        if expr() :
            if i < len(l) and l[i][1] == ')':
                i += 1
                return True;
    else:
        if i >= len(l):
            print(f"Chaine invalide near character {l[-1][1]} index out")
        else:
            print(f"Chaine invalide near character {l[i][1]}")
        return False
