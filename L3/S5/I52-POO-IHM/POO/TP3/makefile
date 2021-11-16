main.exe: main.o poly.o vec-complex.o complex_def.o
	g++ -Wall $^ -I../TP2 -L../TP2 -lComplex -o main

main.o: main.cc poly.h vec-complex.h 
	g++ -Wall -c main.cc -lComplex -I../TP2 -L../TP2 

poly.o: poly.cc poly.h
	g++ -Wall -c poly.cc

vec-complex.o: vec-complex.h vec-complex.cc 
	g++ -Wall -c vec-complex.cc -lComplex -I../TP2 -L../TP2 
complex_def.o: complex_def.cc complex_def.h
	g++ -Wall -c complex_def.cc


