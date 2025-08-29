#include "this_ptr.hpp"

using grammer::this_ptr::Student;
using namespace std;

// test
int main() {
    Student *stu1 = new Student;
    // this 确实指向了当前对象
    stu1->PrintThis();
    cout << stu1 << endl;

    // 对于不同的对象， this值不同
    Student *stu2 = new Student;
    stu2->PrintThis();
    cout << stu2 << endl;
    return 0;
}
