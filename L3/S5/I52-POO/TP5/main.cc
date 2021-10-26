#include "person.h"
#include "teacher.h"
#include "student.h"
#include "subject.h"
#include "cursus.h"

using namespace std;
int main() {
    Subject sl[3];
    sl[0] = Subject("POO");
    sl[1] = Subject("ADG");
    sl[2] = Subject("TDL");

    Teacher t1("GRAY", "Doran", 30, sl, 3);
    t1.print();
  
    return 0;
}
