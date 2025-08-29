#ifndef GRAMMER_COPY_DEEP_HEADER
#define GRAMMER_COPY_DEEP_HEADER

#pragma once
#include <cmath>
#include <ctime>
#include <iostream>
#include <string.h>
// #include <windows.h> // win
#include <unistd.h> // linux sleep()

namespace grammer {
namespace copy_deep {

// 简单类，使用浅拷贝即可
class Base {
public:
    Base() : m_a(0), m_b(0) {}
    Base(int a, int b) : m_a(a), m_b(b) {}

private:
    int m_a;
    int m_b;
};

//=================================================== 类中有指针成员时，使用深拷贝
class My_Array {
public:
    My_Array(int len);
    My_Array(const My_Array &arr);
    ~My_Array();

public:
    // 常量版本，只允许只读访问元素 ***
    const int& operator[](int i) const { return m_ptr[i]; }
    // 非常量版本，允许修改元素 ***
    int& operator[](int i) { return m_ptr[i]; }

    // 1. getter 通常是 const 函数
    int length() const { return m_len; }

private:
    int *m_ptr;
    int m_len;
};

My_Array::My_Array(int len) : m_len(len) {
    m_ptr = (int *)calloc(len, sizeof(int));
}

// 深拷贝：拷贝一份内容，而非拷贝一个指向同一份内容的 指针
// 2. this->m_len, 表示当前instance的m_len
My_Array::My_Array(const My_Array &arr) {
    this->m_len = arr.m_len;
    this->m_ptr = (int *)calloc(this->m_len, sizeof(int));
    memcpy(this->m_ptr, arr.m_ptr, this->m_len * sizeof(int));
}
My_Array::~My_Array() {
    free(this->m_ptr);
}

// 3. 参数 arr 是 const 对象，函数体中就只能调用 My_Array 的 const 成员
void PrintMy_Array(const My_Array &arr) {
    int len = arr.length();
    for (int i = 0; i < len; i++) {
        if (i == len - 1) {
            // operator[] 需要使用 const 修饰的函数
            std::cout << arr[i] << std::endl;
        } else {
            std::cout << arr[i] << ", ";
        }
    }
}


//
class Base2 {
public:
    Base2(int a = 0);
    Base2(const Base2 &obj);

public:
    int GetCount() const { return m_count; }
    time_t GetTime() const { return m_time; }

private:
    int m_a;
    time_t m_time; // 创建对象的时间
    static int m_count; // 创建过对象的个数
};

int Base2::m_count = 0; // 初始化全局变量
// 用下两种构造函数构造的对象，count都会++
Base2::Base2(int a) : m_a(a) {
    m_count++;
    m_time = time((time_t *)nullptr); // 获取当前时间
}

// 深拷贝: 只需在拷贝构造函数中显式地做些处理
Base2::Base2(const Base2 &obj) {
    this->m_a = obj.m_a;
    // 这里 m_count & m_time 就不能是简单的浅拷贝了
    this->m_count++;
    this->m_time = time((time_t *)nullptr);
}

} // namespace copy_deep
} // namespace grammer

#endif // GRAMMER_COPY_DEEP