#include <iostream>
#include "swap.h"
#include "complex.h"

using namespace std;
int main() {
    /*
    int x = 2, y = 22;
    cout<<"x = "<<x<<"y ="<<y<<endl;
    swap(x,y);
    cout<<"After swap\n"<<"x = "<<x<<"y ="<<y<<endl;
    complex_num a = {2, 5}; 
    complex_num b = {3, 7};
    cout<<"a =", print_complex_num(a);
    cout<<"b =", print_complex_num(b);

    swap(a,b);
    cout<<"a =", print_complex_num(a);
    cout<<"b =", print_complex_num(b);

    print_complex_num(product(conjugate(a),a));
    cout<<"==";
    cout<<module(a)*module(a)<<"?"<<endl;
    */
    complex_num a; 
    cout<<"adresse a = "<<&a<<endl;
    cout<<"adresse a.ident ="<< &a.ident<<endl;
    cout<<"adresse a.re ="<< &a.re<<endl;
    cout<<"adresse a.im ="<< &a.im<<endl;
    complex_num& a_ref = a;
    cout<<"adresse a_ref = "<<&a_ref<<endl;
    cout<<"adresse a_ref.ident ="<< &a_ref.ident<<endl;
    cout<<"adresse a_ref.re ="<< &a_ref.re<<endl;
    cout<<"adresse a_ref.im ="<< &a_ref.im<<endl;
    
    complex_num recep;
    recep = bidon(a);
    cout<<"adresse recep = "<<&recep<<endl;
    cout<<"adresse recep.ident ="<< &recep.ident<<endl;
    cout<<"adresse recep.re ="<< &recep.re<<endl;
    cout<<"adresse recep.im ="<< &recep.im<<endl;
    complex_num *tab = create_vect_complex(3);
    for(int i = 0; i < 3; i++)
        cout<<"tab["<<i<<"]"<<"adresse ="<<&tab[i]<<endl;
    

    return 0;
}



