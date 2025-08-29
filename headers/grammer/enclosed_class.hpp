#ifndef GRAMMER_ENCLOSED_CLASS_HEADER
#define GRAMMER_ENCLOSED_CLASS_HEADER
#pragma once

#include <iostream>
using namespace std;

namespace grammer {
namespace enclosed_class {

/// 封闭类通常指：嵌套类
class Outer {
public:
    // Inner 只能在Outer 作用域内访问，不能在Outer外部被访问
    // 嵌套类优势在于可以将相关的类和函数组织在一起，提高代码的可读性和可维护性。
    // 此外，嵌套类还可以隐藏实现细节，防止外部代码直接访问内部类的成员变量和成员函数，
    // 从而提高代码的安全性
    class Inner {
    public:
        Inner() = default;
        Inner(string name, int age): name__(name), age__(age) {}
        void hello_inner() {
            std::cout << "Hello from Inner::hello_inner!" << std::endl;
        }
        // Inner 类可以访问 Outer 类的私有成员
        void show_outer(Outer& out) {
            std::cout << "Outer name: " << out.name__ << std::endl;
        }
    private:
        string name__;
        int age__;
    };

    void show_inner() {
        inner_.hello_inner();
        inner_.show_outer(*this);
    }
private:
    Inner inner_;
    string name__ = "Outer";
};



class Car {
private:
  class Engine { // 嵌套类 Engine，私有成员
  public:
    std::string model;
    int horsepower;

    Engine(std::string model, int horsepower) : model(model), horsepower(horsepower) {}

    void start() {
      std::cout << "Engine started: " << model << std::endl;
    }
  };

  Engine* engine;
  std::string model;

public:
  Car(std::string carModel, std::string engineModel, int horsepower) : model(carModel) {
    engine = new Engine(engineModel, horsepower);
  }

  ~Car() {
    delete engine;
  }

  void startCar() {
    engine->start();
    std::cout << "Car started: " << model << std::endl;
  }
};


} // namespace enclosed_class
} // namespace grammer

#endif // GRAMMER_ENCLOSED_CLASS_HEADER
