#include <iostream>

using std::string;
using std::cout;
using std::endl;

class Person {
    private:
        string name;
        string surname;
        unsigned int age;
};


class Student: public Person {
    private:
        Course course;
};

class Teacher: public Person{
    private:
        Subject * teaching_sl;
};

class Cursus {
    string title;
    Teacher responsable;
    Subject * subject_l;

};
    
class Subject {
    private:
        string name;
};

