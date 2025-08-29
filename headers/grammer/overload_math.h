#ifndef GRAMMER_OVERLOAD_MATH_HEADER
#define GRAMMER_OVERLOAD_MATH_HEADER
#pragma once

#include <cmath>
#include <iostream>

namespace grammer {
namespace overload_math {

class Complex {
public:
    Complex(double real = 0.0, double imag = 0.0)
        : m_real(real), m_imag(imag) {}
    double real() const { return m_real; } // getter 通常是const
    double imag() const { return m_imag; }

public:
    // 以全局函数形式重载，friend 不是成员函数，只是声明为这个类的friend
    friend Complex operator+(const Complex &c1, const Complex &c2);
    friend Complex operator-(const Complex &c1, const Complex &c2);
    friend Complex operator*(const Complex &c1, const Complex &c2);
    friend Complex operator/(const Complex &c1, const Complex &c2);
    friend bool operator==(const Complex &c1, const Complex &c2);
    friend bool operator!=(const Complex &c1, const Complex &c2);

    // 以成员函数形式重载
    Complex &operator+=(const Complex &c);
    Complex &operator-=(const Complex &c);
    Complex &operator*=(const Complex &c);
    Complex &operator/=(const Complex &c);

private:
    double m_real;
    double m_imag;
};

// 以成员函数重载 自运算
//重载+=运算符
Complex &Complex::operator+=(const Complex &c) {
    this->m_real += c.m_real;
    this->m_imag += c.m_imag;
    return *this;
}
//重载-=运算符
Complex &Complex::operator-=(const Complex &c) {
    this->m_real -= c.m_real;
    this->m_imag -= c.m_imag;
    return *this;
}
//重载*=运算符
Complex &Complex::operator*=(const Complex &c) {
    this->m_real = this->m_real * c.m_real - this->m_imag * c.m_imag;
    this->m_imag = this->m_imag * c.m_real + this->m_real * c.m_imag;
    return *this;
}
//重载/=运算符
Complex &Complex::operator/=(const Complex &c) {
    this->m_real = (this->m_real * c.m_real + this->m_imag * c.m_imag)
            / (pow(c.m_real, 2) + pow(c.m_imag, 2));
    this->m_imag = (this->m_imag * c.m_real - this->m_real * c.m_imag)
            / (pow(c.m_real, 2) + pow(c.m_imag, 2));
    return *this;
}

// 全局形式重载
//重载+运算符
Complex operator+(const Complex &c1, const Complex &c2) {
    Complex c;
    c.m_real = c1.m_real + c2.m_real; // friend，所以可以访问private成员
    c.m_imag = c1.m_imag + c2.m_imag;
    return c;
}
//重载-运算符
Complex operator-(const Complex &c1, const Complex &c2) {
    Complex c;
    c.m_real = c1.m_real - c2.m_real;
    c.m_imag = c1.m_imag - c2.m_imag;
    return c;
}
//重载*运算符  (a+bi) * (c+di) = (ac-bd) + (bc+ad)i
Complex operator*(const Complex &c1, const Complex &c2) {
    Complex c;
    c.m_real = c1.m_real * c2.m_real - c1.m_imag * c2.m_imag;
    c.m_imag = c1.m_imag * c2.m_real + c1.m_real * c2.m_imag;
    return c;
}
//重载/运算符  (a+bi) / (c+di) = [(ac+bd) / (c²+d²)] + [(bc-ad) / (c²+d²)]i
Complex operator/(const Complex &c1, const Complex &c2) {
    Complex c;
    c.m_real = (c1.m_real * c2.m_real + c1.m_imag * c2.m_imag)
            / (pow(c2.m_real, 2) + pow(c2.m_imag, 2));
    c.m_imag = (c1.m_imag * c2.m_real - c1.m_real * c2.m_imag)
            / (pow(c2.m_real, 2) + pow(c2.m_imag, 2));
    return c;
}
//重载==运算符
bool operator==(const Complex &c1, const Complex &c2) {
    if (c1.m_real == c2.m_real && c1.m_imag == c2.m_imag) {
        return true;
    } else {
        return false;
    }
}
//重载!=运算符
bool operator!=(const Complex &c1, const Complex &c2) {
    if (c1.m_real != c2.m_real || c1.m_imag != c2.m_imag) {
        return true;
    } else {
        return false;
    }
}


} // namespace overload_math
} // namespace grammer

#endif // GRAMMER_OVERLOAD_MATH_HEADER
