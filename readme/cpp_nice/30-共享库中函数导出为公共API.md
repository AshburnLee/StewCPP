
通过使用导出宏，你可以明确控制哪些函数被导出为公共API。有助于避免不必要的函数被暴露给外部模块。

===

## 将共享库中函数导出为公共 API 供其他模块使用，实例

~~~cpp
#if defined _WIN32 || defined CYGWIN
#define COMPILER_DLL_EXPORT __declspec(dllexport)
#else
#define COMPILER_DLL_EXPORT attribute((visibility("default")))
#endif
~~~

### 解释

上述代码是一个条件编译指令，用于根据不同的操作系统平台来定义宏 COMPILER_DLL_EXPORT。这个宏用于控制符号（通常是函数或变量）的导出属性，以便在创建动态链接库（DLL）时使用。

让我们逐步解释这段代码：

`#if defined _WIN32 || defined __CYGWIN__` 这是一个预处理器指令，用于检查是否定义了宏`_WIN32`或`__CYGWIN__`。`_WIN32`宏通常在Windows平台上由编译器定义，而`__CYGWIN__`宏则在使用`Cygwin`环境（一个在Windows上模拟Unix环境的工具）时定义。

`#define COMPILER_DLL_EXPORT __declspec(dllexport)` 如果上述条件为真（即代码正在Windows或Cygwin环境下编译），则定义宏`GC_DLL_EXPORT为__declspec(dllexport)`。`__declspec(dllexport)`是Windows平台特有的关键字，用于在编译时告诉编译器将后面的符号（函数或变量）导出到DLL中，使得这些符号可以被其他模块或程序链接和使用。

`#else` 如果上述条件不为真（即代码不是在Windows或Cygwin环境下编译），则执行`#else`分支。

`#define COMPILER_DLL_EXPORT __attribute__((visibility("default")))` 在非Windows平台上，宏`GC_DLL_EXPORT`被定义为`__attribute__((visibility("default")))`。**这是GCC和Clang等编译器支持的属性，用于控制符号的可见性**。`visibility("default")`属性指示**编译器将符号导出为共享库的公共接口**，这意味着这些符号可以**被其他模块或程序链接和使用**。

`#endif` 结束条件编译指令。

### 如何应用这段代码

**当你编写一个库并希望将其中的某些函数或变量导出为公共API时**，你可以使用 `COMPILER_DLL_EXPORT` 宏来标记这些函数或变量。例如：

~~~cpp
// mylibrary.h
#ifndef MYLIBRARY_H
#define MYLIBRARY_H
#include "export.h" // 假设上述宏定义在这个头文件中

// 使用 COMPILER_DLL_EXPORT 宏来导出函数
COMPILER_DLL_EXPORT void myPublicFunction();

#endif // MYLIBRARY_H
~~~

在这个例子中，`myPublicFunction`函数被标记为导出，这意味着它将成为库的公共API。当这个头文件被包含在源文件中并且源文件被编译为 DLL 或共享库时，`myPublicFunction`函数将**可以被其他模块或程序链接和使用**。

这种方式使得你的库代码**更加可移植**，因为它可以在不同的操作系统平台上正确地导出符号，而无需修改源代码。

- 定义函数

首先，在你的库代码中定义 myPublicFunction 函数。例如，如果你正在编写一个库，你可能会在一个源文件中这样实现它：
~~~cpp
// mylibrary.cpp
#include "mylibrary.h"
// 实现函数
void myPublicFunction() {
    // 函数的功能代码
    // ...
    std::cout << "Hello from myPublicFunction!" << std::endl;
}
~~~

- 编译库

接下来，你需要将你的库编译成 DLL 或 SO 文件。这通常涉及到使用编译器（如gcc、clang、或MSVC）和构建系统（如Make、CMake等）。

例如，使用 gcc 编译一个共享库可能看起来像这样：

`gcc -shared -o libmylibrary.so mylibrary.cpp -fPIC` 在Windows上，使用MSVC编译DLL可能看起来像这样： `cl /LD mylibrary.cpp /o mylibrary.dll`

- 使用函数

一旦你的库被编译成DLL或SO文件，其他程序就可以链接到这个库并调用 `myPublicFunction` 函数了。**在其他程序中，你需要 1.包含库的头文件以获取函数的声明，2. 并在链接时指定库文件**。

- 例如，另一个程序可能包含以下代码：

~~~cpp
// main.cpp
#include "mylibrary.h"

int main() {
    // 调用库中的函数
    myPublicFunction();
    return 0;
}
~~~

然后，你可以编译这个程序并链接到你的库：

`gcc -o myprogram main.cpp -L/path/to/library -lmylibrary` 在这个命令中，`-L/path/to/library` 指定了库文件的路径，`-lmylibrary` 指定了要链接的库的名称（不包括前缀 lib 和后缀 .so 或 .dll）。

### 注意事项

确保在编译时定义了 `COMPILER_DLL_EXPORT` 宏，以便正确地导出函数。在 Windows 上，当你编译使用DLL的程序时，你可能需要定义一个宏来导入DLL中的函数，例如` __declspec(dllimport)`。这通常通过在包含头文件之前定义另一个宏来实现，例如 `COMPILER_DLL_EXPORT`。

确保在运行使用库的程序时，库文件（DLL或SO）位于程序可以找到的路径上，例如通过设置 `LD_LIBRARY_PATH` 环境变量在Linux上，或 PATH 环境变量在Windows上。
通过这种方式，myPublicFunction 可以作为库的一部分被其他程序使用，从而实现代码的重用和模块化。


