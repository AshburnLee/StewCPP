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

#include <cstdint>
#include <type_traits>

template <std::size_t N, typename T>
bool is_aligned(const T* p) {
  static_assert((N & (N - 1)) == 0, "N must be power of two");
  auto addr = reinterpret_cast<std::uintptr_t>(p);
  return (addr & (N - 1)) == 0;
}

template <std::size_t N>
size_t do_align(size_t size) {
    // 将 size 增加到下一个对齐边界的临界值 & 掩码
    return (size + (N - 1)) & ~(N - 1);
}

namespace {
  struct S { double x; };
}

void Test3(){
  S s;
  bool ok = is_aligned<alignof(S), S>(&s);
  std::cout << "Is aligned: " << ok << std::endl; // 1=true
  return;
}

// 先构造一个“可能未对齐”的指针，再用 do_align 强制对齐并验证
void Test4() {
    // 1) 在一块原始缓冲上手工制造一个“不对齐”的 S 指针
    //    这里我们按 1 字节对齐拿到原始内存，然后故意偏移 1 字节
    constexpr std::size_t N = alignof(S);
    std::cout << "alignof(S) = " << N << "\n";

    // 分配比对齐需求更大的原始字节缓冲
    std::size_t buf_size = sizeof(S) + N; // 足够容纳一个对齐后的 S
    char* raw = new char[buf_size];

    // 故意制造一个“肯定不按 N 对齐”的地址：原始地址 + 1
    S* misaligned = reinterpret_cast<S*>(raw + 1);
    bool ok0 = is_aligned<N, S>(misaligned);
    std::cout << "misaligned ptr aligned? " << ok0 << " (expect 0)\n";

    // 2) 使用 do_align 计算在 raw 内部的下一个 N 字节对齐地址
    std::uintptr_t base = reinterpret_cast<std::uintptr_t>(raw);
    std::uintptr_t aligned_addr = do_align<N>(base);
    S* aligned = reinterpret_cast<S*>(aligned_addr);
    bool ok1 = is_aligned<N, S>(aligned);
    std::cout << "aligned ptr aligned?   " << ok1 << " (expect 1)\n";

    // 简单使用一下，防止被优化掉
    aligned->x = 3.14;
    std::cout << "aligned->x = " << aligned->x << "\n";

    delete[] raw;
}

int main() {
  Test1();
  Test2();
  Test3();
  return 0;
}
