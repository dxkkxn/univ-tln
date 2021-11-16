main.exe: main.o person.o teacher.o student.o subject.o cursus.o
	g++ -Wall -g $^ -o main.exe
main.o: main.cc person.h
	g++ -Wall -g -c main.cc
person.o: person.cc person.h
	g++ -Wall -g -c person.cc
teacher.o: teacher.cc teacher.h
	g++ -Wall -g -c teacher.cc
student.o: student.cc student.h
	g++ -Wall -g -c student.cc
subject.o: subject.cc subject.h
	g++ -Wall -g -c subject.cc
cursus.o: cursus.cc cursus.h
	g++ -Wall -g -c cursus.cc
