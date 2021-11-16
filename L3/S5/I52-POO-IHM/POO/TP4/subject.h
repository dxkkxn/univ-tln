#ifndef SUBJECT_H
#define SUBJECT_H
#include <iostream>
using std::string;
class Subject {
    private:
        string name;
        float coef;
    public:
        Subject();
        Subject(string, float);
        void print();
        string get_name();
        float get_coef();
};
#endif
