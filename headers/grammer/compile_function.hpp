#ifndef COMPILE_FUNCTION_HEADER
#define COMPILE_FUNCTION_HEADER
#pragma once
#include <iostream>

namespace grammer {
namespace compile_function {
void Show();
void Show(int);

namespace cf {
void Show();
}

class CompileFunc {
public:
    void Show();
};

void CompileFunc::Show() {
    std::cout << "函数需要定义，不能只有声明，否则编译报错找不到符号\n";
}


} // namespace compile_function
} // namespace grammer

#endif // COMPILE_FUNCTION_HEADER