#include "referrence.hpp"

using grammer::referrence::A;
using grammer::referrence::Money;
using grammer::referrence::num;
using grammer::referrence::AB;
using grammer::referrence::isOdd;
using grammer::referrence::give_100;

/*
  引用的本质
*/
void Test1() {
    A *a = new A();
    //输出A类型的大小
    cout << sizeof(A) << endl;
    //输出r本身的内容
    cout << hex << showbase << *((int *)a + 1) << endl;
    // 输出num的地址
    cout << &num << endl;
    return;
}

/*
  引用也不能指代临时数据
*/
void Test2() {
    int m = 100, n = 36;
    /* 以下编译报错
    int &r1 = m + n;
    int &r2 = m + 28;
    int &r3 = 12 * 3;
    int &r4 = 50;
    int &r5 = give_100();
    */
}

/*
  临时变量不能用引用指代
*/
void Test3() {
    AB s1 = {23, 45};
    AB s2 = {90, 75};
    AB *ptr = &s1; // pass,
    //AB *p1 = &(s1 + s2); // 临时变量 error: taking address of rvalue
    //AB *p2 = &(func());  // 临时变量 error: taking address of rvalue
}

/*
  引用作为函数参数
*/
void Test4() {
    int a = 100;
    isOdd(a); //正确
    // isOdd(a + 9);  //错误
    // isOdd(27);  //错误
    // isOdd(23 + 55);  //错误
}

int main() {
    Test1();
    Test2();
    Test3();
    Test4();
    return 0;
}
