#ifndef COMPLEX_DEF_H
#define COMPLEX_DEF_H
class ComplexDef{
    private:
        float re, im;
    public:
        ComplexDef();
        ComplexDef(float, float);
        ComplexDef(const ComplexDef&);
        ~ComplexDef();
        void print(); 
        ComplexDef& operator=(const ComplexDef& C);
        ComplexDef& operator+(const ComplexDef& C);
        ComplexDef& operator*(const ComplexDef& C);
        bool operator==(const ComplexDef& C);
        ComplexDef& operator%(const ComplexDef& C) ;
        friend ostream & operator<<(ostream&, const ComplexDef& c);
};
#endif
