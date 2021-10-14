#include <iostream>
#include "complex.h"
#include "vec-complex.h"
#include "poly.h"
#include "complex_def.h"

using namespace std;
/*
Complex global;
void f() {
    cout<<"var_f ";
    Complex var_f;
    cout << "static_f";
    static Complex static_f;
}

Complex g() {
    cout<<"return_val ";
    Complex return_val;
    return return_val;
}
Complex & h() {
    cout<<"return_val_ref ";
    Complex return_val_ref(5,10);
    return return_val_ref;
}
*/

int main() {
  /*
    cout<<"loc_main ";
    Complex loc_main;
    f();g();
    Complex res = h();
    res.print();
    cout<<"Program end"<<endl;
    ifstream file("data.txt");
    VecComplex vc(file);
    vc.print_vec();
    float arr[6] = {0.1,0.2,0.3,0.4,0.5,1};
    Poly try_poly(5,arr);
    Poly def_poly;
    Poly cpy_poly(try_poly);
    try_poly.print();
    def_poly.print();
    cout<<"def_poly <- try_poly"<<endl;
    def_poly = try_poly;
    def_poly.print();
    try_poly.print();
    cpy_poly.print();
  */
    ComplexDef test(5,1);
    ComplexDef test1(2,1);
    ComplexDef zero;
    zero = test * 3;
    zero.print();
    return 0;
}
