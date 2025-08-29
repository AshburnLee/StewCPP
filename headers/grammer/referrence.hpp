#ifndef GRAMMER_REFERREBCE_HEADER
#define GRAMMER_REFERREBCE_HEADER
#pragma once

using namespace std;

#include <iomanip>
#include <iostream>

namespace grammer {
namespace referrence {

/*
  引用的本质
*/
int num = 99;
class A {
public:
    A();

private:
    int m_n;
    int *ptr_r;
    int &ref_r;
};
A::A() : m_n(0), ptr_r(&num), ref_r(num) {}


/*
  引用也不能指代临时数据
*/
typedef struct {
    int card1;
    int card2;
} Money;

int give_100() {
    return 100;
}

Money get_all() {
    Money a;
    a.card1 = 200;
    a.card2 = 400;
    return a;
}

Money operator+(const Money &xiao, const Money &ming) {
    Money home;
    home.card1 = xiao.card1 + ming.card1;
    home.card2 = xiao.card2 + ming.card2;
    return home;
}



/*
  临时变量不能用引用指代
*/
typedef struct {
    int a;
    int b;
} AB;

AB operator+(const AB &A, const AB &B) {
    AB C;
    C.a = A.a + B.a;
    C.b = A.b + B.b;
    return C;
}
AB func() {
    AB a;
    a.a = 100;
    a.b = 200;
    return a;
}



/*
  引用作为函数参数
*/
bool isOdd(int &n) {
    if (n % 2 == 0) {
        return false;
    } else {
        return true;
    }
}


} // namespace referrence
} // namespace grammer

#endif // GRAMMER_REFERREBCE_HEADER