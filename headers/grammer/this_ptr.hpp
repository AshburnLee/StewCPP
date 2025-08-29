#ifndef GRAMMER_THIS_PTR_HEADER
#define GRAMMER_THIS_PTR_HEADER
#pragma once

#include <iostream>

namespace grammer {
namespace this_ptr {

class Student {
public:
    void GetName(char *name);
    void GetAge(int age);
    void PrintThis();

private:
    char *m_name;
    int m_age;
};

void Student::GetName(char *name) {
    this->m_name = name;
}
void Student::GetAge(int age) {
    this->m_age = age;
}

void Student::PrintThis() {
    std::cout << this << std::endl;
}

} // namespace this_ptr
} // namespace grammer

#endif // GRAMMER_THIS_PTR_HEADER