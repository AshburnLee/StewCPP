#include <iostream>

void test1() {
    int a = 10, b = 20;
    int& r = a;      // r 绑定到 a
    r = b;           // 这是“给 a 赋值”，不是把 r 重新绑到 b
    std::cout << "a=" << a << ", b=" << b << ", r=" << r << "\n";
    std::cout << "&a=" << &a << ", &b=" << &b << ", &r=" << &r << "\n";

    int* p = &r;  // r 始终是 a 的别名，p 指向的是 a。
    std::cout << "content of p: " << *p << "\n"; 
    return;
}

int& func(int& x) {
    return x;
}
int& inc(int& x){
    x += 2;
    return x;
}

// 返回左值引用的函数 可以被赋值
void test2() {
    int a = 5;
    func(a) = 10;
    inc(a) = 10;  // a += 2, a = 12, 这里又给a赋值10, 故a=10
    std::cout << a << "\n"; // Output: 10
    return;
}

int main(){
    test1();
    test2();
    return 0;
}

// r 是a 的别名，就始终是 r的别名，&r 就是 &a 
