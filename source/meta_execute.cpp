
#include <iostream>
#include <type_traits>

/// 1. 编译期的 循环代码
template <size_t INPUT>
constexpr size_t CountOne = (INPUT % 2) + CountOne<INPUT / 2>;

// 特化 模板为0时的值
template <>
constexpr size_t CountOne<0> = 0;


///2. 累加
template <size_t...INPUT> // 这是C++中的模板参数包（template parameter pack）的语法。
// size_t...INPUT表示一个可变数量的size_t类型的模板参数。
constexpr size_t Accumulate = 0;

template <size_t CURINPUT, size_t...INPUT>
constexpr size_t Accumulate<CURINPUT, INPUT...>
     = CURINPUT + Accumulate<INPUT...>;


int main() {
    constexpr size_t res = CountOne<45>;
    std::cout << res << std::endl;

    constexpr size_t res2 = Accumulate<1,2,3,4,5,6>;
    std::cout << res2 << std::endl;

    return 0;
}