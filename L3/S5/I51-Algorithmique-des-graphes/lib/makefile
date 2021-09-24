OBJ=inout.o graph.o 
CFLAGS=-Wall -g
libgraph.a: $(OBJ)
	ar -cr libgraph.a $^
graphe.o: graph.c graph.h inout.h
	gcc $(CFLAGS) -c graph.c
inout.o: inout.c inout.h
	gcc $(CFLAGS) -c inout.c

