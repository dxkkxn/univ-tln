CC = gcc -Wall
# Yet another compiler of Compiler
YACC = bison -v

calc.exe: calc.o list_var.o
	$(CC) -o calc.exe calc.o list_var.o

calc.o: calc.c
	$(CC) -c calc.c

calc.c: calc.y 
	$(YACC) calc.y -o calc.c

list_var.o: list_var.c list_var.h 
	$(CC) -c list_var.c
