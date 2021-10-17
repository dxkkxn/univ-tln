main.exe: main.o person.o teacher.o student.o
	g++ -Wall $^ -o main.exe
main.o: main.cc person.h
	g++ -Wall -c main.cc
person.o: person.cc person.h
	g++ -Wall -c person.cc
teacher.o: teacher.cc teacher.h
	g++ -Wall -c teacher.cc
student.o: student.cc student.h
	g++ -Wall -c student.cc
