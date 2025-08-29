0. 变量的声明和定义
1. extern int x
2. extern "C" {}


## 变量的定义 && 声明   [extern关键字]

变量的定义和声明是不同的概念。**定义会分配内存**，而声明只告诉编译器变量的类型和名称，但不分配内存。一个变量只能定义一次，但可以声明多次。

~~~cpp
/// header.h
extern int x; // 声明 x，但不定义

/// source.cpp
#include "header.h"

int x = 10; // 定义 x 并初始化为 10

int main() {
  extern int x; // 再次声明 x
  std::cout << x << std::endl; // 输出 x 的值
  return 0;
}
~~~

- `header.h` 文件包含 `extern int x`; 这行代码声明了变量 `x`，但没有定义它。**`extern` 关键字告诉编译器 x 的定义在其他地方**。
- `source.cpp` 文件包含 `int x = 10`; 这行代码定义了变量 x 并将其初始化为 10。这行代码也**隐式地声明了 x**。
- `main` 函数中再**次声明 x**，这允许 `main` 函数使用 x。


## 报错：一个 map 是 multiple definition 的

这意味着你在多个编译单元（通常是 .cpp 文件）中定义了同一个 std::map 变量。 ***

extern 关键字可以用来解决这个问题，通过在一个地方定义变量，然后在其他地方声明它。示例：

1. 在头文件中声明 `extern` 变量：

`extern` 关键字告**诉编译器** x 的定义在其他地方。 ***

~~~cpp
// my_map.h
#ifndef GLOBAL_MAP_H
#define GLOBAL_MAP_H

#include <map>

extern std::map<int, std::string> myMap;

#endif // GLOBAL_MAP_H
~~~

2. 在一个源文件中定义实际的变量：

~~~cpp
// my_map.cpp
#include "my_map.h"

// 定义 myMap
std::map<int, std::string> myMap = {  
    {"key1", 1},
    {"key2", 2},
    {"key3", 3}
}; // 定义并初始化
~~~

3. 在其他源文件中只包含（含有申明的）头文件即可：

~~~cpp
// other_file.cpp
#include "my_map.h"

// Now you can use myMap in this file
~~~

这样， `myMap` 只会在 `my_map.cpp` 中定义一次，而其他文件只是声明了它（通过 `my_map.h`），避免了多次定义导致的错误。 ***


## 实例二

~~~cpp
// file1.cpp
int globalVar = 10; // 定义, 编译器会为 globalVar 分配内存空间，并将其初始值设置为 10。

// file2.cpp
extern int globalVar; // 声明，extern 关键字告诉编译器，globalVar 的定义在其他地方（ file1.cpp）。编译器不会为 globalVar 分配新的内存空间，而是期望链接器在链接阶段找到 globalVar 的定义。
int main() {
  globalVar = 20; // 使用 globalVar
  return 0;
}
~~~

在这个例子中，file2.cpp 使用 `extern` 声明 `globalVar`。编译器不会为 `globalVar` 分配存储空间，而是依赖链接器在链接阶段找到 file1.cpp 中 `globalVar` 的定义。

`globalVar` 的声明周期从声明处到文件结尾。

- 通过 extern 声明，不同的编译单元 (.cpp文件) 可以访问和修改同一个.
- extern 依赖于链接器来解析符号


## extern "C"  [禁用编译器命名修饰]

被修饰的 code 禁用 `name mangling`。使用 `extern "C"` 修饰的代码不一定是用C语言编写的，它可能是用 C++ 编写的，但其**链接属性被显式设置为C语言风格**。 ***

1. 名称修饰（Name Mangling）

名称修饰是指编译器在生成目标代码时对函数和变量的名称进行修改，以包含更多的信息（如函数的参数类型、返回类型等）。这**是编译器为了支持函数重载 & 运算符重载(就是静态多态) 和 解决链接时的名称冲突而采用的一种技术**和其他 C++ 特性。例如，假设有以下两个函数：

~~~CPP
void foo(int);
void foo(double);
~~~

在 C++ 中，这两个函数会被编译器修饰成不同的符号名称，以便在链接时区分它们。可能的修饰名称如下（具体的修饰规则**依赖于编译器**）：
`_Z3fooi_asd_foo(int)` & `_Z3food_asd_foo(double)` , GCC编译器会在生成的符号名前添加特定的前缀（如_Z）

2. C 语言的符号名称

在 C 语言中，函数和变量的名称不会被修饰。C 编译器生成的符号名称就是函数或变量的名称本身。例如：

~~~C
void foo(int);
~~~

在 C 中，这个函数的符号名称就是 `foo`。

3. `extern "C"` 的作用

当你需要在 C++ 代码中调用 C 语言的函数，或者需要让 C 语言代码调用 C++ 函数时，名称修饰会导致链接错误。如果在C++ 中抵用C函数，如果没有这个声明，C 函数在 C++ 编译会被 Name Mangling，导致链接时找不到对应的符号。


为了避免这个问题，可以使用 `extern "C"` 来指示编译器按照 C 语言的方式处理被包裹的代码，从而生成一致的符号名称。

通过使用 `extern "C"`，你可以在 C++ 代码中无缝地调用 C 语言的函数，或者让 C 语言代码调用 C++ 函数，从而实现跨语言的互操作。

KAQ：我为什么会在 c++ 代码中调用 c 函数？答：

- 许多现有的库和代码都是用 C 语言编写的。通过在 C++ 代码中调用这些 C 函数，你可以重用这些库和代码；
- C 语言通常比 C++ 更接近底层硬件，因此在某些情况下，C 语言编写的代码可能具有更高的性能
- 某些嵌入式系统或硬件驱动程序可能是用 C 语言编写的，而应用程序逻辑是用 C++ 编写的
- 许多标准库和第三方库都是用 C 语言编写的。例如，数学库（如 math.h）、字符串处理库（如 string.h）

这些通常是使用C 编译器编译的，所以需要保证它的符号不被修饰。在链接时，可以被找到。

## 确实 C 没有命名修饰

C++ 标准库头文件（如 <cmath> 或 <math.h>）已经为你处理了 `extern "C"` 的问题。C++ 标准库头文件在内部已经包含了适当的 `extern "C"` 声明，以确保与 C 标准库的兼容性。但，如果你在自己的 C++ 代码中直接调用**自定义的 C 函数**或使用自定义的 C 头文件，你需要显式地使用 `extern "C"` 来避免名称修饰问题。

~~~cpp
// my_math.h
#ifndef MY_MATH_H
#define MY_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

double my_sqrt(double x);

#ifdef __cplusplus
}
#endif

#endif // MY_MATH_H
~~~

~~~c
// my_math.c
#include "my_math.h"
#include <math.h>

double my_sqrt(double x) {
    return sqrt(x);
}
~~~

~~~cpp
// main.cpp
#include <iostream>
#include "my_math.h"  // 包含自定义的 C 头文件

int main() {
    double x = 9.0;

    // 使用自定义的 C 函数 my_sqrt 计算平方根
    double result = my_sqrt(x);

    std::cout << "The square root of " << x << " is " << result << std::endl;

    return 0;
}
~~~

~~~sh
g++ -c my_math.c -o my_math.o
g++ -c main.cpp -o main.o
g++ my_math.o main.o -o app
./app
~~~

当 my_math.h 中有 `extern "C"` 时， `readelf -Ws my_math.o` 返回：

`3: 0000000000000000    43 FUNC    GLOBAL DEFAULT    1 _Z7my_sqrtd`

当 my_math.h 中没有 `extern "C"` 时， `readelf -Ws my_math.o` 返回：

`3: 0000000000000000    43 FUNC    GLOBAL DEFAULT    1 my_sqrt`



关键是 my_math.c 是已经通过 C 编译器编译过了的，其中的符号没有被修饰，这时 在 main.cpp 中调用 my_math.c 编译的函数，就需要用到 extern "C" 来告诉编译器，这个函数是用 C 语言写的。不要给他命名修饰，否则找不到 符号。***

