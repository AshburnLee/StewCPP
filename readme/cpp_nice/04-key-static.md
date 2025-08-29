
## static  ***

有多种用法（编译器处理 static 的三种行为）：

### 1. 全局变量和函数（改变链接性）

这时它限制了这些变量或函数的作用域，使它们只在定义它们的源文件（编译单元）中可见。这有助于避免名称冲突，并提供了一种**封装**实现细节的方式。

修饰全局变量，标准库倾向于使用命名空间来组织全局符号，而不是依赖 static 来限制可见性。避免使用 static 修饰全局变量。难以维护，不符合模块化设计，不是好的实践

修饰函数，是标准库中很常见。（用于创建只能在特定文件中使用的辅助函数，避免命名冲突。*** 这提高了封装性和代码的可维护性。

实例：

~~~cpp
/// utility.h
namespace MyUtils {
  // 外部通过公共接口函数访问static函数
  int publicAddFunction(int a, int b); 
}

/// utility.cpp
#include "utility.h"

namespace MyUtils {
  // 声明一个静态函数，只在 utility.cpp 可见
  static int helperFunction(int a, int b) {
    return a + b;
  }

  int publicAddFunction(int a, int b) {
    return helperFunction(a, b); // 在公共接口函数内部调用静态函数
  }
}

/// main.cpp
#include "utility.h"
#include <iostream>

int main() {
  int result = MyUtils::publicAddFunction(5, 3); // 调用公共接口函数
  std::cout << result << std::endl; // 输出 8
  return 0;
}
~~~


### 2. 修饰类的静态成员(函数和变量)

~~~cpp
class MyClass {
public:
  MyClass() {
    count++;
  }
  static int get_count() {  // 只能访问 static 成员
    return count;
  }
private:
  static int count; // static 成员变量声明
};
~~~

静态成员属于类本身，而不是类的任何特定对象。静态成员变量在所有对象实例之间共享，而静态成员函数通过类调用而非类对象，因为没有 `this` 指针。


### 3. 一般函数内修饰变量

在函数内部，static 关键字可以用于声明局部静态变量。这些变量在第一次执行到它的声明时初始化，并在下一次相同调用之前保持它们的值，直到程序结束。具体讲，当你在函数内部声明一个局部变量时，这个变量通常是**自动存储期（automatic storage duration）**的，即，它的生命周期仅限于函数调用的范围内。**每次进入函数时，局部变量都会被创建，函数结束时被销毁**。但，如果你使用 static 关键字声明一个局部变量，这个变量的**生命周期会延长到整个程序的执行期间，即使它的作用域仍然局限于声明它的函数内部**。这意味着局部静态变量可以在连续的函数调用之间保持状态。 即： 在函数内部声明的静态局部变量只会被初始化一次。即使函数多次调用，静态局部变量的值也会在函数调用之间保持不变。

实例：
~~~cpp
#include <iostream>
void countFunctionCalls() {
    // 声明一个局部静态变量
    static int count = 0; // 只在第一次调用函数时初始化为0，
    count++; // 每次调用函数时增加计数
    std::cout << "Function has been called " << count << " times." << std::endl;
}

int main() {
    countFunctionCalls(); // 输出: Function has been called 1 times.
    countFunctionCalls(); // 输出: Function has been called 2 times.
    countFunctionCalls(); // 输出: Function has been called 3 times.
    return 0;
}
~~~



## 全局变量

最佳实践，避免使用全局变量。

如果必须使用全局变量：

1. 优先使用命名空间: 使用命名空间可以组织全局变量，避免命名冲突。

2. 谨慎使用 extern: extern 应该只在需要在**多个文件中共享同一个变量时**使用。 确保只有一个 .cpp 文件定义该变量，其他文件只使用 extern 声明。

3. 尽量使用 static: 如果全局变量不需要在多个文件中共享，则使用 static 修饰，限制其作用域，避免命名冲突和不必要的耦合。

