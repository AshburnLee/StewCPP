#include "memory_in_c.h"

// 变量的定义
int a = 2;
char b;
int c;

// memory alignment
int main() {

    // %p是一个格式化输出符号，用于输出指针的值
    // 在上面的代码中，(void*)&a、(void*)&b、(void*)&c分别表示
    // 变量a、b、c的地址，%p表示输出指针的值
    // 因此，上面的代码的作用是输出变量a、b、c的地址。
    printf("&a: %p\n&b: %p\n&c: %p\n", (void*)&a, (void*)&b, (void*)&c);
    return 0;
}
