import Scanner, Parser, Codegen, sys, os

if (os.path.isfile(sys.argv[1])):
    f = open(sys.argv[1],"r")
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
