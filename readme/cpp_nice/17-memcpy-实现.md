

理解这个 my_memcpy_improved 【done，见 self_memcpy.h】 与 word 对齐有关

===

## 有使用过 memcpy 函数吗？如何自己实现一个memcpy函数？重写 memcpy 需要注意哪些问题？

直接逐字节(一个 char 占一个字节)复制数据，简化板：

~~~cpp
#include <iostream>
void* my_memcpy(void* dest, const void* src, size_t n) {
    if (dest == nullptr || src == nullptr) {
        return nullptr; // or throw an exception
    }
    
    char* dest_char = static_cast<char*>(dest);   // 
    const char* src_char = static_cast<const char*>(src);  // 

    for (size_t i = 0; i < n; ++i) {
        dest_char[i] = src_char[i]; 
    }

    return dest;
}

int main() {
    char src[] = "Hello, world!";
    char dest[14];

    my_memcpy(dest, src, sizeof(src));
    std::cout << "Copied string: " << dest << std::endl;
    return 0;
}
~~~

解释几点：

1. `void*` 指针的限制: `void*` 指针是一种通用指针类型，它可以指向任何类型的对象，但是不能直接对其进行解引用或进行算术运算。 你不能直接使用 `*dest` 来访问 `dest` 指向的内存内容，因为编译器不知道 `dest` 指向的是什么类型的数据。需要cast到其他类型。

2. `char*` 指针的灵活性: `char*` 指针可以**指向单个字节**，并且允许进行指针算术运算。 通过将 `void*` 转换为 `char*`，我们可以逐字节访问和操作内存。 这对于 `memcpy` 函数来说非常重要，因为它需要逐字节复制数据。选择 `char*` 是因为 `char` 类型表示1字节，这与 `memcpy` 函数逐字节复制数据的操作相匹配。


## memcpy 改进版本  [理解了]

改进后的 memcpy 函数将复制过程分为三个部分，是为了优化性能，特别是针对不同内存对齐情况下的效率。这是因为现代 CPU 访问内存时，对齐的内存访问速度远高于未对齐的访问。 未对齐的访问可能会导致多个内存访问操作，严重降低效率。

优化版本主体有 3 部分：

1. 处理前缀未对齐部分:

    许多 CPU 要求某些数据类型（例如 int、long、double 等）必须位于特定地址边界上（例如 4 字节对齐、8 字节对齐）。如果目标地址 dest 不是对齐的，直接使用 long 类型进行复制会导致访问未对齐的内存，从而降低效率。

    因此，第一步先处理 dest 地址的前缀部分，即**未对齐的字节。这部分逐字节复制**，确保后续的 long 类型复制能够从对齐的地址开始。 这部分代码确保了后续的批量复制能够高效进行。

2. 处理对齐部分:

    处理完前缀未对齐部分后，dest 地址已经对齐。 这部分代码使用 long 类型（或其他更大的数据类型，取决于 CPU 架构和编译器优化）进行**批量复制。 一次复制多个字节，显著提高了复制效率**。 这是因为 CPU 可以更有效地处理对齐的批量内存访问。

3. 处理后缀未对齐部分:

    最后，可能还有一些剩余的字节需要复制，这些字节的数量不足以构成一个完整的 long 类型。 这部分代码**再次逐字节复制**，处理剩余的未对齐部分。 这确保了所有数据都被正确复制。

~~~cpp
#include <iostream>
#include <cstring> // for memcpy (for comparison)

// dest 必须事先分配好，且长度足够，这个函数不会分配内存
void* my_memcpy_improved(void* dest, const void* src, size_t n) {
    char* dest_char = static_cast<char*>(dest);
    const char* src_char = static_cast<const char*>(src);

    // dest 的首地址不是字的整数倍（未对齐），则需要逐字节复制：
    size_t prefix_len = (size_t)dest_char % sizeof(long);
    if (prefix_len != 0 && n >= prefix_len) {
        prefix_len = sizeof(long) - prefix_len;
        // 只逐字节复制prefix_len个字节
        for (size_t i = 0; i < prefix_len; ++i) {
            dest_char[i] = src_char[i];
        }
        dest_char += prefix_len;
        src_char += prefix_len;
        n -= prefix_len;
    }

    // 处理对齐部分 (假设 long 是最优复制单位)
    // 逐字节复制 prefix_len 个字节之后，剩下的对齐部分一定是位于特定地址边界上 ***
    size_t long_count = n / sizeof(long);
    if (long_count > 0) {
        long* dest_long = reinterpret_cast<long*>(dest_char);
        const long* src_long = reinterpret_cast<const long*>(src_char);
        for (size_t i = 0; i < long_count; ++i) {
            dest_long[i] = src_long[i];
        }
        dest_char += long_count * sizeof(long);
        src_char += long_count * sizeof(long);
        n -= long_count * sizeof(long);
    }

    // 处理后缀未对齐部分
    for (size_t i = 0; i < n; ++i) {
        dest_char[i] = src_char[i];
    }

    return dest;
}
int main() {
    char src[] = "Hello, world!";
    char dest[14];  // char dest[14]; 在栈上分配了 100 字节的内存空间。但是，编译器通常会尽量对齐数据，但不能保证 dest 的起始地址一定是字对齐的。
    
    my_memcpy_improved(dest, src, sizeof(src));
    std::cout << "My memcpy: " << dest << std::endl;
    
    std::memcpy(dest, src, sizeof(src)); // 使用标准库的 memcpy 进行比较
    std::cout << "Standard memcpy: " << dest << std::endl;
    return 0;
}
~~~

main 中 `char dest[14];` 在栈上分配了 100 字节的内存空间。但是，编译器通常会尽量对齐数据，但不能保证 dest 的起始地址一定是字对齐的。


## 语法补充
### sizeof() 运算符

~~~cpp
char b[] = "Hello, world!";  // 字符数组 编译器会自动在字符串末尾添加 '\0'
std::string a = "Hello, world!"; 
~~~

`sizeof(a)` 和 `sizeof(b)` 结果分别是多少？

答：前者 是13 + 终止符'\0' 所以是 14 bytes；后者根据编译器而不同，我的平台结果是 32 bytes。

### char b[] = "Hello, world!"; 和 std::string a = "Hello, world!"; 两者的不同

从内存分配上看不同，string 类是字符数组的一个封装。

