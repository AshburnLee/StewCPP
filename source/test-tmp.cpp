#include <iostream>

int main() {
    int* a = new int[10];
    for (int i = 0; i < 10; ++i) {
        a[i] = i*2;
    }

    int* b = a;

    std::cout << &a << std::endl;
    std::cout << &b << std::endl;

    // a和b指向同一个数组，所以它们的地址是一样的
    for (int i = 0; i < 10; ++i) {
        std::cout << &a[i] << " " << &b[i] << "\n";
    }


    delete[] a;

    return 0;
}