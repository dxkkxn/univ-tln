CFLAGS = -Wall
main: main.o swap.o complex.o 
	g++ $(CFLAGS) $^ -o main
main.o: main.cc swap.h 
	g++ $(CFLAGS) -c main.cc
swap.o: swap.cc swap.h complex.h
	g++ $(CFLAGS) -c swap.cc
complex.o: complex.cc complex.h
	g++ $(CFLAGS) -c complex.cc

