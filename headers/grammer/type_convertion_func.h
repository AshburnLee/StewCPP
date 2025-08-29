#ifndef GRAMMER_TYPE_CONVERTION_FUNC_HEADER
#define GRAMMER_TYPE_CONVERTION_FUNC_HEADER
#pragma once

#include <iostream>

namespace grammer {
namespace type_convertion_func {

// 1). 将类强制转换为int，(其实就是转化类成员)
class Cfloat {
public:
    Cfloat(float m) : m_num(m) {}
    // ***
    inline operator int() const { return (int)m_num; }
    float GetNum() { return m_num; }

private:
    float m_num;
};



// 2) 重载强制转换运算符
// 下面的程序对 double 类型强制转换运算符进行了重载
class Complex2 {
private:
    double m_real;
    double m_imag;

public:
    Complex2(double real = 0.0, double imag = 0.0)
        : m_real(real), m_imag(imag) {};
    // 重载强制类型转换运算符时，不需要指定返回值类型，
    // 因为返回值类型是确定的，就是运算符本身代表的类型，在这里就是 double。
    inline operator double() const { return m_real; }
};


// 3).
class complex {
public:
    complex() : m_real(0.f), m_imag(0.f) {}
    complex(double real, double imag) : m_real(real), m_imag(imag) {}

public:
    friend complex operator+(const complex &c1, const complex &c2);
    friend std::ostream &operator<<(std::ostream &out, const complex &c); // 打印运算符
    inline operator double() const { return m_real; }

private:
    double m_real;
    double m_imag;
};
// 全局 operator+， *** 用到了complex对象private成员，必须在类里边声明友元
complex operator+(const complex &c1, const complex &c2) {
    complex res;
    res.m_real = c1.m_real + c2.m_real;
    res.m_imag = c1.m_imag + c2.m_imag;
    return res;
}
// 全局 operator<< ，*** 用到了complex对象private成员，所以要在complex中声明友元
std::ostream &operator<<(std::ostream &out, const complex &c) {
    out << c.m_real << " + " << c.m_imag << "i\n";
    return out;
}


} // namespace type_convertion_func
} // namespace grammer

#endif // GRAMMER_TYPE_CONVERTION_FUNC_HEADER
