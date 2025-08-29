#include "friends.hpp"
#include <vector>

using grammer::friends::Address;
using grammer::friends::Employee;
using grammer::friends::Student;

void Test1() {
    Student *junhui = new Student("Junhui", 23, "Hongyu Apartment");
    Student *jianhui = new Student("Jinahui", 45, "zizhu high-tech park");
    std::vector<Student *> room = {junhui, jianhui};
    for (auto stu : room) {
        Visit(stu);
    }
}

void Test2() {
    Employee *emp = new Employee("Junhui", 23);
    // emp 可以访问 addr中的所有成员
    Address *addr = new Address("Henan", "Anyang", "Kaifaqu");
    emp->Show(addr);
}

int main() {
    Test1();
    Test2();
    return 0;
}
