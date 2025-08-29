// #include <stdio.h>
// #include "my_math.h"

// int main() {
//     int a = 3;
//     int b = 5;
//     printf("a + b = %d\n", add(a, b));
//     printf("a-b=%d\n", sub(3, 5));
//     printf("a*b=%d\n", mul(3, 5));
//     printf("a/b=%d", div(3, 5));

//     return 0;
// }


#include <stdio.h>
#include <dlfcn.h>  // windows 下似乎没有该文件
int main() {
    int m = 3, n = 4;
    //打开库文件
    void* handler = dlopen("libmymath.so", RTLD_LAZY);
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