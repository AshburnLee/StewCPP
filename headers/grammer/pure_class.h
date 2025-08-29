#ifndef GRAMMER_PURE_CLASS_HEADER
#define GRAMMER_PURE_CLASS_HEADER
#pragma once

#include <memory>
#include <vector>
#include <iostream>

namespace grammer {
namespace pure_class {
using namespace std;

class IShape {
public:
    virtual double GetArea() const = 0;
    virtual void ZhouChang() const = 0;
    virtual ~IShape() {}
};

class Circle : public IShape {
public:
    Circle(double r) : _radius(r) {}
    double GetArea() const override {
        return 3.14 * _radius * _radius;
    }
    void ZhouChang() const override {
        cout << "Circle ZhouChang: " << 2 * 3.14 * _radius << endl;
    }
private:
    double _radius;
};

class Rectangle : public IShape {
public:
    Rectangle(double l, double w) : _height(l), _width(w) {}
    double GetArea() const override {
        return _height * _width;
    }
    void ZhouChang() const override {
        cout << "Rectangle ZhouChang: " << 2 * (_height + _width) << endl;
    }
private:
    double _height;
    double _width;
};

} // namespace pure_class
} // namespace grammer

#endif // GRAMMER_PURE_CLASS_HEADER