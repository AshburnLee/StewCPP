#ifndef GRAMMER_STATIC_IN_CLASS_HEADER
#define GRAMMER_STATIC_IN_CLASS_HEADER
#pragma once

#include <iostream>

namespace grammer {
namespace static_class {

class StaticObj {
public:
    int a = 1;
    //static int b = 2; // 1). 编译报错 不能类内初始化
    static int b;
    static const int c = 3; // 2). const 修饰就可以类内初始化
    StaticObj() { b++; };
    int GetB() { return b; }

    // static int GetBs() {return a;} // 6). static函数中只能用static类变量
    static int GetBs() { return b; }
};

int StaticObj::b = 2; // 5). 只能在类外初始化



// static 修饰一般变量
void _func() {
    int n = 0;
    static int m = 0; // m 是全局変量而 非函数私有変量
    n++;
    m++;
    printf("non static: %zd\n", n);
    printf("static: %zd\n", m);
}



class Student {
public:
    Student(char *name, float score);
    void Show();

private:
    static int m_total; //静态成员变量
private:
    char *m_name;
    float m_score;
};
int Student::m_total = 0;
Student::Student(char *name, float score) : m_name(name), m_score(score) {
    m_total++;
}
void Student::Show() {
    std::cout << m_name << " score is: " << m_score
         << ", total student is: " << m_total << std::endl;
}



class Student2 {
public:
    Student2(char *name, float score);
    void Show();

public: // 声明静态成员函数
    static int getTotal();
    static float getPoints();

private:
    static int m_total; //总人数
    static float m_points; //总成绩
private:
    char *m_name;
    int m_age;
    float m_score;
};
int Student2::m_total = 0;
float Student2::m_points = 0.0;
Student2::Student2(char *name, float score) : m_name(name), m_score(score) {
    m_total++;
    m_points += score;
}
void Student2::Show() {
    std::cout << m_name << " age is: " << m_age << ", score: " << m_score << std::endl;
}
//定义静态成员函数
int Student2::getTotal() {
    return m_total;
}
float Student2::getPoints() {
    return m_points;
}


} // namespace static_class
} // namespace grammer

#endif // GRAMMER_STATIC_IN_CLASS_HEADER
