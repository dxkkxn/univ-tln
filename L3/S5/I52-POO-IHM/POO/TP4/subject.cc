#include <iostream>
#include "subject.h"

using std::cout;
using std::endl;
Subject::Subject() {
    name = "Undefined";
    coef = 0;
}
Subject::Subject(string _name, float _coef) {
    name = _name;
    coef = _coef;
}
void Subject::print() {
    cout << name << " coef = " << coef << endl;
}
string Subject::get_name() {
    return name;
}
float Subject::get_coef() {
    return coef;
}

