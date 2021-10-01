CFLAGS=-Wall 
main: main.o complex.o 
	g++ $(CFLAGS) $^ -o main

main.o : main.cc libComplex.a
	g++ $(CFLAGS) -c main.cc -lComplex

libComplex.a: complex.o
	ar cr libComplex.a complex.o
	ranlib libComplex.a

complex.o : complex.cc complex.h
	g++ $(CFLAGS) -c complex.cc	
	
