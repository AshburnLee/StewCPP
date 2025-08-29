#ifndef GRAMMER_TEMPLATE_H
#define GRAMMER_TEMPLATE_H
#pragma once

#include <iostream>

namespace grammer {
namespace my_template {
using namespace std;

// 全特化
template <typename T1, typename T2>
class MyPair {
public:
    MyPair(T1 val1, T2 val2): _val1(val1), _val2(val2) {}
    void Log(){
        std::cout << "Generic version: " << _val1 << ", " << _val2 << std::endl;
    }
private:
    T1 _val1;
    T2 _val2;
};

// 偏特化，注意：偏特化必须保持与原模板相同的参数数量
template <typename T1>
class MyPair<T1, int> {
public:
    MyPair(T1 val1, int val2): _val1(val1), _val2(val2) {}
    void Log(){
        std::cout << "Generic version: " << _val1 << ", " << _val2 << std::endl;
    }
private:
    T1 _val1;
    int _val2;
};


} // namespace my_tempalte
} // namespace grammer

#endif // GRAMMER_TEMPLATE_H