#ifndef SELF_MEMCPY_H
#define SELF_MEMCPY_H

/*
memcpy 逻辑上是如何做的？

*/
#include <iostream>
#include <cstddef>
#include <cstring>


class SelfMemcpy {
public:
    void* memcpy(void* dest, const void* src, size_t count);
    void* memcpy_aligned(void* dest, const void* src, size_t count);
};

void* SelfMemcpy::memcpy(void* dest, const void* src, size_t count) {
    if (dest == nullptr || src == nullptr) {
        return nullptr; // or throw an exception
    }
    
    char* dest_char = static_cast<char*>(dest);   // 
    const char* src_char = static_cast<const char*>(src);  // 

    for (size_t i = 0; i < count; ++i) {
        dest_char[i] = src_char[i]; 
    }

    return dest;
}

// 优化的 memcpy 函数（字对齐复制）
void* SelfMemcpy::memcpy_aligned(void* dest, const void* src, std::size_t count) {
    // 检查指针是否为空
    if (dest == nullptr && src == nullptr) {
        return dest;
    }

    // 转换指针类型以进行字节操作
    char* dest_ptr = static_cast<char*>(dest);
    const char* src_ptr = static_cast<const char*>(src);

    // 确定字大小（这里假设为 4 字节）
    const std::size_t word_size = 4;

    // 1. 处理非对齐的前缀
    // 同时检查 dest_ptr 和 src_ptr 的对齐情况是为了确保最佳性能和避免潜在的硬件问题。
    // 代码有局限性，当dest src首地址都字对齐或者都不对齐时，才有效。
    std::size_t prefix_bytes = 0;
    bool dest_aligned = (reinterpret_cast<std::uintptr_t>(dest_ptr) % word_size == 0);

    if (!dest_aligned) {
        // 计算 dest_ptr 和 src_ptr 对齐到下一个字边界所需的字节数
        std::size_t dest_align_bytes = dest_aligned ? 0 : word_size - (reinterpret_cast<std::uintptr_t>(dest_ptr) % word_size);

        // 选择较大的对齐字节数，以确保 dest_ptr 和 src_ptr 都对齐
        prefix_bytes = std::min(dest_align_bytes, count);

        for (std::size_t i = 0; i < prefix_bytes; ++i) {
            dest_ptr[i] = src_ptr[i];
        }
        dest_ptr += prefix_bytes;
        src_ptr += prefix_bytes;
        count -= prefix_bytes;
    }

    // 2. 字对齐复制
    std::size_t word_count = count / word_size;  // 当有余数时，这个余数大小就是 remaining_bytes
    std::uint32_t* dest_word_ptr = reinterpret_cast<std::uint32_t*>(dest_ptr);
    const std::uint32_t* src_word_ptr = reinterpret_cast<const std::uint32_t*>(src_ptr);

    for (std::size_t i = 0; i < word_count; ++i) {
        dest_word_ptr[i] = src_word_ptr[i];  // 每次复制一个字
    }

    // 3. 处理剩余的后缀
    std::size_t remaining_bytes = count % word_size;
    dest_ptr += word_count * word_size;
    src_ptr += word_count * word_size;

    for (std::size_t i = 0; i < remaining_bytes; ++i) {
        dest_ptr[i] = src_ptr[i];
    }

    return dest;
}

#endif  // SELF_MEMCPY_H
