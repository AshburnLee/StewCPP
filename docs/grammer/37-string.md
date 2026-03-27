## std::string 类型的 < 运算符已经重载，用于执行字典序比较

`std::sort(words.begin(), words.end(), [](const std::string& a, const std::string& b) { return a < b; });` 这样写就可以实现字典序排列。以验证 CHECK

排序后：ape apple application banana


## 对于一个字符串，分别使用 sizeof 与 strlen，得到的结果有什么区别

`sizeof` 运算符

- 作用: `sizeof` 运算符是一个**编译时运算符**，它不考虑运行时值，它返回一个对象或类型在内存中占用的字节数。对于字符数组（C 风格字符串），`sizeof` 返回整个数组的字节数，包括字符串的结束符 \0。
- 使用方法: `sizeof(string_variable)` 或 `sizeof string_variable`
- 结果: 与字符串内容无关，只取决于字符串数组的声明大小。

`strlen` 函数

- 作用: `strlen` 函数是一个**运行时函数**，它返回 C 风格字符串的长度（不包括结束符 \0）。它从字符串的起始地址开始计数，直到遇到 \0 结束符为止。
- 使用方法: `strlen(string_variable)`
- 结果: 取决于字符串中实际字符的数量。


~~~cpp
#include <cstring> // for strlen

int main() {
  char str1[] = "hello";  // 字符数组，包含结束符 '\0'
  char str2[20] = "world"; // 字符数组，包含结束符 '\0'，预留了更多空间
  const char* str3 = "test"; // 字符串字面量，存储在只读内存中

  std::cout << "sizeof(str1): " << sizeof(str1) << std::endl; // 输出 6 (5 个字符 + 1 个结束符)
  std::cout << "strlen(str1): " << strlen(str1) << std::endl; // 输出 5

  std::cout << "sizeof(str2): " << sizeof(str2) << std::endl; // 输出 20 (预分配的大小)
  std::cout << "strlen(str2): " << strlen(str2) << std::endl; // 输出 5

  std::cout << "sizeof(str3): " << sizeof(str3) << std::endl; // 输出 4 或 8 (取决于编译器和系统，指针大小)
  std::cout << "strlen(str3): " << strlen(str3) << std::endl; // 输出 4

  return 0;
}
~~~

sizeof(std::string):

~~~cpp
  std::string str4 = "lvliang";

  std::cout << "sizeof(str4): " << sizeof(str4) << std::endl; // std::string 对象的大小  32  
  std::cout << "str4.length(): " << str4.length() << std::endl; //  7 最佳实践
  std::cout << "str4.size(): " << str4.size() << std::endl;     //  7 最佳实践
~~~

`sizeof(str4)` 仍然返回 `std::string` 对象的大小，这与字符串的实际内容长度无关。
