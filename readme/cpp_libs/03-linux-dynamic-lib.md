## 创建动态链接库

已有 my_math.h 和 my_math.cpp 和 main.cpp。生成动态链接库只需要：

`g++ -shared -fPIC my_math.cpp -o libmymath.so`

g++ (gcc) 命令中，各个选项的含义是：
 
- `-shared`：表示生成动态链接库；
- `-fPIC`：也可以写成 `-fpic`，功能是令 GCC 编译器生成动态链接库时，用相对地址表示库中各个函数和变量的存储位置。这样做的好处是，无论动态链接库被加载到内存的什么位置，都可以被多个程序（进程）同时调用；
- `-o libmymath.so`：-o 选项用于指定生成文件的名称，此命令最终生成的动态链接库文件的文件名为 `libmymath.so`。

也可以：先将 my_math.c 编译为目标文件，然后再将目标文件转换为动态链接库，整个过程为： 

`g++ -c -fPIC mymath.c `                   转换为目标文件
`g++ -shared mymath.o -o libmymath.so `    生成动态链接库

## 使用动态链接库

`g++ .\main.cpp .\libmymath.so -o test` 生成可执行文件
`./test` 执行

## 可能会发生的问题

注意：`libmymath.so` 和 `test` 会一起载入内存。以下内容在Linux下可能会发生：

运行 test 时可能会遇到如下问题： 

~~~sh
error while loading shared libraries: libmymath.so: cannot open shared object file: No such file or directory
~~~

通过执行 `ldd test` 指令，可以查看 test 执行时需要调用的所有动态链接库，及各自的存储位置：

~~~sh
~$ ldd test
linux-vdso.so.1 (0x00007fff353ef000)
libmymath.so => not found
libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fef8c9fd000)
/lib64/ld-linux-x86-64.so.2 (0x00007fef8cc07000)
~~~

可以看到 libmymath.so 显示 not found

运行由动态链接库生成的可执行文件时，必须确保程序运行时可以找到所有需要的动态链接库。常用的解决方案有如下几种：

- 将链接库文件移动到标准库目录下（例如 /usr/lib、/usr/lib64、/lib、/lib64）；
- 在终端输入`export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:xxx`，其中xxx为动态链接库文件的绝对存储路径（此方式仅在当前终端有效，关闭终端后无效）；
- 修改`~/.bashrc`或`~/.bash_profile`文件，即在文件最后一行添加`export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:xxx`（xxx为动态库文件的绝对存储路径）。保存之后，执行`source .bashrc`指令（此方式仅对当前登陆用户有效）。
