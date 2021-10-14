#ifndef COMPLEX_H
#define COMPLEX_H
class Complex{
    private:
        float re, im;
        static int ident;
    public:
        Complex();
        Complex(float, float);
        Complex(const Complex&);
        ~Complex();
        void print();
        void product(Complex& a);
        float module(Complex& a);
        void conjugate(Complex& a);
        float get_re();
        float get_im();
        bool is(const Complex&);
        void sum1(Complex& a);
        Complex sum2(const Complex &z);
        Complex sum3(const Complex &z);
        Complex& sum4(const Complex &z);
};
#endif
