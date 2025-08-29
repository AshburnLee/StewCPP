#include "overload_math.h"

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

    if (c1 == c2) { cout << "c1 == c2" << endl; }
    if (c1 != c2) { cout << "c1 != c2" << endl; }
    return 0;
}
