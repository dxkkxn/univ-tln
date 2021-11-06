#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include "person.h"
#include "cursus.h"
#include "teacher.h"

class Student: public Person {
    private:
        Cursus cur;
    public:
        Student();
        Student(string sn, string n, unsigned age, Cursus c);
        void print();
};

#endif
