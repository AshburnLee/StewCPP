#ifndef GRAMMER_LAMBDA_HEADER
#define GRAMMER_LAMBDA_HEADER
#pragma once

#include <iostream>

using namespace std;
namespace grammer {
namespace lambda {

// lambda 函数的最基本使用
int add(int y) {
    int x = 10;
    auto Adder = [&x](int y) { return x + y; };
    return Adder(y);
}

class Person {
private:
    int _age;
    std::string _name;
public:
    Person(int age, std::string name): _age(age), _name(name) {}
    int GetAge() const { return _age;}
    std::string GetName() const { return _name;}
};

auto AgeLess = [](Person& a, Person& b){ return a.GetAge() < b.GetAge();};
auto AgeGreater = [](Person& a, Person& b){ return a.GetAge() > b.GetAge();};

} // namespace lambda
} // namespace grammer

#endif // GRAMMER_LAMBDA_HEADER