#include "poly.h"
#include <iostream>

using namespace std;

Poly::Poly() {
    deg = -1;
    coef_arr = NULL;
}
Poly::Poly(unsigned deg_aux, float *arr_aux) {
    cout<<"Call to constructor by param for"<<this<<endl;
    deg = deg_aux;
    coef_arr = new float[deg+1];
    for(int i = 0; i <= deg; i++)
        coef_arr[i] = arr_aux[i];
}

Poly::Poly(const Poly &P){
    cout<<"Call to constructor by copy for"<<this<<endl;
    deg = P.deg;
    coef_arr = new float [deg+1];
    for(int i = 0; i<= deg; i++)
        coef_arr[i] = P.coef_arr[i];
}

Poly::~Poly(){
    cout<<"Call to destructor for"<<this<<endl;
    delete [] coef_arr;
}

Poly & Poly::operator=(const Poly& P) {
    if(this != &P) {
        delete [] coef_arr;
        deg = P.deg;
        coef_arr = new float[deg+1];
        for(int i = 0; i <= deg; i++)
            coef_arr[i] = P.coef_arr[i];
    }
    return (*this);
}

void Poly::print() {
    cout<<coef_arr[0]<<" " ;
    for(int i = 1; i<=deg; i++) {
        cout<<coef_arr[i]<<"x^"<<i<<" ";
    }
}
