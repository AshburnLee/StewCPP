#ifndef GRAMMER_OVERLOAD_HEADER
#define GRAMMER_OVERLOAD_HEADER
#pragma once

#include <iostream>

namespace grammer {
namespace overload {

// 2). 全局‘+’ 号重载, 就是个一般意义上的函数
struct Ichar {
    char a;
};

char operator+(Ichar ia, Ichar ib) {
    int a, b;
    a = ia.a - 48;
    b = ib.a - 48;
    return a + b + 48;
}


// 3). 类内运算符重载
class Girl {
private:
    int m_a;
    int m_b;

public:
    Girl() {}
    Girl(int a, int b) : m_a(a), m_b(b) {}
    int GetA() { return m_a; }
    int GetB() { return m_b; }

    Girl operator+(const Girl &g) const { // this代表当前对象
        Girl tg(this->m_a + g.m_a, this->m_b + g.m_b);
        return tg;

        // *** 类对象可以直接访问自己的 private 成员
        // Girl tg;
        // tg.m_a = this->m_a + g.m_a;
        // tg.m_b = this->m_b + g.m_b;
        // return tg;
    }
};


// 4)
class Complex {
public:
    Complex();
    Complex(double real, double imag);
    Complex operator+(const Complex &a) const;
    void Show() const;

private:
    double m_real;
    double m_imag;
};
Complex::Complex() : m_real(0.f), m_imag(0.f) {}
Complex::Complex(double real, double imag) : m_real(real), m_imag(imag) {}
Complex Complex::operator+(const Complex &a) const {
    Complex b;
    b.m_real = this->m_real + a.m_real;
    b.m_imag = this->m_imag + a.m_imag;
    return b;
}
void Complex::Show() const {
    std::cout << m_real << " + " << m_imag << "i" << std::endl;
}


// 5). 声明全局范围内的运算符重载
class complex {
public:
    complex();
    complex(double real, double imag);

public:
    void display() const;
    // **** 声明为友元函数，友元函数不是成员函数
    friend complex operator+(const complex &A, const complex &B);

private:
    double m_real;
    double m_imag;
};
complex::complex() : m_real(0.0), m_imag(0.0) {}
complex::complex(double real, double imag) : m_real(real), m_imag(imag) {}
void complex::display() const {
    std::cout << m_real << " + " << m_imag << "i" << std::endl;
}
// 在全局范围内重载+
// *** 运算符重载函数不是 complex 类的成员函数，
// 但却用到了 complex 类的 private 成员变量，
// 所以必须在 complex 类中将该函数声明为友元函数 ***
// 所以要先在这里定义，后在类中声明friend ***
complex operator+(const complex &A, const complex &B) {
    complex C;
    C.m_real = A.m_real + B.m_real;
    C.m_imag = A.m_imag + B.m_imag;
    return C;
}


} // namespace overload
} // namespace grammer

#endif // GRAMMER_OVERLOAD_HEADER