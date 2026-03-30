#include <iostream>

int main() {
    int a = 10, b = 20;
    int& r = a;      // r 绑定到 a
    r = b;           // 这是“给 a 赋值”，不是把 r 重新绑到 b
    std::cout << "a=" << a << ", b=" << b << ", r=" << r << "\n";
    std::cout << "&a=" << &a << ", &b=" << &b << ", &r=" << &r << "\n";

    int* p = &r;  // r 始终是 a 的别名，p 指向的是 a。
    std::cout << "content of p: " << *p << "\n"; 
}

// r 是a 的别名，就始终是 r的别名，&r 就是 &a 
