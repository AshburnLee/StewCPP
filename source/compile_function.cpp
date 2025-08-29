#include "compile_function.hpp"

using grammer::compile_function::CompileFunc;

// 函数不能只有声明，否则
// undefined reference to 
namespace grammer::compile_function {
void Show() {
    std::cout << "no args\n";
}
void Show(int n) {
    std::cout << "with args: " << n << "\n";
}
}

// 函数不能只有声明，否则
// undefined reference to 
namespace grammer::compile_function::cf {
void Show() {
    std::cout << "in cf\n";
}
}

int main() {
    grammer::compile_function::Show();
    grammer::compile_function::Show(5);
    grammer::compile_function::cf::Show();
    CompileFunc obj;
    obj.Show();
    return 0;
}

/*
如果只有声明，没有定义，g++ 编译时返回：
/home/junhui/workspace/PrepareCPP/source/compile_function.cpp:9: undefined reference to `grammer::compile_function::Show()'
/usr/bin/ld: /home/junhui/workspace/PrepareCPP/source/compile_function.cpp:10: undefined reference to `grammer::compile_function::Show(int)'
/usr/bin/ld: /home/junhui/workspace/PrepareCPP/source/compile_function.cpp:11: undefined reference to `grammer::compile_function::cf::Show()'
/usr/bin/ld: /home/junhui/workspace/PrepareCPP/source/compile_function.cpp:13: undefined reference to `grammer::compile_function::CompileFunc::Show()'
*/
