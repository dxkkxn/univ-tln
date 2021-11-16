#include <iostream>
#include <vector>
#include "person.h"
#include "student.h"

using std::cout;
using std::endl;


Student::Student() {
    nb_marks = 0;
    marks = NULL;
}

Student::Student(string sn, string n, unsigned a, unsigned nb_m):
    Person(sn, n, a) {
        nb_marks = nb_m;
        marks = new float[nb_m]();
    }

Student::Student(const Student & s):Person(s) {
    nb_marks = s.nb_marks;
    marks = new float[s.nb_marks];
    for(unsigned i = 0; i < nb_marks; i++)
        marks[i] = s.marks[i];
}
Student::~Student(){
    delete[] marks;
}
void Student::write_marks(float *arr, unsigned size){
    for(unsigned i = 0; i<size; i++)
        marks[i] = arr[i];
}
void Student::print() {
   cout << get_surname() << " " << get_name() << " his/her marks are [";
   for(unsigned i = 0; i < nb_marks; i++)
       cout << marks[i] << ",";
   cout << marks[nb_marks-1] << "]" << endl;
}

float Student::average() {
    float sum = 0;
    for(unsigned i = 0; i < nb_marks; i++)
        sum += marks[i];
    return (sum/nb_marks);
}

void Student::print_marks() {
  cout << "[";
  for(unsigned i = 0; i < nb_marks; i++)
      cout << marks[i] << ",";
  cout << marks[nb_marks-1] << "]" << endl;
}

Student & Student::operator=(const Student & s) {

    if (this != &s) {
        this->Person::operator=(s);
        delete [] marks;
        nb_marks = s.nb_marks;
        marks = new float[nb_marks];
        for(unsigned i = 0; i < nb_marks; i++)
            marks[i] = s.marks[i];
    }
    return (*this);
}
