CFLAGS=-Wall -g 
connexe.o : connexe.c graph.h list.h connexe.h
	gcc $(CFLAGS) -c connexe.c -I$(GRAPH)

list.o : list.c list.h
	gcc $(CFLAGS) -c list.c -I$(GRAPH)

graph.o: graph.c graph.h
	gcc $(CFLAGS) -c graph.c
