#include "complex_def.h"
#include <iostream>
#include <cmath>

using std::cout; using std::endl; using std::cerr;
ComplexDef::ComplexDef(){
    re = 0; im = 0;
    cout<<"call to constructor by default "<<this<<" number"<<endl;

}
ComplexDef::ComplexDef(float a, float b){
    re = a; im = b;
    cout<<"call to constructor by param "<<this<<" number"<<endl;
}
ComplexDef::ComplexDef(const ComplexDef& cm){
    re = cm.re; im = cm.im;
    cout<<"call to constructor by copy "<<this<<" number"<<endl;
}
ComplexDef::~ComplexDef() {
    cerr<<"Destroyed "<<this<<" number"<<endl;
}

friend ostream & ComplexDef::operator<<(ostream&, const ComplexDef& c) {
    cout<<c.re<<"+"<<c.im<<"i";
}

ComplexDef& ComplexDef::operator=(const ComplexDef& C) {
    re = C.re;
    im = C.im;
    return *this;
}

ComplexDef& ComplexDef::operator+(const ComplexDef& C) {
    re += C.re;
    im += C.im;
    return *this;
}
ComplexDef& ComplexDef::operator*(const ComplexDef& C) {
    re = (re*C.re) - (im*C.im);
    im = (re*C.im) - (im*C.re);
    return *this;
}

bool ComplexDef::operator==(const ComplexDef& C) {
    return(re == C.re && im == C.im);
}

ComplexDef& ComplexDef::operator%(const ComplexDef& c) {
    re = sqrt(pow(c.re,2)+pow(c.im,2));
    im = 0;
    return *this;
}
