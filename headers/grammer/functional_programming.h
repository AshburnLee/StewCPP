#ifndef GRAMMER_FUNCTIONAL_PROGRAMMING_HEADER
#define GRAMMER_FUNCTIONAL_PROGRAMMING_HEADER
#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

namespace grammer {
namespace functional {

/*
代码体现的函数式编程特性：

    纯函数 (Pure Functions): lambda 表达式 [](int x) { return x * x; } 是一个纯函数，它只依赖于输入参数，没有副作用（不修改外部状态）。 [](int x) { return x % 2 == 0; }也是一个纯函数。

    高阶函数 (Higher-Order Functions): std::transform, std::for_each, std::find_if, std::accumulate, std::copy_if 都是高阶函数，它们接受函数作为参数（在本例中是 lambda 表达式）。

    不可变性 (Immutability): 虽然 numbers 向量被修改了，但函数式编程的思想是尽量避免修改原有数据，而是创建新的数据结构（例如 squaredNumbers, evenSquaredNumbers）。

    声明式编程 (Declarative Programming): 代码描述了 什么 要做（例如，将每个数字平方，查找大于 50 的数字），而不是 如何 做（没有显式的循环语句）。
    STL 和现代 C++ 特性为在 C++ 中进行声明式编程提供了强大的支持
*/

int functional_programming() {
  // 创建一个整数向量
  std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  // 使用 lambda 表达式和 std::transform 将每个数字平方
  std::vector<int> squaredNumbers;
  std::transform(numbers.begin(), numbers.end(), std::back_inserter(squaredNumbers),
                 [](int x) { return x * x; });

  // 使用 lambda 表达式和 std::for_each 打印平方后的数字
  std::cout << "Squared numbers: ";
  std::for_each(squaredNumbers.begin(), squaredNumbers.end(),
                [](int x) { std::cout << x << " "; });
  std::cout << std::endl;


  // 使用 lambda 表达式和 std::find_if 查找第一个大于 50 的平方数
  auto it = std::find_if(squaredNumbers.begin(), squaredNumbers.end(),
                         [](int x) { return x > 50; });

  if (it != squaredNumbers.end()) {
    std::cout << "First number greater than 50: " << *it << std::endl;
  } else {
    std::cout << "No number greater than 50 found." << std::endl;
  }

  // 使用 std::accumulate 计算所有平方数的和 (reduce 操作)
  int sumOfSquares = std::accumulate(squaredNumbers.begin(), squaredNumbers.end(), 0);
  std::cout << "Sum of squared numbers: " << sumOfSquares << std::endl;


  // 使用 std::filter 过滤出偶数的平方数 (filter 操作)
  std::vector<int> evenSquaredNumbers;
  std::copy_if(squaredNumbers.begin(), squaredNumbers.end(), std::back_inserter(evenSquaredNumbers),
               [](int x) { return x % 2 == 0; });

  std::cout << "Even squared numbers: ";
  std::for_each(evenSquaredNumbers.begin(), evenSquaredNumbers.end(),
                [](int x) { std::cout << x << " "; });
  std::cout << std::endl;

  return 0;
}

} // namespace functional
} // namespace grammer

#endif // GRAMMER_FUNCTIONAL_PROGRAMMING_HEADER
