main.exe: main.o person.o
	g++ -Wall main.o person.o -o main.exe
main.o: main.cc person.h
	g++ -Wall -c main.cc
person.o: person.cc person.h
	g++ -Wall -c person.cc
