#include "type_convertion_func.h"

using grammer::type_convertion_func::Cfloat;
using grammer::type_convertion_func::Complex2;
using grammer::type_convertion_func::complex;
using namespace std;

void Test1() {
    Cfloat cf(3.1412);
    cout << "force convert before: " << cf.GetNum() << endl;
    cout << "force convert after: [exp=3]" << (int)cf << ", " << int(cf)
         << endl;
}

void Test2() {
    Complex2 c(1.2, 3.4);
    cout << "exp=[1.2] actual=" << (double)c << ", infact "
         << c.operator double() << endl;
    double n = 2 + c;
    cout << "exp=[3.2] actual=" << n << endl;
}

void Test3() {
    complex c1(12.3, 100);
    double f = c1;
    int i = complex(2.1, 3.2);
    cout << "complex c1 = " << f << endl;
    cout << "float f = " << c1 << endl;
    cout << "int i = " << i << endl; // 先转为double再转为int
}

int main() {
    cout << "------------------------type_convertion_func\n";
    Test1();
    Test2();
    Test3();
    return 0;
}
