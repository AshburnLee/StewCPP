## 显式调用动态链接库   low priority

Windows 下以“运行时加载”的方式调用一个动态链接库。Linux 平台也支持运行时加载。

Linux 平台下，动态加载库的装载、使用、卸载等操作需要借助以下 4 个函数来完成，使用它们时需要引入`<dlfcn.h>`头文件。 

1) dlopen()：打开库文件

    - 类似于读写文件前必须先打开文件，程序使用某个库文件的资源时也需要先打开它。所谓“打开”动态库文件，其实就是将库文件装载到内存中，使当前程序（进程）可以使用它。

    - 打开库文件需要借助 dlopen() 函数，语法格式为：

        `void* dlopen (const char* filename, int flag);`

    - filename 参数用于指定目标动态库的存储路径和库文件名；flag 参数的值有以下 2 种：

      - `RTLD_NOW`：将库文件中所有的资源都载入内存；
      - `RTLD_LAZY`：暂时不将库文件中的资源载入内存，使用时才载入。


    - dlopen() 函数成功加载库文件时，会返回一个指向它的指针，这个指针在调用 dlsym() 和 dlclose() 函数时会用到；如果加载失败，则返回 NULL。

2) dlsym()：从库文件中找到要调用的资源

    - 库文件成功“打开”后，借助 dlsym() 函数可以调用库文件中的资源（函数或者变量），语法格式如下：

        `void* dlsym(void *handle, char *symbol);`

      - hanle 参数为已打开的库文件的指针
      - symbol 参数用于指定要调用的函数的名称。

    - 如果 dlsym() 函数成功找到指定函数，会返回一个指向该函数的指针；反之如果查找失败，函数会返回 NULL。

3) dlerror()：获取调用失败的原因
    - 借助 dlerror() 函数，我们可以获得最近一次 dlopen()、dlsym() 或者 dlclose() 函数操作失败的错误信息。该函数的语法格式如下：

        `const char* dlerror(void);`

    - 调用 dlerror() 函数需要传递任何参数。如果返回值为 NULL，表明上一次调用的 dlopen()、dlsym() 或 dlclose() 函数执行成功；反之，则返回相应的错误信息。

4) dlclose()：关闭打开的库文件

    - dlclose() 函数的作用和 dlopen() 函数正好相反，它用于卸载一个已加载的动态库。

    - 注意，同一个动态库文件可能载入多次，每个动态库文件都配置一个初始值为 0 的计数器，当调用 dlopen() 函数加载它时，计数器加 1，当有 dlclose() 函数卸载它时，计数器减 1，只有当计数器减至 0 时，动态库才会被真正地卸载掉（取消进程空间和该动态库的映射关系），指向链接库的指针也会失效。

    - dlclose() 函数的语法格式如下：

        `int dlclose (void *handle);`
        handle 表示已打开的库文件指针。当函数返回 0 时，表示函数操作成功；反之，函数执行失败。

## 例

首先创建好 libmymath.so 动态库文：

`g++ -shared mymath.o -o libmymath.so `

以下是演示整个显式调用的过程：

main.c

```cpp
#include <stdio.h>
#include <dlfcn.h>
int main() {
    int m = 3, n = 4;
    //打开库文件
    void* handler = dlopen("libmyMath.so", RTLD_LAZY);
    if(dlerror() != NULL){
        printf("%s",dlerror());
    }
  
    //获取库文件中的 add() 函数
    int(*add)(int,int)=dlsym(handler, "add");
    if(dlerror()!=NULL){
        printf("%s",dlerror());
    }
    //获取库文件中的 sub() 函数
    int(*sub)(int,int)=dlsym(handler, "sub");
    if(dlerror()!=NULL){
        printf("%s",dlerror());
    }
    //获取库文件中的 mul() 函数
    int(*mul)(int,int)=dlsym(handler, "mul");
    if(dlerror()!=NULL){
        printf("%s",dlerror());
    }
    //获取库文件中的 div() 函数
    int(*div)(int,int)=dlsym(handler, "div");
    if(dlerror()!=NULL){
        printf("%s",dlerror());
    }
    printf("%d+%d=%d\n",m,n,add(m, n));
    printf("%d-%d=%d\n",m,n,sub(m, n));
    printf("%d*%d=%d\n",m,n,mul(m, n));
    printf("%d÷%d=%d\n",m,n,div(m, n));
    //关闭库文件
    dlclose(handler);
    return 0;
}
```

将 main.c 和 libmymath.so 置于同一目录执行：

`gcc main.c -o test -ldl`

注意，程序中用到了<dlfcn.h>头文件，对应的库文件为/lib/libdl.so，gcc 命令在编译 main.c 时必须用-ldl指明这个库文件

