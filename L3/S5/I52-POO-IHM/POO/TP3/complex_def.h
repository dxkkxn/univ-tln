#ifndef COMPLEX_DEF_H
#define COMPLEX_DEF_H
#include <iostream>
class ComplexDef{
    private:
        float re, im;
    public:
        ComplexDef();
        ComplexDef(float, float);
        ComplexDef(const ComplexDef&);
        ~ComplexDef();
        void print(); 
        ComplexDef& operator=(const ComplexDef& C);
        ComplexDef& operator+(const ComplexDef& C);
        ComplexDef operator*(const ComplexDef& C);
        bool operator==(const ComplexDef& C);
        friend std::ostream& operator<<(std::ostream&, const ComplexDef&);
        ComplexDef operator*(float);
        friend ComplexDef operator*(float, const ComplexDef& );
        ComplexDef conjugate(const ComplexDef& a);
        ComplexDef inverse();
        ComplexDef operator/(const ComplexDef&);
        ComplexDef module(const ComplexDef&);

};
#endif
