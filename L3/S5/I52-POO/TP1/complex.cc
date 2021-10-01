#include "complex.h"
#include <iostream>
#include <cmath>

using namespace std;

void print_complex_num(const complex_num& a){
    cout<<a.re<<"+"<<a.im<<"i"<<endl;
}
complex_num sum(const complex_num& a, const complex_num& b){
    complex_num res;
    res.re = a.re+ b.re;
    res.im = a.im+ a.im;
    return res;
}
complex_num product(const complex_num& a, const complex_num& b){
    complex_num res;
    res.re = (a.re*b.re) - (a.im*b.im);
    res.im = a.re*b.im + a.im*b.re;
    return res;
}

float module(const complex_num& a){ 
    return sqrt(pow(a.re,2)+pow(a.im,2));
}

// z = a + ib --> z = a - ib
complex_num conjugate(const complex_num& a){
    complex_num res = a;
    res.im *=-1;
    return res;
}

void init(complex_num& a){
    static int i = 0;
    a.ident = i, a.re = 0, a.im = 0;
    i++;
}

complex_num bidon(complex_num& formel) {
    cout<<"adresse formel = "<<&formel<<endl;
    cout<<"adresse formel.ident ="<< &formel.ident<<endl;
    cout<<"adresse formel.re ="<< &formel.re<<endl;
    cout<<"adresse formel.im ="<< &formel.im<<endl;
    complex_num res;
    init(res);
    cout<<"adresse res= "<<&res<<endl;
    cout<<"adresse res.ident ="<< &res.ident<<endl;
    cout<<"adresse res.re ="<< &res.re<<endl;
    cout<<"adresse res.im ="<< &res.im<<endl;
    return res;
}

void create_complex_num(complex_num** ppc) {
    *ppc = new complex_num;
    init(**ppc);
}

void create_complex_num_2(pt_complexe_num& a) {
    a = new complex_num;
    init(*a);
}

complex_num* create_complex_num(){
    complex_num* new_complex = new complex_num;
    init(*new_complex);
    return new_complex;
}

complex_num* create_vect_complex (unsigned int n){
    complex_num *tab_complex = new complex_num[n];
    return tab_complex;
}



    



