#include "complex.h"
#include <iostream>
#include <cmath>

using namespace std;
int Complex::ident = 0;
Complex::Complex(){
    re = 0; im = 0;
    cout<<"call to constructor by default "<<this<<" number"<<ident<<endl;
    ident++;

}
Complex::Complex(float a, float b){
    re = a; im = b;
    cout<<"call to constructor by param "<<this<<" number"<<ident<<endl;
    ident++;
}
Complex::Complex(const Complex& cm){
    re = cm.re; im = cm.im;
    cout<<"call to constructor by copy "<<this<<" number"<<ident<<endl;
    ident++;
}
Complex::~Complex() {
    cerr<<"Destroyed "<<this<<" number"<<ident<<endl;
    ident--;
}
void Complex::print() {
    cout<<re<<"+"<<im<<"i"<<endl;
}
void Complex::sum1(Complex& a){
    re += a.re; im += a.im;
}
Complex Complex::sum2(const Complex &z) {
    return Complex(re+z.re, im+z.im);
}
Complex Complex::sum3(const Complex &z) {
    re = re + z.re; im = im + z.im;
    return *this;
}
Complex& Complex::sum4(const Complex &z) {
    re = re + z.re; im = im + z.im;
    return *this;
}

void Complex::product(Complex& a){
    re = (re*a.re) - (im*a.im);
    im = (re*a.im) - (im*a.re);
}
float Complex::module(Complex& a){
    return sqrt(pow(a.re,2)+pow(a.im,2));
}
void Complex::conjugate(Complex& a){
    im *= -1;
}

float Complex::get_re(){
    return re;
}
float Complex::get_im(){
    return im;
}
bool Complex::is(const Complex& a){
    return (re==a.re && im==a.im);
}
