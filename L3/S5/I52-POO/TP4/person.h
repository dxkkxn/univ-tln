#include <string>

using std::string;
class Person {
    private:
        std::string name;
        std::string surname;
        unsigned int age;
    public:
        Person();
        Person(string name, string surname, unsigned age);
        Person(const Person & );
        void print();
        void grow();
        
};
