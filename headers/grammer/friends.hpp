#ifndef GRAMMER_FRIENDS_HEADER
#define GRAMMER_FRIENDS_HEADER
#pragma once

#include <iostream>
#include <string>

namespace grammer {
namespace friends {

/// 非成员位友元
class Student {
public:
    Student(const std::string& name, int age, const std::string& addr);

private:
    std::string m_name;
    int m_age;
    std::string m_addr;

public:
    // 将类外部函数声明为友元函数
    // Visit(): 我想访问这个类中的所有私有成员
    friend void Visit(Student *st);
};

Student::Student(const std::string& name, int age, const std::string& addr)
    : m_name(name), m_age(age), m_addr(addr) {}

// 非成员函数，声明为friend 目的只是访问类private成员
void Visit(Student *st) {
    std::cout << st->m_name << ", AGE: " << st->m_age << ", ADDR: " << st->m_addr
         << std::endl;
}


/// 其他类成员位友元
class Address; // 前项声明

class Employee {
public:
    Employee(const std::string& name, int age);

private:
    std::string m_name;
    int m_age;

public:
    void Show(Address *addr);
};

class Address {
public:
    Address(char *province, char *city, char *districe);

private:
    char *m_province;
    char *m_city;
    char *m_district;

public:
    friend class Employee; //employee 可以访问address中的所有成员
};

Employee::Employee(const std::string& name, int age) : m_name(name), m_age(age) {}

void Employee::Show(Address *addr) {
    std::cout << m_name << ", age: " << m_age;
    std::cout << " Home Address: " << addr->m_province << ", " << addr->m_city
         << ", " << addr->m_district << std::endl;
}

Address::Address(char *pro, char *city, char *dist)
    : m_province(pro), m_city(city), m_district(dist) {}


} // namespace friends
} // namespace grammer

#endif // GRAMMER_FRIENDS_HEADER