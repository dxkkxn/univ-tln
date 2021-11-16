#include "vec-complex.h"
#include "complex.h"
#include <iostream>

using namespace std;

VecComplex::VecComplex(const Complex* vec_p, unsigned short size_p){
    size = size_p;
    vec = new Complex [size];
    for(int i = 0; i < size; i++)
         vec[i] = vec_p[i];
}

VecComplex::VecComplex(ifstream& in){
  in>>size;
  vec = new Complex [size];
  float a, b;
  for(int i = 0; i < size; i++){
    in>>a;
    in>>b;
    vec[i]=Complex(a,b);
  }
}
VecComplex::~VecComplex(){
    cout<<"Destruction vec complex ";
    delete[] vec;
}

void VecComplex::print_vec() {
    for(int i = 0; i<size; i++)
        vec[i].print();
}
