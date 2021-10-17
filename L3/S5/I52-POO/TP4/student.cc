#include <iostream>
#include <vector>
#include "person.h"
#include "student.h"

using std::cout;
using std::endl;
using std::vector;

Student::Student(string sn, string n, unsigned a, unsigned nb_m):
    Person(sn, n, a) {
        nb_marks = nb_m;
        marks.assign(nb_m, 0);
    }

Student::Student(const Student & s):Person(s) {
    nb_marks = s.nb_marks;
    marks = s.marks;
}
Student::~Student(){
    marks.clear();
}
void Student::add_marks(float *arr, unsigned size){
    for(unsigned i = 0; i<size; i++)
        marks[i] = arr[i];
}
void Student::print() {
   cout << get_surname() << " " << get_name() << " his/her marks are [";
   for(unsigned i = 0; i < (marks.size()-1); i++) 
       cout << marks[i] << ",";
   cout << marks.back() << "]" << endl;
}

float Student::average() {
    float sum = 0;
    for(unsigned i = 0; i < marks.size(); i++) 
        sum += marks[i];
    return (sum/marks.size());
}


Student & Student::operator=(const Student & s) {
    if (this != &s) {
        marks.clear();
        nb_marks = s.nb_marks;
        marks = s.marks;
    }
    marks[0] = 9;
    return (*this);
}
        


