#ifndef STUDENT2_H
#define STUDENT2_H
#include "student.h"
#include "subject.h"
class Student2: public Student {
    private:
        Subject * subjects_followed;
    public:
        Student2(string sn, string n, unsigned age, unsigned nb_m, Subject * sf);
        Student2();
        ~Student2();
        void print();
        float average();
};
#endif
