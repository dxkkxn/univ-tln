#include <string>
#include "teacher.h"

using std::cout;
using std::endl;

Teacher::Teacher():Person(){
    statut = "unemployed";
    hours = 0;
}
Teacher::Teacher(string _surname, string _name, 
                 unsigned age, string _statut):Person(_surname, _name, age){
    statut = _statut;
    hours = 0;
}

void Teacher::print(){
    (*this).Person::print();
    cout << " is " << statut << " and has worked " << hours << " hours"<<endl; 
}
void Teacher::work(unsigned h) {
    hours += h;
}
