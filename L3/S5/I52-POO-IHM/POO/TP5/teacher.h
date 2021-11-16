#ifndef TEACHER_H
#define TEACHER_H
#include "person.h"
#include "subject.h"

using std::string;

class Teacher: public Person{
    private:
        Subject * teaching_sl;
        unsigned size_tsl;
    public:
        Teacher();
        Teacher(string sn, string n, unsigned age, Subject *sl, unsigned size);
        Teacher(const Teacher &);
        ~Teacher();
        Teacher & operator=(const Teacher &);
        void print();
};

#endif
