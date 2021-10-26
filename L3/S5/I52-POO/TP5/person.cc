#include <iostream>
#include <string>
#include "person.h"
using std::string;
using std::cout;
using std::endl;

void Person::print() {
    cout << name << " " << surname << " is "<< age << " years old ";
}

Person::Person(){
    name = "Undefined";
    surname = "UNDEFINED";
    age = 0;
}

Person::Person(string _surname, string _name, unsigned _age){
    name = _name;
    surname = _surname;
    age = _age;
}

Person::Person(const Person& p){
    name = p.name;
    surname = p.surname;
    age = p.age;
}
