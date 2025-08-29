#include "inherit.h"

using grammer::inherit::Student;
using grammer::inherit::OOO;
using namespace std;

void InheritTest() {
    OOO *p = new Student("junhui", 157);
    p->DisplayName();
    // 调用子类的析构函数, 然后 调用父类析构函数。
    // 如此确保了派生类和基类的析构函数都被正确调用，避免了资源泄漏和未定义行为。
    delete p;

    // p访问不到 PrintID()
    Student *q = new Student("junhui", 157);
    q->DisplayName();
    q->PrintID();
}

int main() {
    cout << "------------------------inherit\n";
    InheritTest();
    return 0;
}
