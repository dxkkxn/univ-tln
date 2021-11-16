#include "person.h"
#include "teacher.h"
#include "student.h"
#include "subject.h"
#include "student2.h"

using namespace std;
int main() {
  /*
    float t[3] =  {2.5, 12, 23};
    Student s("LOBARDO", "Quentin", 22, 3);
    s.print();
    s.write_marks(t, 3);
    s.print();
    cout << s.average() << endl;
    Student copy(s);
    copy.print();
    Student s2("AFDADS", "Adsfaf", 21, 3);
    s2.print();
    s.print();
    s2 = s;
    s2.print();
    s.print();

    Person dg("GRAY", "Doran", 30);
    dg.grow();
    dg.print();
    cout<<endl;

    Teacher sr("ROGUE", "Severus", 50, "tenured");
    sr.work(200);
    sr.print();

    float marks_hp[4] = {12, 9, 15, 14};
    Student hp("POTTER", "Harry", 15, 4);
    hp.write_marks(marks_hp, 4);
    hp.print();
    cout << " his/her average marks is" << hp.average() << endl;

    Subject undefined;
    Subject poo("POO", 0.3);
    undefined.print();
    poo.print();
    cout << poo.get_name() << poo.get_coef() << endl;
    cout << undefined.get_name() << undefined.get_coef() << endl;
*/
    Subject sbs[4];
    sbs[0] = Subject("Magie", 3);
    sbs[1] = Subject("Potion", 2);
    sbs[2] = Subject("Divination", 4);
    sbs[3] = Subject("Info", 1);
    Student2 hp("POTTER", "Harry", 18, 4, sbs);

    float marks_hp[4] = {12, 9, 15, 14};
    hp.write_marks(marks_hp, 4);
    hp.print();
    cout << endl;
    sbs[3] = Subject("Divination", 4);
    hp.print();
    cout << hp.average() << endl;

    return 0;
}
