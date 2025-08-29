#ifndef GRAMMER_ENUM_CLASS_HEADER
#define GRAMMER_ENUM_CLASS_HEADER
#pragma once


#include <iostream>

namespace grammer {
namespace enum_class {
enum class Color : unsigned char {
  Red,    // 默认值为0
  Green,  // 默认值为1
  Blue,   // 默认值为2
  Yellow = 250 // 可以指定特定值
};

int main() {
  // 使用作用域解析运算符访问枚举成员
  Color c1 = Color::Red;
  Color c2 = Color::Green;

  // 必须进行显式类型转换才能进行比较
  if (static_cast<int>(c1) < static_cast<int>(c2)) {
    std::cout << "Red is less than Green" << std::endl;
  }

  // 输出枚举成员的值 (需要显式转换)
  std::cout << "c1 = " << static_cast<int>(c1) << std::endl; // 输出 0
  std::cout << "c2 = " << static_cast<int>(c2) << std::endl; // 输出 1
  std::cout << "Yellow = " << static_cast<int>(Color::Yellow) << std::endl; // 输出 250

  return 0;
}

} // namespace enum_class
} // namespace grammer
#endif // GRAMMER_ENUM_CLASS_HEADER
