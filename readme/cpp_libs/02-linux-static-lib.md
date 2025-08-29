## 创建和使用静态库

创建 my_math.c 文件

~~~cpp
// my_math.h
//实现两个整数相加，返回它们的和
int add(int a, int b);
//实现两个整数相减，返回它们的差
int sub(int a, int b);
//实现两个整数相乘，返回它们的乘积
int mul(int a, int b);
//实现两个整数相除，返回它们的商
int div(int a, int b);

// my_math.cpp
#include "my_math.h"
int add(int a, int b) {
    return  a + b;
}
int sub(int a, int b) {
    return  a - b;
}
int mul(int a, int b) {
    return  a * b;
}
int div(int a, int b) {
    if (b != 0) {
        return a / b;
    }
    return -1;
}
~~~

## 创建静态库

Linux上，GCC编译器将上述文件转换为静态库需要两步骤：

1) 编译所有的 .c 库文件，生成对应的目标文件。本节我们以 my_math.cpp 库文件为例，因此只编译这 1 个文件即可。

    首先，准备好要编译的 my_math.cpp 库文件和 my_math.h 头文件，使用**编译器**执行：

    ~~~sh
    g++ -c my_math.cpp -o my_math.o  # 编译.cpp 文件
    ~~~

2) 将所有的目标文件打包成一个静态链接库。例如，下面的指令将 my_math.o 打包成了一个静态链接库

    ~~~sh  
    ar rcs libmymath.a my_math.o   # 打包为libxxx.a
    ~~~

    `ar` 命令常用于创建静态链接库，其中 `r、c、s` 是 `ar` 命令创建静态链接库所需要设定的参数。
    需要注意的是，Linux 平台上静态链接库的名称不是随意的，通常遵循 libxxx.a 格式，xxx 部分可以自定义。

经过以上两步，我们就成功地创建了一个静态链接库文件。

## 使用静态库

静态链接库的用法很简单，就是和其它目标文件一起参与链接，最终生成一个可执行文件。***

先创建一个 main.cpp。并对 改文件进行编译得到对应的目标文件：

~~~cpp
g++ -c main.cpp -o main.o
~~~

由此，我们得到了 `main.o` 和 `libmymath.a` 这两个目标文件，接下来就可以开始将它们链接成一个可执行文件，实现链接的指令有两种： 

1) `g++ -static main.o libmymath.a -o test`

2) `g++ main.o -o test -static -lmymath -L ./`  `-l`后紧跟`libxxx.a` 中的`xxx`部分；`-L` 指明`libxxx.a` 的路径

使用gcc一样的结果。

两种方式都可以将 `main.o` 和 `libmymath.a` 链接成一个可执行文件，该文件的名称为 `test`

执行：`./test`

### 完整命令

~~~sh
vim my_math.cpp
vim my_math.cpp.h

g++ -c my_math.cpp -o my_math.o
ar rcs libmymath.a my_math.o

vim main.cpp

g++ -c main.cpp -o main.o
g++ -static main.o libmymath.a -o test
# 或 
# g++ main.o -o test -static -lmymath -L ./

./test
~~~
