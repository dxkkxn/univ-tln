CFLAGS=-Wall
main: main.o libComplex.a
	g++ $(CFLAGS) main.o -o main -lComplex -L.

main.o : main.cc complex.h
	g++ $(CFLAGS) -c main.cc

libComplex.a: complex.o
	ar cr libComplex.a complex.o
	ranlib libComplex.a

complex.o : complex.cc complex.h
	g++ $(CFLAGS) -c complex.cc
