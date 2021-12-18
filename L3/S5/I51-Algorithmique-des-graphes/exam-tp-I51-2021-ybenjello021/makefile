CFLAGS=-Wall -g 
OBJ=connexe.o detection.o disjoint.o graph.o list.o  

connexe.o : connexe.c graph.h list.h connexe.h
	gcc $(CFLAGS) -c connexe.c

detection.o : detection.c disjoint.h graph.h 
	gcc $(CFLAGS) -c detection.c

list.o : list.c list.h

graph.o: graph.c graph.h
	gcc $(CFLAGS) -c detection.c
