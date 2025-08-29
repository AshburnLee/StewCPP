#include "cpp11.h"

using grammer::cpp11::Add;
using grammer::cpp11::Pow;
using grammer::cpp11::Data;
using grammer::cpp11::Test;
using grammer::cpp11::Person;
using namespace std;

/// unique_ptr
void TestUniquePtr() {
    unique_ptr<Data> data(new Data);
    // unique_ptr<Data> data = make_unique<Data>();  // c++14
    std::cout << "unique_ptr: " << data->a << " " << data->b << "\n";
    std::cout << "size of unique_ptr: " << sizeof(data) << '\n'; // 8字节
    // 当data离开的起作用域时，会自动释放

    shared_ptr<Data> data2(new Data);
    std::cout << "shared_ptr: " << data2->a << " " << data2->b << "\n";
    std::cout << "size of shared_ptr: " << sizeof(data2) << '\n'; // 16字节
}

void TestConstexpr() {
    // 静态数组大小一定是个常量！
    // 此处编译器最将[]中替换为8，常量
    int a[Add(2, 3)] = {};
    int b[Pow(2, 3)] = {};
}

void TestPerson() {
    Person p1;
    p1.printInfo(); // Output: Name: , Age: 0

    Person p2("Alice");
    p2.printInfo(); // Output: Name: Alice, Age: 0

    Person p3(25);
    p3.printInfo(); // Output: Name: , Age: 25

    Person p4("Bob", 30);
    p4.printInfo(); // Output: Name: Bob, Age: 30
}

int main() {
    TestUniquePtr();
    TestConstexpr();
    TestPerson();
    return 0;
}