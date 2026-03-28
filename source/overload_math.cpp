#include <cmath>
#include <iostream>

namespace grammer {
namespace overload_math {

class Complex {
public:
    Complex(double real = 0.0, double imag = 0.0) : m_real(real), m_imag(imag) {}
    double real() const { return m_real; }
    double imag() const { return m_imag; }

    friend Complex operator+(const Complex& c1, const Complex& c2);
    friend Complex operator-(const Complex& c1, const Complex& c2);
    friend Complex operator*(const Complex& c1, const Complex& c2);
    friend Complex operator/(const Complex& c1, const Complex& c2);
    friend bool operator==(const Complex& c1, const Complex& c2);
    friend bool operator!=(const Complex& c1, const Complex& c2);

    Complex& operator+=(const Complex& c);
    Complex& operator-=(const Complex& c);
    Complex& operator*=(const Complex& c);
    Complex& operator/=(const Complex& c);

private:
    double m_real;
    double m_imag;
};

Complex& Complex::operator+=(const Complex& c) {
    m_real += c.m_real;
    m_imag += c.m_imag;
    return *this;
}

Complex& Complex::operator-=(const Complex& c) {
    m_real -= c.m_real;
    m_imag -= c.m_imag;
    return *this;
}

Complex& Complex::operator*=(const Complex& c) {
    const double nr = m_real * c.m_real - m_imag * c.m_imag;
    const double ni = m_imag * c.m_real + m_real * c.m_imag;
    m_real = nr;
    m_imag = ni;
    return *this;
}

Complex& Complex::operator/=(const Complex& c) {
    const double den = std::pow(c.m_real, 2) + std::pow(c.m_imag, 2);
    const double nr = (m_real * c.m_real + m_imag * c.m_imag) / den;
    const double ni = (m_imag * c.m_real - m_real * c.m_imag) / den;
    m_real = nr;
    m_imag = ni;
    return *this;
}

Complex operator+(const Complex& c1, const Complex& c2) {
    Complex c;
    c.m_real = c1.m_real + c2.m_real;
    c.m_imag = c1.m_imag + c2.m_imag;
    return c;
}

Complex operator-(const Complex& c1, const Complex& c2) {
    Complex c;
    c.m_real = c1.m_real - c2.m_real;
    c.m_imag = c1.m_imag - c2.m_imag;
    return c;
}

Complex operator*(const Complex& c1, const Complex& c2) {
    Complex c;
    c.m_real = c1.m_real * c2.m_real - c1.m_imag * c2.m_imag;
    c.m_imag = c1.m_imag * c2.m_real + c1.m_real * c2.m_imag;
    return c;
}

Complex operator/(const Complex& c1, const Complex& c2) {
    Complex c;
    c.m_real = (c1.m_real * c2.m_real + c1.m_imag * c2.m_imag)
        / (std::pow(c2.m_real, 2) + std::pow(c2.m_imag, 2));
    c.m_imag = (c1.m_imag * c2.m_real - c1.m_real * c2.m_imag)
        / (std::pow(c2.m_real, 2) + std::pow(c2.m_imag, 2));
    return c;
}

bool operator==(const Complex& c1, const Complex& c2) {
    return c1.m_real == c2.m_real && c1.m_imag == c2.m_imag;
}

bool operator!=(const Complex& c1, const Complex& c2) {
    return c1.m_real != c2.m_real || c1.m_imag != c2.m_imag;
}

} // namespace overload_math
} // namespace grammer

using grammer::overload_math::Complex;
using namespace std;

int main() {
    Complex c1(25, 35);
    Complex c2(10, 20);
    Complex c3(1, 2);
    Complex c4(4, 9);
    Complex c5(34, 6);
    Complex c6(80, 90);

    Complex c7 = c1 + c2;
    c7 = c1.operator*=(c7);
    Complex c8 = c1 - c2;
    Complex c9 = c1 * c2;
    Complex c10 = c1 / c2;
    cout << "c7 = " << c7.real() << " + " << c7.imag() << "i" << endl;
    cout << "c8 = " << c8.real() << " + " << c8.imag() << "i" << endl;
    cout << "c9 = " << c9.real() << " + " << c9.imag() << "i" << endl;
    cout << "c10 = " << c10.real() << " + " << c10.imag() << "i" << endl;

    c3 += c1;
    c4 -= c2;
    c5 *= c2;
    c6 /= c2;
    cout << "c3 = " << c3.real() << " + " << c3.imag() << "i" << endl;
    cout << "c4 = " << c4.real() << " + " << c4.imag() << "i" << endl;
    cout << "c5 = " << c5.real() << " + " << c5.imag() << "i" << endl;
    cout << "c6 = " << c6.real() << " + " << c6.imag() << "i" << endl;

    if (c1 == c2) {
        cout << "c1 == c2" << endl;
    }
    if (c1 != c2) {
        cout << "c1 != c2" << endl;
    }
    return 0;
}
