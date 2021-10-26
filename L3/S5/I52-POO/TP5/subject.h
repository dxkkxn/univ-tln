#ifndef SUBJECT_H
#define SUBJECT_H
#include <iostream>
using std::string;
class Subject {
    private:
        string name;
    public:
        Subject();
        Subject(string);
        string get_name();
};
#endif
