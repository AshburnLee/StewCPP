
## lambda  [常用于高阶函数的参数]

语法形式为：`[capture list] (parameter list) -> return type { function body }`, 是个匿名函数，它可以在需要函数对象的地方使用。lambda 表达式中的 `capture list` 用于捕获外部变量，可以指定**按值捕获**或**按引用捕获**

labmda中 `capture list` 和 `parameter list` 的区别:

- `parameter list` 用于指定函数对象的参数列表，可以为空。参数是调用 Lambda 函数时传入的参数。
- `capture list` 用于捕获外部变量，可以指定按值捕获或按引用捕获。

~~~cpp
#include <iostream>
#include <functional>

int main() {
    int x = 1;
    int y = 2;

    // 按值捕获 x，按引用捕获 y，并指定参数列表
    auto add = [x, &y](int a, int b) -> int {
        return x + y + a + b;
    };

    // 真实的y值
    y = 3;

    // 调用lambda
    int result = add(1, 2); // 1+3+1+2 = 7
    std::cout << "x + y + 1 + 2 = " << result << std::endl;

    return 0;
}
~~~

- `[a, b]() {}`  Capture by value
- `[&a, &b]() {}`  Capture by reference
- `[=]() {}`  Capture all by value
- `[&]() {}`  Capture all by reference
- `[=, &c]() {}`  Mixed capture
- `[this]() {}`  Capture this pointer

## 声明式编程中的 lambda

`std::sort()` 默认的行为是升序排列，即其中的lambda是 `std::less()`，它是一个 `functor`，重载了 `operator()`.

  如果 `std::less` 返回 true，`std::sort` 解释为 a 应该排在 b 之前。
  如果` std::less` 返回 false，`std::sort` 解释为 a 不应该排在 b 之前。并且执行交换操作。

所以一个函数中的lambda的行为是什么？或者函数会如何使用lambda对象？需要理解具体的函数

## std::priority_queue  [你应该学习每一个这样的对象如何使用谓词]

`std::priority_queue` 是一个**容器适配器**，它提供了一种**基于优先级的队列**。这意味着队列中的元素不是按照它们被插入的顺序排列的，而是按照一定的优先级顺序排列的。默认情况下，`std::priority_queue` 使用 **std::less** 来比较元素，**使得较大的元素位于队列的顶部**，默认最大堆。谓词返回一个 bool 值。这个 bool 值表示第一个参数是否**小于**第二个参数（按照你定义的优先级规则）

`std::priority_queue` 的行为： 当 `std::priority_queue` 使用你提供的谓词比较两个元素 a 和 b 时，**如果 predicate(a, b) 返回 true，std::priority_queue 会认为 a 的优先级低于 b。即，std::priority_queue 会认为 b （后边这个）更靠近堆顶。** ***

即 谓词返回 true，第二个参数更接近堆顶！

总结：

~~~js
less 谓词：a < b, b (较大的) 更接近堆顶, 故这是最大堆！ CHECK
greater 谓词：a > b, b (较小的) 更接近堆顶，故这是最小堆！  CHECK
~~~

## 注意

~~~cpp
auto AgeLess = [](Person& a, Person& b){ return a.GetAge() < b.GetAge();};
...
priority_queue<Person, vector<Person>, decltype(AgeLess)> root_max(AgeLess);
~~~

1. 对于 priority_queue 第三个模板参数应该**明确类型**，class，struct都可以，如果是 lambda，需要明确类型，通过 `decltype` 获取类型。
2. 虽然你使用了 `decltype(AgeLess)` 来获取 lambda 表达式的类型，但是你没有提供 lambda 表达式的实例给 `priority_queue` 的构造函数。

    模板参数类型： `decltype(AgeLess)` 确实可以获取 lambda 表达式的类型，但它只是一个类型，而不是一个对象。
    构造函数需要实例： `std::priority_queue` 的构造函数需要一个比较器对象的实例，以便在比较元素时使用。


## decltype() 

不是运算符，而是一个类型说明符 。它用于推导表达式的类型。以下是 decltype 的一些关键特性：

  - 类型推导： `decltype(expression)` 会返回 expression 的类型 
  - 编译时确定： `decltype` 在编译时确定类型，而不是在运行时
  - 不执行表达式： `decltype` 不会执行 expression，仅仅是推导其类型
  - C++11 引入： `decltype` 是在 C++11 标准中引入的

