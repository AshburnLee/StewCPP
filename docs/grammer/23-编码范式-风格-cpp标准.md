
## 统一初始化 (uniform initialization) 

是 C++11 引入的另一种特性，它使用花括号 {} 来初始化变量，可以用于任何类型的变量，包括基本类型、类和数组。如：

~~~cpp
uint32_t const lda{is_A_transpose ? k : m};
uint32_t const ldb{is_B_transpose ? n : k};  // {} 中使用3元运算符 初始化
uint32_t const ldc{m};

float const alpha{1.0f};
float const beta{0.0f};

constexpr int WMMA_M{16};  // constexpr 用于在编译时将数字嵌入到代码中
constexpr int WMMA_N{16};
constexpr int WMMA_K{16};
constexpr int WARP_SIZE{32};

for (uint32_t ki{0}; ki < k; ki += WMMA_K)...  // 循环变量也可以通过 {} 初始化
~~~

## c++ 中的函数式编程

函数式编程（Functional Programming）是一种编程范式，它强调使用纯函数、不可变数据和高阶函数来构建程序。在 C++ 中，虽然它主要是一种面向对象的语言，但它也支持函数式编程的一些特性和概念。

C++ 中的函数式编程特性：

- 纯函数：纯函数是指在相同输入下总是产生相同输出，并且没有副作用的函数。纯函数使得代码更容易理解和测试。
- 不可变数据：不可变数据是指一旦创建就不能修改的数据。使用不可变数据可以避免许多并发和状态管理的问题。
- 高阶函数：高阶函数是指可以**接受函数作为参数或返回函数的函数**。C++ 中的标准库提供了许多高阶函数，如 std::transform、std::accumulate 等。Lambda 表达式：Lambda 表达式是匿名函数，可以在需要函数对象的地方使用。它们使得编写内联函数变得更加简洁。


## C++ 中的函数式编程有以下几个优势：

1. 易于理解和测试：函数式编程中的函数是纯函数，即给定相同的输入，总是会产生相同的输出，没有副作用。这使得函数更容易理解和测试。
2. 并行计算：由于函数式编程避免了状态和可变数据，因此它非常适合并行计算。在多核和多处理器的环境中，这是一个巨大的优势。
3. 代码简洁：函数式编程通常可以产生更简洁的代码。通过使用高阶函数，如 map、reduce 和 filter，可以用更少的代码实现相同的功能。
4. 强大的抽象能力：函数式编程提供了强大的抽象能力，可以帮助我们更好地解决复杂的问题。



## c++ 的编程范式 [范式]

1. **过程式编程**：这是最基础的编程范式，主要关注如何通过函数来操作数据。这种范式适用于简单的、线性的编程任务。
2. **面向对象编程**：这种范式通过类和对象来组织代码，强调数据和操作数据的方法的封装。这种范式适用于复杂的、需要大量代码复用和模块化的编程任务。
3. **泛型编程**：这种范式允许编写与数据类型无关的代码。**通过模板机制**，可以定义可以处理多种数据类型的函数和类。这提高了代码的可重用性和效率。
4. **函数式编程**：这种范式把计算视为函数的计算，避免使用可变状态和副作用。C++ 虽然不是纯粹的函数式语言，但通过 lambda 表达式、标准库中的算法函数等，可以支持函数式编程风格的代码编写。

C++ 的强大之处就在于它支持多种编程范式的混合使用。 ***


## 声明式编程 Declarative Programming  [编程风格]

在 C++ 中，声明式编程是一种**强调描述结果**而**不是过程**的编程风格，它可以现与函数式编程相结合，但两者并非完全等同。 STL 和代 C++ 特性为在 C++ 中进行声明式编程提供了强大的支持。

C++ 支持一些声明式编程的特性，主要通过以下方式实现：

- 标准模板库 (STL) 算法: STL 提供了许多高阶算法函数，例如 std::sort, std::find, std::transform, std::accumulate 等。这些算法函数允许你声明性地描述你想要对数据进行的操作，而无需显式地编写循环或迭代器。 你只需要指定要操作的数据和操作本身，STL 算法会负责如何高效地执行这些操作。
- Lambda 表达式: Lambda 表达式允许你定义匿名函数，这使得你可以将函数作为参数传递给 STL 算法，从而进一步增强声明式编程的能力。
- 范围 for 循环: 范围 for 循环提供了一种更简洁的方式来迭代容器中的元素，这比传统的迭代器方式更具声明性。
- 一些现代 C++ 特性: 例如 std::views (C++20) 提供了对数据进行转换和过滤的声明式方式，而无需创建中间容器。


## Designated initializers，指定初始化器是 C++20 的特性

~~~cpp
const my_graph_compiler_version *my_graph_compiler_get_version(void) {
  static const my_graph_compiler_version ver = {
      .api_version = {MY_GC_API_V_MAJOR, MY_GC_API_V_MINOR,
                      MY_GC_API_V_PATCH,
                      MY_GC_API_V_HASH}, // version defined by oneDNN
      .gc_version = {
          GC_VERSION_MAJOR, GC_VERSION_MINOR, GC_VERSION_PATCH,
          GC_VERSION_HASH}}; // version defined by graph compiler itself
  return &ver;
}
~~~

在C++中，`.gc_version` 这种语法是使用了指定初始化器（designated initializers）的特性，这是C99标准中的一个特性，后来在C++20标准中也被引入了。指定初始化器**允许你在初始化结构体或数组时明确指定要初始化的成员或元素，而不是依赖于它们在结构体或数组中的顺序**。


## 这是什么样的继承？ [CRTP-设计模式]

~~~cpp
class my_type : public std::enable_shared_from_this<my_type> {}
~~~

CRTP（Curiously Recurring Template Pattern，奇特递归模板模式）是一种继承模式，其中一个类继承自一个以自身为模板参数的模板类。 这意味着派生类成为其基类的模板参数。这是 C++ 中的 **CRTP**（Curiously Recurring Template Pattern）一种设计模式. 它通过模板类继承自己的派生类，从而使得派生类能够在基类中使用其自身的类型。例子：

~~~cpp
#include <iostream>
#include <memory>

class my_type : public std::enable_shared_from_this<my_type> {
public:
    std::shared_ptr<my_type> getShared() {
        // shared_from_this() 是属于 std::enable_shared_from_this 的函数，不是my_type 自己定义的
        return shared_from_this(); // 通过 shared_from_this() 返回一个 shared_ptr
    }
    void doSomething() {
        std::cout << "Doing something within my_type!" << std::endl;
    }
};

int main() {
    std::shared_ptr<my_type> ptr = std::make_shared<my_type>();
    std::shared_ptr<my_type> ptr2 = ptr->getShared();

    ptr2->doSomething(); // 在获取的 shared_ptr 上调用成员函数

    return 0;
}
~~~

这种模式允许对象自己生成共享指针，而不是依赖外部代码创建新的 `shared_ptr`。

CRTP 应用场景：
- 代码复用： CRTP 允许在基类中实现公共功能，并由派生类提供具体的实现。这避免了代码重复，提高了代码的可维护性。,
- 静态接口强制： 通过在基类中使用 static_assert 或 C++20 的概念，可以强制派生类实现特定的接口，从而在编译时检查接口的完整性。
- 混合（Mixin）： CRTP 可以用来实现混合模式，**将一些功能添加到现有的类中，而无需继承**。
- 避免虚函数的开销： 在性能要求非常高的场景下，CRTP 可以替代虚函数，**避免运行时虚函数调用的开销，从而提高程序的效率**。


## C++14 特性

C++14 允许 Lambda 表达式中的参数使用 auto 关键字，从而使 Lambda 表达式更加泛型。

~~~CPP
auto lambda = [](auto x, auto y) { return x + y; };
std::cout << lambda(1, 2) << std::endl;  // 输出 3
std::cout << lambda(1.5, 2.5) << std::endl;  // 输出 4.0
~~~

C++14 引入了 `std::make_unique`，用于创建 `std::unique_ptr` 对象。

~~~CPP
auto ptr = std::make_unique<int>(42);
~~~

二进制字面量：C++14 允许使用二进制字面量来表示二进制数。

~~~CPP
int binary = 0b1010;  // 等价于十进制的 10
~~~

数字分隔符：C++14 允许使用单引号作为数字分隔符，以提高可读性。

~~~CPP
int large_number = 1'000'000;  // 等价于 1000000
~~~

返回类型推导：C++14 允许函数的返回类型使用 `auto` 进行推导。

~~~CPP
auto add(int a, int b) {
    return a + b;
}
~~~

`constexpr` 的改进：C++14，允许在 `constexpr` 函数中使用更多的语法特性，如循环和条件语句。C++11 中只能有一个 `return` 语句，C++14 可以有多个。

~~~CPP
constexpr int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}
~~~


## 委托构造函数   [C++11，减少代码重复]

C++ 委托构造函数允许一个构造函数调用同一类中的另一个构造函数。这有助于减少代码冗余，**特别是当多个构造函数执行类似的初始化步骤时**。 委托构造函数使用 : 后跟另一个构造函数的调用来实现。

~~~cpp
class Rectangle {
public:
    int width;
    int height;
    int color;

    Rectangle(int width, int height) : width(width), height(height), color(0) {
        std::cout << "Width and height constructor called" << std::endl;
    }

    Rectangle(int width, int height, int color) : Rectangle(width, height) { // 委托构造函数
        this->color = color;
        std::cout << "Width, height, and color constructor called" << std::endl;
    }
};

int main() {
    Rectangle r1(5, 10);             // 调用宽度和高度构造函数
    Rectangle r2(5, 10, 255);       // 调用委托构造函数
    return 0;
}
~~~


## 基于范围的 for-loop  [C++11]

对于任何标准库中的容器，可以使用如下方式遍历：

~~~cpp
// c++11
vector<int> nums = {1,2,3};
for ( int x: nums) {...}

// c++17 结构化绑定
map<int, string> mp = {{1, "One"},{2, "Two"}};
for (auto [key, val] :mp) {...}
~~~

## c++ 标准是向前兼容的

C++14 是 C++11 的一个增量更新，旨在改进和扩展 C++11 的功能。因此，C++14 是向后兼容 C++11 的。


## 类内初始化  [C++,简化代码]

C++11 放宽了这些限制，允许对非静态成员进行类内初始化 。这意味着你可以在类声明中直接为非静态成员赋初始值，而无需在构造函数中显式初始化。

~~~cpp
class Person {
public:
    std::string name = "Unknown"; // 类内初始化
    int age = 0;                 // 类内初始化
    
    Person() = default; // 默认构造函数
    ...
}
~~~

## 私有成员就地初始化  [c++11特性]

~~~cpp
class MyClass {

private:
    std::string backend_ {};
    std::string name_ {};
    float priority_ {5.0f};
}
~~~


## std::all_of  [声明式编程]

逻辑很简单时 使用 `std::all_of` 而不是循环：
~~~cpp
    // valid stride: "acdb"
    const auto all_letters = [](const std::string &ss) -> bool {
        // bool status = true;
        // for (auto item : ss) {
        //     if (!std::isalpha(item)) {
        //         status = false;
        //         break;
        //     }
        // }
        // return status;
        // 改为：
        return std::all_of(ss.cbegin(), ss.cend(), [](int c){
            assert(c < UINT8_MAX);
            return std::isalpha(c);
        });
    };

// 使用 std::all_of 检查所有数字是否都大于 0
bool allPositive = std::all_of(numbers.begin(), numbers.end(), [](int n){ return n > 0; });  

// 使用 std::any_of 检查是否存在大于 3 的数字
bool anyGreaterThan3 = std::any_of(numbers.begin(), numbers.end(), [](int n){ return n > 3; });

// 使用 std::count_if 统计大于 2 的数字个数
int countGreaterThan2 = std::count_if(numbers.begin(), numbers.end(), [](int n){ return n > 2; });

~~~

`std::all_of` 的第三个参数是一个谓词 (predicate)，它是一个可调用对象，接受一个**迭代器指向的元素**作为参数。

`<algorithm>` 头文件中的这类函数是声明式编程，**它们关注的是“做什么”，而不是“怎么做”**。更多的类似声明式函数：

~~~
用于检查元素的函数:

    std::all_of: 检查所有元素是否都满足条件。
    std::any_of: 检查是否存在至少一个元素满足条件。
    std::none_of: 检查所有元素是否都不满足条件。

用于查找元素的函数:

    std::find: 查找第一个满足条件的元素。
    std::find_if: 查找第一个满足给定谓词的元素。
    std::find_if_not: 查找第一个不满足给定谓词的元素。
    std::search: 在一个范围内查找另一个范围。

用于计数元素的函数:

    std::count: 统计满足条件的元素个数。
    std::count_if: 统计满足给定谓词的元素个数。

用于修改元素的函数:

    std::for_each: 对每个元素应用一个函数。
    std::transform: 将一个范围内的元素转换到另一个范围。
    std::replace: 将特定值替换为另一个值。
    std::replace_if: 将满足给定谓词的元素替换为另一个值。

用于排序和排列的函数:

    std::sort: 对范围内的元素进行排序。
    std::stable_sort: 保持相等元素的相对顺序的排序。
    std::partial_sort: 对范围内的部分元素进行排序。
    std::nth_element: 找到第 n 个元素。
    std::random_shuffle: 对范围内的元素进行随机排列。

用于数值运算的函数:

    std::accumulate: 对范围内的元素进行累加。
    std::inner_product: 计算两个范围内的元素的内积。
    std::min_element: 查找范围内的最小元素。
    std::max_element: 查找范围内的最大元素。
    std::minmax_element: 查找范围内的最小和最大元素。
~~~

另一个实例，当元素是一个结构时：

~~~cpp
struct man {
    int id_;
    // 其他成员...
};
int main() {
    std::vector<man> men = {
        {10 /* id_ */, /* other members... */},
        {13 /* id_ */, /* other members... */},
        {18 /* id_ */, /* other members... */}
    };

    // 查找 id_ 值为 13 的 man 对象
    int target_id = 13;
    auto it = std::find_if(men.begin(), men.end(), [target_id](const man& m) {
        return m.id_ == target_id;
    });
    if (it != men.end()) {
        std::cout << "Found man with id 13." << std::endl;
        // 可以通过 *it 访问找到的 man 对象
    } else {
        std::cout << "Man with id 13 not found." << std::endl;
    }
    return 0;
}
~~~

例：

~~~cpp
// 创建用于存放交集结果的 vector
std::vector<Worker> res;

// 使用 std::copy_if 算法和 lambda 表达式找到交集
std::copy_if(vector1.begin(), vector1.end(), std::back_inserter(res),
            [&vector2](const Worker& w) {
                return std::find(vector2.begin(), vector2.end(), w.id) != vector2.end();
            });
~~~

