#include <iostream>
#include "complex.h"
#include "vec-complex.h"
#include "poly.h"

using namespace std;

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

int main() {
  /*
    cout<<"loc_main ";
    Complex loc_main;
    f();g();
    Complex res = h();
    res.print();
    cout<<"Program end"<<endl;
  */
    ifstream file("data.txt");
    VecComplex vc(file);
    vc.print_vec();
    float arr[6] = {0.1,0.2,0.3,0.4,0.5,1};
    Poly try_poly(5,arr);
    try_poly.print();

    return 0;
}
