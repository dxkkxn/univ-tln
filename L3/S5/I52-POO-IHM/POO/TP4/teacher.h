#ifndef TEACHER_H
#define TEACHER_H
#include "person.h"

using std::string;

class Teacher: public Person{
    private:
        string statut;
        unsigned hours;
    public:
        Teacher();
        Teacher(string surname, string name, unsigned age, string statut);
        Teacher(const Teacher&);
        void print();
        void work(unsigned);
};
#endif
