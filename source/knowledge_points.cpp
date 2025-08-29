
#include <iostream>

namespace utils {

void print_binary(unsigned int num) {
    // 从最高位开始逐位打印二进制表示
    for (int i = sizeof(num) * 8 - 1; i >= 0; i--) {
        // 使用位运算检查当前位是否为1
        unsigned int mask = 1 << i;
        std::cout << ((num & mask) ? "1" : "0");
    }
    std::cout << std::endl;
}

} // utils

static constexpr unsigned mask = 1u << (sizeof(unsigned) * 8 - 1);

// main 不能放进如何namespace
int main() {
    std::cout << mask << std::endl;
    ::utils::print_binary(mask);
    return 0;
}   