OBJ=inout.o graph.o connexe.o stack.o eulerian.o list.o binary.o
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

eulerian.o: eulerian.c eulerian.h
	gcc $(CFLAGS) -c eulerian.c

list.o: list.c list.h
	gcc $(CFLAGS) -c list.c

binary.o: binary.c binary.h
	gcc $(CFLAGS) -c binary.c

disjoint.o: disjoint.c disjoin.h
	gcc $(CFLAGS) -c disjoint.c
