HEADER = '\033[95m'
WARNING = '\033[93m'
FAIL = '\033[91m'
ENDC = '\033[0m'
BOLD = '\033[1m'
UNDERLINE = '\033[4m'


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
            list_ul.append(('NOMBRE', nb))

        elif s[i] in OP:
            list_ul.append(('OP', s[i]))
        elif s[i] == '(':
            list_ul.append(('PAR_OUV', s[i]))
        elif s[i] == ')':
            list_ul.append(('PAR_FER', s[i]))
        elif s[i] == ' ' or s[i] == '\n' :
            pass
        else:
            error(s,i)
            return None
        i += 1
    return list_ul

def error(s,i):
    print(f"{FAIL} SYNTAX ERROR {s[0]} {ENDC}")
    for j in range(len(s)):
        print(s[j], end ="", sep="")
        if j == i:
            print(f"{BOLD}{FAIL}{s[j]}{ENDC}", end="",sep="")
    print("\n")



