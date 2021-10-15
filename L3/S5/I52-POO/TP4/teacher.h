#include <string>
using std::string;

class Teacher: public Person{
    private:
        std::string statut;
        unsigned int hours;
    public:
        Teacher();
        Teacher(string surname, string name, unsigned age, string statut);
        Teacher(const Teacher&);
        void print();
        void work();
        
};
