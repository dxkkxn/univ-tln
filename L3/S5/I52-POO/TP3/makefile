main: main.o poly.o vec-complex.o
	g++ -Wall $^ -lComplex -L../TP2 -o main

main.o: main.cc poly.h vec-complex.h complex.h
	g++ -Wall -c main.cc 

poly.o: poly.cc poly.h
	g++ -Wall -c poly.cc

vec-complex.o: vec-complex.h vec-complex.cc complex.h
	g++ -Wall -c vec-complex.cc 


