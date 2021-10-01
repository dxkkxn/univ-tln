#include "complex.h"
#include <iostream>

using namespace std;

int main() {
    Complex x(1,2);
    Complex y(3,4);
    Complex z(y);
    cout<<" x = ";
    x.print();
    (x.sum1(y));
    cout<<" x = ";
    x.print();
    (x.sum2(y)).print();
    cout<<" x = ";
    x.print();
    ( (x.sum2(y)).sum2(z) ).print();
    cout<<" x = ";
    x.print();
    ( (x.sum3(y)).sum3(z) ).print();
    cout<<" x = ";
    x.print();
    ( (x.sum4(y)).sum4(z) ).print();
    cout<<" x = ";
    x.print();
    return 0;
}
