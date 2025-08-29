#ifndef GRAMMER_COPY_CONSTRUCTOR_HEADER
#define GRAMMER_COPY_CONSTRUCTOR_HEADER
#pragma once

#include <cmath>
#include <iostream>
using namespace std;

namespace grammer {
namespace copy_constructor {

class Student {
public:
    Student(string name = "", int ages = 0, float score = 0.f);
    // 拷贝构造函数，***也是构造函数，用于初始化对象
    // ***记住，参数是 const &
    Student(const Student &stu);

public:
    void Display();

private:
    string m_name;
    int m_age;
    float m_score;
};

Student::Student(string name, int age, float score)
    : m_name(name), m_age(age), m_score(score) {}
// 拷贝构造函数
Student::Student(const Student &stu) {
    // ***将外部stu对象的成员 拷贝给当前对象（this）
    this->m_name = stu.m_name;
    this->m_age = stu.m_age;
    this->m_score = stu.m_score;
    cout << "copy constructor is called\n";
}

void Student::Display() {
    cout << m_name << " age: " << m_age << " score: " << m_score << endl;
}


} // namespace copy_constructor
} // namespace grammer

#endif // GRAMMER_COPY_CONSTRUCTOR_HEADER