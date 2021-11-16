#include <string>
#include "teacher.h"

using std::cout;
using std::endl;

Teacher::Teacher():Person(){
    teaching_sl = NULL;
    size_tsl = 0;
}

Teacher::Teacher(string sn, string name, unsigned age,
                 Subject* sl, unsigned size):Person(sn, name, age){
    teaching_sl = new Subject[size];
    size_tsl = size;
    for(unsigned i = 0; i < size; i++)
        teaching_sl[i] = sl[i];
}

Teacher::~Teacher() {
    delete [] teaching_sl;
}

Teacher::Teacher(const Teacher & t):Person(t) {
    size_tsl = t.size_tsl;
    teaching_sl = new Subject[t.size_tsl];
    for(unsigned int i = 0; i < size_tsl; i++)
        teaching_sl[i] = t.teaching_sl[i];
}

Teacher& Teacher::operator=(const Teacher & t) {
    if (this != &t) {
        this->Person::operator=(t);
        delete [] teaching_sl;
        size_tsl = t.size_tsl;
        teaching_sl = new Subject[size_tsl];
        for(unsigned int i = 0; i < size_tsl; i++)
            teaching_sl[i] = t.teaching_sl[i];
    }
    return *this;
}

void Teacher::print() {
    (*this).Person::print();
    cout << " and teach the following subjects ";
    for(unsigned i = 0; i < size_tsl; i++) {
        cout << teaching_sl[i].get_name() << " ";
    }
}
