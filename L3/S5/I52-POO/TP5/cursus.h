#ifndef CURSUS_H
#define CURSUS_H

#include <iostream>
#include "subject.h"
#include "teacher.h"

using std::string;

class Cursus {
    private:
        string title;
        Teacher responsable;
        Subject * subject_l;
        unsigned size_sl;
    public:
        Cursus();
        Cursus(string t, Teacher r, Subject *s_l, unsigned size_sb);
        Cursus(const Cursus &);
        ~Cursus();
        Cursus & operator=(const Cursus &);


};

#endif
