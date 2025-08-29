#ifndef GRAMMER_INHERIT_HEADER
#define GRAMMER_INHERIT_HEADER
#pragma once

#include <iostream>

namespace grammer {
namespace inherit {

class OOO {
public:
    OOO() {}

    virtual void DisplayName() { std::cout << "OOO name: " << _name << std::endl; }
    virtual ~OOO() { std::cout << "~OOO \n"; }

private:
    std::string _name;
};

class Student : public OOO {
public:
    Student(const std::string& name, int id) : _name(name), _id(id) {}
    ~Student() { std::cout << "~Student \n"; }

    // 因为 DisplayName 被声明为虚函数（virtual），这使得在运行时能够调用实际对象类型的实现
    // 根据实际对象 进行动态绑定
    virtual void DisplayName() { std::cout << "Student name: " << _name << std::endl; }

    void PrintID() { std::cout << "id: " << _id << std::endl; }

private:
    std::string _name;
    int _id;
};

} // namespace inherit
} // namespace grammer

#endif // GRAMMER_INHERIT_HEADER