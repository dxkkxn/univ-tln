###############################################
# Codegen.py
# ----------
#
# Compilateur arithmétique fonctionnel
#
# BENJELLOUN Youssef et LEAL Andre
# I53 - Compilation et theorie des langages
# 10/10/2021
###############################################

import Scanner, Parser, Codegen, sys, os

def main():
    # Vérification de l'existance d'un argument
    if len(sys.argv) < 2:
        print("Fichier ou expression arithmétique non trouvé(e)")
        return -1
    # Si l'argument n'est pas un fichier, le premier argument
    # est considéré comme une expression arithmétique
    if (os.path.isfile(sys.argv[1])):
        f = open(sys.argv[1], "r")
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

    #Ce block permet de tester le compilo plus rapidement
    """
    try:
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
