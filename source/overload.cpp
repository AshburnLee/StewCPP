#include "overload.h"

using grammer::overload::Complex;
using grammer::overload::complex;
using grammer::overload::Girl;
using grammer::overload::Ichar;
using namespace std;

void Test2() {
    Ichar i1;
    Ichar i2;
    i1.a = '2';
    i2.a = '1';
    char i3 = i1 + i2;
    // char i3 = operator+(i1, i2); // *** 这是本质上，同一般函数调用
    std::cout << "Ichar+ichar, exp=3, actual=[" << i3 << "]" << std::endl;
}

void Test3() {
    Girl g1(10, 20);
    Girl g2(20, 10);

    Girl g3 = g1 + g2;
    // Girl g3 = g1.operator+(g2); // *** 本质上的，同一般成员函数调用
    cout << "in class operator+: " << g3.GetA() << " " << g3.GetB()
         << endl; // 外部函数不能直接访问private
}

void Test4() {
    Complex a(1.2, 2.3);
    Complex b(2.1, 3.2);
    // Complex c = a + b;
    // 在 Complex 类中重载了运算符+，该重载只对 Complex 对象有效,
    // 当执行c = a + b; 语句时，编译器检测到+号左边（+号具有左结合性，所以先检测左边）
    // 是一个 complex 对象，就会调用成员函数operator+()，也就是转换为下面的形式：
    Complex c = a.operator+(b);
    c.Show();
}

void Test5() {
    complex c1(4.3, 5.8);
    complex c2(2.4, 3.7);
    complex c3;
    c3 = c1 + c2;
    c3.display();
}

int main() {
    Test2();
    Test3();
    Test4();
    Test5();
    return 0;
}