#include "enclosed_class.hpp"

using grammer::enclosed_class::Outer;
using grammer::enclosed_class::Car;

void test_outer() { 
    Outer out; 
    out.show_inner();
}

void test_car() {
    Car myCar("Toyota Camry", "Toyota 2.5L", 178);
    myCar.startCar();
}

int main() {
    test_outer();
    test_car();
    return 0;
}
