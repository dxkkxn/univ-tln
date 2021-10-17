#include "person.h"
#include "teacher.h"
#include "student.h"

using namespace std;
int main() {
    /*
    float t[3] =  {2.5, 12, 23};
    Student s("LOBARDO", "Quentin", 22, 3);
    s.print();
    s.add_marks(t, 3);
    s.print();
    cout << s.average() << endl;
    Student copy(s);
    Student s2("AFDADS", "Adsfaf", 21, 3);
    s2.print();
    s.print();
    s2 = s;
    s2.print();
    s.print();
    */
    Person dg("GRAY", "Doran", 30);
    dg.grow();
    dg.print();
    cout<<endl;

    Teacher sr("ROGUE", "Severus", 50, "tenured");
    sr.work(200);
    sr.print();

    float marks_hp[4] = {12, 9, 15, 14};
    Student hp("POTTER", "Harry", 15, 4);
    hp.add_marks(marks_hp, 4);
    hp.print();
    cout << "his/her average marks is" << hp.average() << endl;



    return 0;
}
