#include <iostream>

int graph = 0;

namespace level_1 {
int graph = 1;
namespace level_2 {
int graph = 2;
namespace level_3 {
int graph = 3;

}
}
}

int main() {
    int graph = 4;
    // ::开头的变量表示是全局的，而不是当前作用域中的其他同名变量
    ::graph = 99;
    std::cout << "::graph(global) " << ::graph << std::endl;
    std::cout << "level_1::graph " << level_1::graph << std::endl;
    std::cout << "level_1::level_2::graph " << level_1::level_2::graph << std::endl;
    std::cout << "level_1::level_2::level_3::graph " << level_1::level_2::level_3::graph << std::endl;
    // graph是main函数中的局部变量
    std::cout << "graph " << graph << std::endl;
    return 0;
}
