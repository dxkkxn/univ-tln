import scanner, parser, codegen, sys, os

f = open("in.txt","r")
str_s = f.read()
l = scanner.scanner(str_s)
postfix = parser.parser(l)
codegen.codegen(postfix)
os.system("chmod u+x a.out")

