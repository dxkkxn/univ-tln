#ifndef COMPLEX_H
#define COMPLEX_H
typedef struct {
    float re,im;
    unsigned int ident;
} complex_num;

void print_complex_num(const complex_num&);

complex_num sum(const complex_num&, const complex_num&);
complex_num product(const complex_num&, const complex_num&);
float module(const complex_num&);
complex_num conjugate(const complex_num&);

void init(complex_num&);

complex_num bidon(complex_num&);

#endif
