#include <vector>
#include <iostream>

using namespace std;
int main() {
    vector<int> v1;
    v1.assign(3, 100);
    cout<< v1.size() << v1.capacity() <<endl;
    cout<< v1.size() << v1.capacity() <<endl;
    return 0;
}
