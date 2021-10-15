#include "person.h"
#include <string>

int main() {
    
    Person undefined;
    Person p("LOBARDO", "Quentin", 22);
    Person p2(p);
    undefined.print();
    p.print();
    p2.print();
    return 0;
}
