#include "cursus.h"
#include "teacher.h"

using std::cout;
using std::endl;

Cursus::Cursus() {
    title = "?";
    responsable = Teacher();
    subject_l = NULL;
    size_sl = 0;

}

Cursus::Cursus(string t, Teacher r, Subject *sl, unsigned size_sb) {
    size_sl = size_sb;
    subject_l = new Subject[size_sb];
    for(unsigned int i = 0; i < size_sb; i++)
        subject_l[i] = sl[i];
    responsable = r;
    title = t;
}

Cursus::Cursus(const Cursus &c) {
    size_sl = c.size_sl;
    subject_l = new Subject[c.size_sl];
    for(unsigned int i = 0; i < size_sl; i++)
        subject_l[i] = c.subject_l[i];
    title = c.title;
    responsable = c.responsable;
}

Cursus::~Cursus(){
    delete[] subject_l;
}

Cursus & Cursus::operator=(const Cursus & c) {
    if (this != &c) {
        title = c.title;
        responsable = c.responsable;

        delete [] subject_l;
        size_sl = c.size_sl;
        cout << size_sl << "<<<<<\n";
        subject_l = new Subject[size_sl];
        for(unsigned int i = 0; i < size_sl; i++)
            subject_l[i] = c.subject_l[i];

    }
    return *this;
}

void Cursus::print() {
    cout << "-------" << title << "------" << endl;
    cout << "The responsable is ";
    responsable.print();
    cout << "The subjects are : " ;
    for(uint i = 0; i < size_sl; i++) {
        cout << subject_l[i].get_name() << " ";
    }
}

