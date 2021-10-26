#include <iostream>
#include <vector>
#include "person.h"
#include "student.h"

using std::cout;
using std::endl;

Student::Student():Person(){
    cursus = Cursus();
}

Student::Student(string sn, string n, unsigned age, Cursus c):Person(sn, n, age) {
    cursus = c;
}

void Student::print(){
    (*this).Person::print();
    cout << " and follow the following cursus ";
    cursus.print();
}
