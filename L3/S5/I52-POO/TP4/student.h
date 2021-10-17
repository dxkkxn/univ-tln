#ifndef STUDENT_H
#define STUDENT_H
#include <vector>
#include <iostream>
#include "person.h"

using std::vector;

class Student: public Person {
    private:
        unsigned nb_marks;
        vector<float> marks;
    public:
        Student(string sn, string n, unsigned a, unsigned nb_m);
        Student(const Student &);
        ~Student();
        void add_marks(float *arr, unsigned size);
        void print();
        float average();
        Student & operator=(const Student &);
};

#endif
