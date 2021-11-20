frlex: frequence.lex count_names.o
	flex frequence.lex
	gcc lex.yy.c count_names.o -lfl  -o frlex
count_names.o: count_names.c count_names.h
	gcc -Wall -g -c count_names.c
