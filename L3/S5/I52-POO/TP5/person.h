#ifndef PERSON_H
#define PERSON_H
#include <iostream>

using std::string;
class Person {
    private:
        std::string name;
        std::string surname;
        unsigned int age;
    public:
        Person();
        Person(string surname, string name, unsigned age);
        Person(const Person & );
        void print();
        void grow(); 
        string get_name();
        string get_surname();
};
#endif
