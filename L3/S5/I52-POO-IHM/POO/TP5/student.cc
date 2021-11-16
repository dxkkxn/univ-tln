#include <iostream>
#include <vector>
#include "person.h"
#include "student.h"
#include "cursus.h"

using std::cout;
using std::endl;

Student::Student():Person(){
    cur= Cursus();
}

Student::Student(string sn, string n, unsigned age, Cursus c):Person(sn, n, age) {
    cur = c;
}

void Student::print(){
    cout << "ooook" << endl;
    (*this).Person::print();
    cout << "ooook" << endl;
    cout << " and follow the following cursus ";
    cur.print();
}
