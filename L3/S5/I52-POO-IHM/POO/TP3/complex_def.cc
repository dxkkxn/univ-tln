#include "complex_def.h"
#include <iostream>
#include <cmath>

using std::cout; using std::endl; using std::cerr;
using std::ostream;
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

ostream& operator<<(ostream &o, const ComplexDef& c) {
    o<<c.re<<"+"<<c.im<<"i";
    return o;
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
ComplexDef ComplexDef::operator*(const ComplexDef& C) {
    ComplexDef res;
    res.re = (re*C.re) - (im*C.im);
    res.im = (re*C.im) + (im*C.re);
    return res;
}

ComplexDef ComplexDef::operator*(float c) {
    ComplexDef res;
    res.re = re * c;
    res.im = im *c;
    return res;
}

ComplexDef operator*(float n, const ComplexDef& c) {
    ComplexDef res;
    res.re = c.re*n;
    res.im = c.im*n;
    return res;
}

bool ComplexDef::operator==(const ComplexDef& C) {
    return(re == C.re && im == C.im);
}

ComplexDef ComplexDef::module(const ComplexDef& c) {
    re = sqrt(pow(c.re,2)+pow(c.im,2));
    im = 0;
    return *this;
}

ComplexDef ComplexDef::conjugate(const ComplexDef& a){
    re = a.re;
    im = a.im * -1;
    return *this;
}

ComplexDef ComplexDef::inverse() {
    ComplexDef res, tmp, tmp2;
    res = tmp.conjugate(*this) * (1/pow(tmp2.module(*this).re,2));
    cout << (1/pow(tmp2.module(*this).re,2))<<endl;
    return res;
}
ComplexDef ComplexDef::operator/(const ComplexDef&c) {
    ComplexDef res, tmp(c);
    tmp = tmp.inverse();
    cout<<"tmp = "<<tmp<<endl;
    cout<<"*this = "<<*this<<endl;
    res = (*this) * tmp;
    cout<<"res = "<<res<<endl;
    return res;
}

