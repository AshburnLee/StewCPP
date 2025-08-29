#include <stdio.h>

int main() {

    // 在GCC中，可以使用__asm__关键字来嵌入汇编代码，并使用__builtin_ia32_disassemble函数来获取反汇编代码。
    // 例如，以下代码使用__asm__关键字嵌入了一段汇编代码，将eax寄存器的值加1
    int a = 0;
    __asm__ (
        "movl %1, %%eax\n\t" // 将变量a的值移动到eax寄存器中
        "addl $1, %%eax\n\t" // 将eax寄存器的值加1
        "movl %%eax, %0\n\t" // 将eax寄存器的值移动到变量a中
        : "=r"(a) // 输出操作数，表示将eax寄存器的值移动到变量a中
        : "r"(a) // 输入操作数，表示将变量a的值移动到eax寄存器中
        : "%eax" // 保留寄存器，表示eax寄存器被修改
    );
    // 这段代码使用了GCC的内联汇编语法，
    // 使用了三个汇编指令，分别是movl、addl和movl。
    // 其中，movl指令用于将数据从内存或寄存器移动到寄存器或内存中，
    // addl指令用于将两个操作数相加，并将结果存储到第一个操作数中，
    // movl指令用于将数据从寄存器或内存移动到内存或寄存器中。
    // 在这里，我们使用了三个操作数，分别是%0、%1和%eax。
    // %0表示输出操作数，表示将eax寄存器的值移动到变量a中，%1表示输入操作数，表示将变量a的值移动到eax寄存器中，%eax表示保留寄存器，表示eax寄存器被修改。
    printf("a = %d\n", a);

    char buffer[256];
    // int length = __builtin_ia32_divss(buffer, sizeof(buffer), (void*)main);
    printf("Disassembly of main():\n%s\n", buffer);


    return 0;
}