#ifndef PERSON_H
#define PERSON_H
#include <iostream>

using std::string;
class Person {
    private:
        string name;
        string surname;
        unsigned int age;
    public:
        Person();
        Person(string surname, string name, unsigned age);
        Person(const Person & );
        void print();
};
#endif
