#ifndef GRAMMER_OVERLOAD_ASSIGNMENT_HEADER
#define GRAMMER_OVERLOAD_ASSIGNMENT_HEADER
#pragma once

#include <cmath>
#include <cstring>
#include <iostream>

namespace grammer {
namespace overload_assignment {

class Array {
public:
    Array(int len);
    Array(const Array &arr);
    ~Array();

public:
    // 获取元素 ***只读元素，只能放在=右边
    // int operator[](int i) const { return m_ptr[i]; }
    // 获取元素 写入
    int &operator[](int i) { return m_ptr[i]; }
    // *****读 const 对象时用；不能写入，因为返回值是const
    const int &operator[](int i) const { return m_ptr[i]; }

public:
    // 赋值运算符
    Array &operator=(const Array &arr);
    int length() const { return m_length; }

private:
    int m_length;
    int *m_ptr;
};

Array::Array(int len) : m_length(len) {
    m_ptr = (int *)calloc(len, sizeof(int));
}
Array::Array(const Array &arr) {
    this->m_length = arr.m_length;
    this->m_ptr = (int *)calloc(this->m_length, sizeof(int));
    // 从arr.m_ptr 拷贝到this->m_ptr
    memcpy(this->m_ptr, arr.m_ptr, m_length * sizeof(int));
}
Array::~Array() {
    free(m_ptr);
}

Array &Array::operator=(const Array &arr) {
    if (this != &arr) { // 判断是否给自己赋值
        this->m_length = arr.m_length;
        free(this->m_ptr);
        this->m_ptr = (int *)calloc(this->m_length, sizeof(int));
        memcpy(this->m_ptr, arr.m_ptr, m_length * sizeof(int));
    }
    return *this;  //支持链式拷贝
}

void ShowArray(const Array &arr) {
    int len = arr.length();
    for (int i = 0; i < len; ++i) {
        if (i == len - 1) {
            std::cout << arr[i] << std::endl;
        } else {
            std::cout << arr[i] << ", ";
        }
    }
}

} // namespace overload_assignment
} // namespace grammer

#endif //  GRAMMER_OVERLOAD_ASSIGNMENT_HEADER
