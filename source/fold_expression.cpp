
#include <iostream>

template<typename... Args>
void print(Args... args) {
    std::cout << "Number of arguments: " << sizeof...(args) << std::endl;
    std::cout << "Values: ";
    // (std::cout << ... << args) << std::endl;
    ((std::cout << args << ", "), ...) << std::endl;
}

template<typename... Args>
auto sum(Args... args) {
    return (args + ...);
}

template<typename... Args>
bool all_true(Args... args) {
    return (... && args);
}

template<typename... Args>
auto subtract_right(Args... args) {
    return (args - ...);  // (args1 - (args2 - args3))
}

template<typename... Args>
auto subtract_left(Args... args) {
    return (... - args);  // ((args1 - args2) - args3)
}

int main() {
    std::cout << sum(1, 2, 3, 4, 5) << std::endl; // 输出：15
    std::cout << std::boolalpha << all_true(true, true, false) << std::endl; // 输出：false

    int i = 1;
    double d = 3.14;
    std::string s = "hello";
    print(i, d, s); // 输出：Number of arguments: 3 Values: 1 3.14 hello
    print(1, 2, 3, 4, 5); // 输出：Number of arguments: 5 Values: 1 2 3 4 5

    std::cout << "Right fold: " << subtract_right(10, 3, 2) << std::endl; // 输出：9 (10 - (3 - 2))
    std::cout << "Left fold: " << subtract_left(10, 3, 2) << std::endl;   // 输出：5 ((10 - 3) - 2)
    return 0;
}
