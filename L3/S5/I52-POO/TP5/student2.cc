#include <iostream>
#include "student2.h"
#include "subject.h"
using std::cout;
using std::endl;
Student2::Student2(string sn, string n, unsigned age, unsigned nb_m,
        Subject * sf):Student(sn,n,age,nb_m) {
        subjects_followed = new Subject[nb_m];
        for(unsigned i = 0; i < nb_m; i++) {
          subjects_followed[i] = sf[i];
        }
};

Student2::Student2():Student(){
    subjects_followed = NULL;
}
Student2::~Student2(){
    delete [] subjects_followed;
}

void Student2::print() {
    cout << this->Person::get_surname() << " " << this->Person::get_name() << endl;
    for(unsigned i = 0; i < this->Student::nb_marks; i++)
        cout << subjects_followed[i].get_name() << " " << this->Student::marks[i] << endl;
}
float Student2::average() {
    float moy = 0;
    for(unsigned i = 0; i < this->Student::nb_marks; i++)
        moy += (this->Student::marks[i]) * subjects_followed[i].get_coef();
    return moy;
}
