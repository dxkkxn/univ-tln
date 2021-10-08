#ifndef POLY_H
#define POLY_H
class Poly{
    private:
        int deg;
        float* coef_arr;
    public:
        Poly();
        Poly(unsigned, float*);
        Poly(const Poly &);
        ~Poly();
        Poly & operator=(const Poly &);
        void print();
};
#endif
