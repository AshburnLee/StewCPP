
#include <iostream>
#include <type_traits>

/// 原函数可以操作的数据包含 数值，类型，模板 3类
// 这里是数值
template <int a, int b>
struct Add_ {
    constexpr static int value = a + b;
};

template <int a, int b>
constexpr int Add = a + b;

// 以模板和类型作为输入
template <template <typename> class T1, typename T2>
struct Fun_ {
    using type = typename T1<T2>::type;
};

template <template <typename> class T1, typename T2>
using Fun = typename Fun_<T1, T2>::type;

/*
这段代码中的第一个模板参数 template <typename> class T1 是一个模板模板参数。
这意味着 T1 是一个模板，它接受一个类型参数。

在C++中，模板可以接受3中输入
1. 类型参数（例如 template <typename T>），
2. 值参数（例如 template <int N>），
3. 模板参数（例如 template <template <typename> class T>）。

在这个例子中，T1 是一个模板参数，它接受一个类型参数。

这样的设计允许我们将一个模板作为参数传递给另一个模板。例如，
我们可以将 std::vector 或 std::list（这些都是接受一个类型参数的模板）作为 T1 传递给 Fun_ 模板。

Fun_<std::vector, int>::type // 这将是 std::vector<int>
Fun_<std::list, double>::type // 这将是 std::list<double>

这种模板模板参数的使用方式提供了很大的灵活性，可以用于创建高度泛化的代码。 
*/

int main() {
    constexpr int x1 = Add_<2, 3>::value;
    constexpr int x2 = Add<2, 3>;
    std::cout << "Add_: " << x1 << ", Add: " << x2 << std::endl;

    Fun<std::remove_reference, int &> x3 = 3; // 这将是 std::remove_reference<int &>
    std::remove_reference<int &>::type x4 = 3;

    std::cout << "Fun_: " << x3 << "\n";
    return 0;
}