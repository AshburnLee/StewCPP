#ifndef GRAMMER_OVERLOAD_SUBSCRIPTOR_HEADER
#define GRAMMER_OVERLOAD_SUBSCRIPTOR_HEADER
#pragma once

#include <cmath>
#include <iostream>

namespace grammer {
namespace overload_subscriptor {

class Array {
public:
    Array(int m_length);
    ~Array();

public:
    int &operator[](int i);
    const int &operator[](int i) const;

public:
    int length() const { return m_length; }
    void display() const;

private:
    int m_length;
    int *m_ptr;
};

Array::Array(int length) : m_length(length) {
    if (length == 0) {
        m_ptr = nullptr;
    } else {
        m_ptr = new int[length];
    }
}
Array::~Array() {
    delete[] m_ptr;
}

// arr.operator[](i) = 3，将3写入m_ptr[i]，就是函数的返回值，
int& Array::operator[](int i) {
    // std::cout<< "non const [] "<<std::endl; //
    return m_ptr[i];
}
// 只读时，调用此函数
const int& Array::operator[](int i) const {
    return m_ptr[i];
}

void Array::display() const {
    for (int i = 0; i < m_length; ++i) {
        if (i == m_length - 1) {
            std::cout << m_ptr[i] << std::endl;
        } else {
            std::cout << m_ptr[i] << ", ";
        }
    }
}

} // namespace overload_subscript
} // namespace grammer

#endif // GRAMMER_OVERLOAD_SUBSCRIPTOR_HEADER
