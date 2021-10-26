#include <iostream>
#include "subject.h"

using std::cout;
using std::endl;
Subject::Subject() {
    name = "Undefined";
}
Subject::Subject(string _name) {
    name = _name;
}
string Subject::get_name() {
    return name;
}
