###############################################
# Codegen.py
# ----------
#
# Compilateur arithmetique fonctionelle
#
# BENJELLOUN Youssef et LEAL Andre
# I53 - Compilation et theorie des langages
# 10/10/2021
###############################################

import Scanner, Parser, Codegen, sys, os
def main():
    # Verification de l'existance d'un argument
    if len(sys.argv) < 2:
        print("Fichier ou expression arithmétique non trouvé")
        return -1
    # Si l'argument n'est pas un fichier, le premier argument
    # est considere comme une expression arithmetique

    if (os.path.isfile(sys.argv[1])):
        f = open(sys.argv[1],"r")
        str_s = f.read()
    else:
        str_s = sys.argv[1]

    l = Scanner.scanner(str_s)

    if l:
        postfix = Parser.parser(l)
    else:
        return -1

    if postfix:
        Codegen.codegen(postfix)
        os.system("chmod u+x a.out")

    #Le code suivant permet de tester le compilo plus rapidement
    """
    try:
        str_s = str_s.replace("NON", "not")
        str_s = str_s.replace("OU", "or")
        str_s = str_s.replace("ET", "and")
        str_s = str_s.replace("VRAI", "True")
        str_s = str_s.replace("FAUX", "False")
        expected = eval(str_s)
        print(f"expected = {expected}")
        print(f"got = ", end="", flush=True)
        os.system("./a.out")
    except:
        pass
    """
    return 1
if __name__ == '__main__':
    main()
