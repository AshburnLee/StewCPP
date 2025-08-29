#ifndef GRAMMER_CPP11_HEADER
#define GRAMMER_CPP11_HEADER
#pragma once

#include <memory>
#include <stdio.h>
#include <iostream>

namespace grammer {
namespace cpp11 {

/// 类内初始化
struct Data {
    int a = 0;
    int b = 2;
};



/// constexpr
/*
constexpr int Pow(int x, int n) {
    int res = x;
    while(--n > 0) {
        res *= x;
    }
    return res;
}
*/

// constexpr 函数体只能有一个return语句，
constexpr int Pow(int x, int n) {
    return n == 0 ? 1 : x * Pow(x, n - 1);
}
constexpr int Add(int x, int y) {
    return x + y;
}



/// 委托构造函数
class Test {
public:
    Test(int n) {}
    Test() : Test(0) {}
};


/*
委托构造函数是指一个构造函数调用同一个类的另一个构造函数来完成部分或全部的初始化工作。
在上面的代码中，Person类定义了4个构造函数，
其中三个构造函数都使用了委托构造函数来完成初始化工作。
例如，第一个构造函数默认初始化了name_和age_成员变量，
然后调用了另一个构造函数Person("", 0)来完成初始化。
这样做的优势是可以避免代码重复，提高代码的可维护性和可读性。
同时，委托构造函数还可以使得类的构造函数更加灵活，
可以根据不同的参数组合来选择不同的初始化方式。
*/

class Person {
public:
    Person() : Person("", 0) {}
    Person(std::string name) : Person(name, 0) {}
    Person(int age) : Person("", age) {}
    Person(std::string name, int age) : name_(name), age_(age) {}

    void printInfo() {
        std::cout << "Name: " << name_ << ", Age: " << age_ << std::endl;
    }

private:
    std::string name_;
    int age_;
};


} // namespace cpp11
} // namespace grammer

#endif // GRAMMER_CPP11_HEADER
