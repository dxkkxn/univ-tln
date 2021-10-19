OBJ=inout.o graph.o connexe.o stack.o eulerien.o
CFLAGS=-Wall -g
libgraph.a: $(OBJ)
	ar -cr libgraph.a $^

connexe.o: connexe.c connexe.h graph.h
	gcc $(CFLAGS) -c connexe.c

graphe.o: graph.c graph.h inout.h
	gcc $(CFLAGS) -c graph.c
	
inout.o: inout.c inout.h
	gcc $(CFLAGS) -c inout.c

stack.o: stack.c stack.h
	gcc $(CFLAGS) -c stack.c

eulerien.o: eulerien.c eulerien.h
	gcc $(CFLAGS) -c eulerien.c
