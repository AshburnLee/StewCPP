#ifndef GRAMMER_CLASS_HEADER
#define GRAMMER_CLASS_HEADER
#pragma once

#include <iostream>

namespace grammer {
namespace class_size {

class Base {
    int fst = 0;
    char sec = char(1);
    int third = 2;
};

class Child : public Base {
    // static成员不属于类的对象，而是属于整个类，因此它不会影响类的大小。
    // 在内存中，static成员通常被存储在全局数据区或静态数据区
    static int forth; // staic 不占空间，不可赋值
};

class Empty {};

} // namespace class_size
} // namespace grammer

#endif // GRAMMER_CLASS_HEADER
