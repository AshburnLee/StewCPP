
1. enum 的功能是允许你**为整数值赋予文本名称**。 ***
2. enum class 更好用
3. enum 作为 map 的 key 需要 std::hash 特化


## 如何将一个 typedef enum {} 定义的对象作为一个 std::map 的key ?

`typedef` 可以去掉，因为它只是为这个 `enum` 对象起了个别名。

~~~cpp
typedef enum {
    aa = 0;
    bb = 1;
    cc = 3;
} MyEnum;

void func(MyEnum &xx) {
    switch (xx) {
        case aa:
            std::cout<< aa;
            break;
        case aa:
            std::cout<< aa;
            break;
        case aa:
            std::cout<< aa;
            break;
        default: assert(!"type is not found");
    }
}
std::map<MyEnum, std::string> colorMap;
~~~

- xx 本质上是啥？

答：xx 本质上是一个 MyEnum 类型的引用，它的底层类型可能是 int，但这取决于**编译器**的选择。**xx 和 aa、bb、cc 的关系是，xx 可以持有这些枚举值中的任何一个**，也就是说**一个enum类型只能持有其中的一个成员**

如果你遇到了类似 "error: implicit instantiation of undefined template 'std::hash<MyEnum>'" 的错误，那么这表明编译器无法找到用于类型 `MyEnum` 的 `std::hash` 特化定义。

在 C++ 标准库中，`unordered_map` `unordered_set` 内部使用哈希函数来快速查找键。 它通过计算键的哈希值来确定键在哈希表中的位置。对于内置类型（例如 `int`, `double`, `string`），`std::hash` 已经提供了特化版本。 但是，对于自定义类型，`std::hash` 没有默认的实现。

因此，你需要提供一个适当的 `std::hash` 特化定义来支持将 `MyEnum` 用作 `std::map` 的键。所以需要加上这个：

~~~cpp
// std::hash 特化定义
namespace std {
    template <>  // T特化为 MyEnum 类型
    struct hash<MyEnum> {
        std::size_t operator()(const MyEnum& value) const {
            return std::hash<int>()(static_cast<int>(value));
        }
    };
}
~~~

1. 我添加了一个 `std::hash` 的特化定义，以支持将 `MyEnum` 类型用作 `std::map` 的键
2. 将这个特化定义放在使用 `std::map` 的代码之前，以确保编译器能够找到特化定义
3. 什么情况下选用这个特化？报错如下时 `error: implicit instantiation of undefined template 'std::hash<MyEnum>'`


## enum 使用

~~~cpp
enum mode_t { min = 0, avg = 1, max = 2, sum = 3, n_modes }; // n_modes 没啥实际用处，表示了以一共有4个modes

if (has_bench_mode_bit(mode_bit_t::perf)) {
    const auto &t = res.timer_map.perf_timer();
    for (int mode = 0; mode < (int)bt::n_modes; ++mode)
        bs.ms[perf_timer][mode] += t.ms((bt::mode_t)mode);
}
~~~

KAQ: 如何访问 enum 中的成员？答：通过`::`， 如上

## enum class 作用域枚举，是强类型  [C++11]

是 C++11 引入的一种改进的枚举类型。它解决了传统 enum 类型的一些缺点，使其更安全、更易于使用。***

传统 `enum` 的缺点：

- 命名空间污染: 传统 enum 的枚举成员会直接进入当前作用域，可能与其他变量或枚举成员发生命名冲突。
- 隐式类型转换: 传统 enum 的枚举成员可以隐式转换为整数，这可能会导致一些难以发现的错误。

## `enum class` 的优势：

- 强类型: enum class 的枚举成员具有强类型，不会隐式转换为整数。**需要显式转换**才能进行算术运算或比较。这增强了代码的类型安全性和可读性。
- 作用域限定: enum class 的枚举成员被限定在其自身的作用域内，**避免了命名空间污染**。访问枚举成员需要使用作用域解析运算符 `::`。
- 自定义底层类型: enum class 可以指定底层数据类型，例如 unsigned char, int, long long 等，以控制枚举成员的大小和范围。

例：

~~~cpp
enum class Color {
    RED,
    GREEN,
    BLUE
};
int main() {
    // 1. 使用作用域，避免命名冲突
    Color myColor = Color::GREEN;

    // 2. 强类型检查：不能隐式转换为整数
    // int colorValue = myColor; // 错误：不能将 Color 隐式转换为 int
    int colorValue = static_cast<int>(myColor); // 正确：显式转换
}
~~~

## 枚举的作用

- c++中 枚举的作用，给出例子解释使用枚举和不使用枚举的区别

枚举的作用是定义一些具有特定含义的常量（为整数值赋予文本名称），可以**提高代码的可读性**和可维护性。以下是使用枚举的例子：

~~~cpp
enum Weekday {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};
typedef enum {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday} Weekday;
Weekday today = Monday;
if (today == Sunday) {
    //do something
}

//不使用枚举时
const int Monday = 0;
const int Tuesday = 1;
const int Wednesday = 2;
const int Thursday = 3;
const int Friday = 4;
const int Saturday = 5;
const int Sunday = 6;
int today = Monday;
if (today == Sunday) {
    //do something
}
~~~

使用枚举可以避免定义大量的常量，提高代码的可读性和可维护性。


## `&` 的使用技巧

~~~cpp
enum dir_t {
    DIR_UNDEF = 0,  // 0
    FLAG_DAT = 1,    // 1
    FLAG_WEI = 2,    // 10
    FLAG_BIA = 4,    // 100
    FLAG_FWD = 32,   // 100000
    FLAG_BWD = 64,   // 1000000
    FLAG_INF = 128,  // 10000000
    FWD_I = FLAG_FWD + FLAG_DAT + FLAG_INF // 32 + 1 + 128 (10100001) 这一个 FWD_I 包含了 3 种不同的信息
}；

// 使用时
if FWD_I & 32: ... // 表达了 32 是否在 FWD_I 中
~~~

上述成员的值是特殊的: 每个值只有最高位是1，其他尾是0，这才能保证 `FWD_I = FLAG_FWD + FLAG_DAT + FLAG_INF` , FWD_I 正确地表达3种值。
