#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include "person.h"

class Student: public Person {
    protected:
        unsigned nb_marks;
        float * marks;
    public:
        Student();
        Student(string sn, string n, unsigned a, unsigned nb_m);
        Student(const Student &);
        ~Student();
        void write_marks(float *arr, unsigned size);
        void print();
        void print_marks();
        float average();
        Student & operator=(const Student &);
};

#endif
