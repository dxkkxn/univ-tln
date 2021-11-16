#ifndef VEC_COMPLEX_H
#define VEC_COMPLEX_H
#include <fstream>
#include "complex.h"

using namespace std;

class VecComplex{
    private:
        unsigned short size;
        Complex* vec;
    public:
        VecComplex(const  Complex*, unsigned short);
        VecComplex(ifstream&);
        ~VecComplex();
        void print_vec();
};
#endif
