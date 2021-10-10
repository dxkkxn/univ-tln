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

# Si l'argument n'est pas un fichier, le premier argument
# est suppose' etre une expression arithmetique
if len(sys.argv) < 2:
    print("Fichier ou expression arithmetique non trouve'")
    exit(-1)

if (os.path.isfile(sys.argv[1])):
    f = open(sys.argv[1], "r")
    str_s = f.read()

else:
    str_s = sys.argv[1]

l = Scanner.scanner(str_s)

if l:
    postfix = Parser.parser(l)
else:
    exit(1)

if postfix:
    Codegen.codegen(postfix)
    os.system("chmod u+x a.out")

#Le code permet de tester le compilo plus rapidement
try:
    expected = eval(str_s)
    print(f"expected = {expected}")
    print(f"got = ", end="", flush=True)
    os.system("./a.out")
except:
    pass
