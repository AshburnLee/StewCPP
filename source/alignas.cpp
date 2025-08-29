// alignas() 的作用是指定变量的对齐方式，以提高访问速度。
// 使用方式为在变量声明时使用 alignas(n)，其中n表示对齐的字节数。
// 对性能的好处是可以减少内存访问次数，提高程序的运行效率。
// 以下是一个使用alignas的例子：


#include <iostream>
#include <cstring>

// 定义一个结构体MyStruct，使用alignas(16)指定其对齐方式为16字节
// 这意味着 MyStruct 的每个实例在内存中的起始地址必须是 16 的倍数。
struct alignas(16) MyStruct {
    // 每个成员变量都有自己的对齐要求，编译器会在必要时添加填充字节，以满足这些对齐要求。
    int a; // 4字节对齐
    char b; // 1字节对齐
    double c; // 8字节对齐
};

int Test1() {
    // 输出MyStruct的大小
    std::cout << "Size of MyStruct: " << sizeof(MyStruct) << std::endl;

    // 创建一个MyStruct类型的变量s，并使用memset函数将其初始化为0
    MyStruct s;
    std::memset(&s, 0, sizeof(s));

    // 给s的成员变量a、b、c赋值，并输出它们的值
    s.a = 1;
    s.b = 'a';
    s.c = 3.14;
    std::cout << " size of a: " << sizeof(s.a) << std::endl;
    std::cout << " size of b: " << sizeof(s.b) << std::endl;
    std::cout << " size of c: " << sizeof(s.c) << std::endl;

    std::cout << " address of a: " << &(s.a) << std::endl;
    std::cout << " address of b: " << &(s.b) << std::endl;
    std::cout << " address of c: " << &(s.c) << std::endl;

    std::cout << " size of s: " << sizeof(s) << std::endl;
    std::cout << " alignof of s: " << alignof(s) << std::endl;
    std::cout << " Offset of a: " << offsetof(MyStruct, a) << " bytes" << std::endl;
    std::cout << " Offset of b: " << offsetof(MyStruct, b) << " bytes" << std::endl;
    std::cout << " Offset of c: " << offsetof(MyStruct, c) << " bytes" << std::endl;

    /*
    size of s: 16
    alignof of s: 16
    Offset of a: 0 bytes
    Offset of b: 4 bytes
    Offset of c: 8 bytes
    */
    return 0;
}


struct MyData {
  float value;
  char padding[5]; // 填充 3 个字节，使结构体大小为 4 的倍数
};
int Test2() {
  MyData myDataArray[10];

  // 打印每个对象的起始地址和与前一个对象的地址差
  for (int i = 0; i < 10; ++i) {
    std::uintptr_t address = reinterpret_cast<std::uintptr_t>(&myDataArray[i]);
    std::cout << "MyData[" << i << "] address: " << address << std::endl;
    if (i > 0) {
      std::uintptr_t prevAddress = reinterpret_cast<std::uintptr_t>(&myDataArray[i - 1]);
      std::cout << "Difference from previous: " << address - prevAddress << " bytes" << std::endl;
    }
  }

  return 0;
}

int main() {
  Test1();
  Test2();
  return 0;
}