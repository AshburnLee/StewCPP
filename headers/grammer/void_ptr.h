#ifndef GRAMMER_VOID_HEADER
#define GRAMMER_VOID_HEADER
#pragma once

#include <memory>
#include <stdio.h>
#include <iostream>

namespace grammer {
namespace void_ptr {
using namespace std;

// void* 指针的应用实例1

// 功能类似于标准库函数 memset，用于将一段内存区域清零。
// void* data void 指针可以指向任何数据类型，但不能直接对其进行解引用操作。
// int byte_size: 这是一个整数，表示要清零的内存块的大小。
void MemSet(void *data, size_t byte_size) {
    // char 类型在 C/C++ 中通常占用一个字节，因此使用 char 指针可以方便地逐字节操作内存。 
    // 强制类型转换 (char *) 是必要的，因为不能直接对 void 指针进行解引用。
    char *ptr = (char *)data;

    // 循环清零
    for (size_t i = 0; i < byte_size; ++i) {
        // 这行代码将 ptr 指向的内存单元的值设置为 0。 
        // 由于 ptr 是 char 指针，因此 0 将被解释为一个字符的 ASCII 码值 0，也就是空字符 '\0'。
        *ptr = 0;
        // 将 ptr 指针向后移动一个字节，指向下一个内存单元。
        ptr++;
    }
}

void TestMemSet() {
    int arr[5] = {1, 2, 3, 4, 5};
    MemSet(arr, sizeof(arr));
    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl; // 输出：0 0 0 0 0
}

// ==================================================================================================

// 泛型指针和泛型函数是 C++ 中的概念，用于实现通用的数据类型和算法。
// 泛型指针是指可以指向任意类型的指针，使用 void* 类型来实现。
// 在需要处理不同类型数据的情况下，可以使用泛型指针来实现通用的代码。

// void* 指针的应用实例 2: 
void PrintValue(void* ptr, char type) {
    switch(type) {
        case 'i': // integer
            std::cout << "Value: " << *(int*)ptr << std::endl;
            break;
        case 'd': // double
            std::cout << "Value: " << *(double*)ptr << std::endl;
            break;
        case 'c': // char
            std::cout << "Value: " << *(char*)ptr << std::endl;
            break;
        default:
            std::cout << "Invalid type" << std::endl;
    }
}
void TestTemplatesVoidPtr() {
    int i = 10;
    double d = 3.14;
    char c = 'a';

    PrintValue(&i, 'i'); // prints "Value: 10"
    PrintValue(&d, 'd'); // prints "Value: 3.14"
    PrintValue(&c, 'c'); // prints "Value: a"
}

// =========================================================================================================

// c++ 中 malloc 函数是如何实现的？实现自己的 malloc 函数

// malloc函数是C++中用于动态分配内存的函数。它的实现通常依赖于操作系统提供的底层内存分配函数，
// 如 brk 或 mmap。具体实现方式因操作系统而异，但通常都是通过向操作系统请求一定大小的内存块，
// 并返回该内存块的首地址来实现的。
// 下面是一个简单的自定义malloc函数的实现，它使用一个静态数组来模拟内存池，
// 每次分配内存时从数组中取出一段空闲内存并返回其首地址。注意，这个实现并不是线程安全的，
// 也没有实现内存的释放功能。

#define MAX_MEM_SIZE 1024 // 内存池大小
char mem_pool[MAX_MEM_SIZE]; // 内存池
size_t offset = 0; // 当前内存池中已分配的内存大小, 静态的
void* my_malloc(size_t size) {
    // 检查是否有足够的可用空间
    if (offset + size > MAX_MEM_SIZE) {
        return nullptr;
    }
    // 返回内存块的指针
    void* ptr = mem_pool + offset;
    // 更新已分配内存大小
    offset += size; 
    // 返回内存块首地址
    return ptr; 
}
// 自定义 free 函数 (简化版，仅重置 offset)
void my_free(void* ptr) {
    //  这个 free 函数非常简陋，它仅仅将 offset 重置到内存池的起始位置。
    //  它没有真正释放内存，也没有处理内存碎片。  在实际应用中，需要一个更复杂的实现。
    offset = 0; //  这会导致后续的 my_malloc 从头开始分配，覆盖之前的内存。
}

void  test_my_alloc() {
  int* a = static_cast<int*>(my_malloc(sizeof(int)));
  if (a != nullptr) {
    *a = 10;
    std::cout << "a: " << *a << std::endl;
    my_free(a); // 释放内存 (简化版)
  }

  double* b = static_cast<double*>(my_malloc(sizeof(double)));
  if (b != nullptr) {
    *b = 3.14;
    std::cout << "b: " << *b << std::endl;
  }
}

// =====================================================================================================



// 泛型指针实例：
// 这个实现只是一个简单的示例，实际上 malloc 函数的实现要比这个复杂得多，
// 需要考虑线程安全、内存对齐、内存池的管理等问题。
// 在C++中，可以使用 void* 类型的指针来实现泛型指针。
// void* 类型的指针可以指向任意类型的数据，但是在使用时需要进行类型转换。具体使用方法可以参考下面的示例代码：

void* my_malloc_wrapper(size_t size) {
    void* ptr = malloc(size); // 分配内存
    if (ptr == nullptr) { // 内存分配失败
        return nullptr;
    }
    return ptr; // 返回内存块首地址
}
// 使用后需要使用free() 释放内存
void TestMyAlloc() {
    int* int_ptr = (int*)my_malloc_wrapper(sizeof(int)); // 分配一个int类型的内存块
    *int_ptr = 10; // 对内存块进行赋值
    std::cout << *int_ptr << std::endl; // 输出内存块的值

    double* double_ptr = (double*)my_malloc_wrapper(sizeof(double)); // 分配一个double类型的内存块
    *double_ptr = 3.14; // 对内存块进行赋值
    std::cout << *double_ptr << std::endl; // 输出内存块的值

    char* char_ptr = (char*)my_malloc_wrapper(sizeof(char)); // 分配一个char类型的内存块
    *char_ptr = 'a'; // 对内存块进行赋值
    std::cout << *char_ptr << std::endl; // 输出内存块的值

    free(int_ptr); // 释放内存
    free(double_ptr);
    free(char_ptr);
}





} // namespace void_ptr
} // namespace grammer

#endif // GRAMMER_VOID_HEADER