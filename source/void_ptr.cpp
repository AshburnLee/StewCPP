#include "void_ptr.h"
#include <iostream>

using grammer::void_ptr::MemSet;
using namespace std;

struct Person {
    int age;
};

void TestPtrSize() {
    // 每种类型指针的大小都是8字节
    printf("sizeof(char*): %zd \n", sizeof(char *));
    printf("sizeof(int*): %zd \n", sizeof(int *));
    printf("sizeof(double*): %zd \n", sizeof(double *));
    printf("sizeof(void*): %zd \n", sizeof(void *));
    unique_ptr<int> uptr(new int(6));
    printf("sizeof(unique_ptr): %zd \n", sizeof(uptr));
    printf("%zd \n", sizeof(void)); // 不同编译器，此处结果不同
}

void TestAcceseVoidPre() {

    int a = 0;
    void *p1 = &a;
    float b = 0.f;
    void *p2 = &b;
    double c = 0.f;
    void *p3 = &c;
    // 报错：因为p1、p2、p3 都是void型指针，*p1 并不知道要取多少个字节，
    // printf("*p1: %zd\n", *p1);
    // printf("*p2: %zd\n", *p2);
    // printf("*p3: %zd\n", *p3);

    // 将void* 转化为指定类型后才行：
    printf("*p1: %zd\n", *(int *)p1);
    printf("*p2: %zd\n", *(float *)p2);
    printf("*p3: %zd\n", *(double *)p3);
}

void TestArea() {
    // ----------------------------------
    int nums[3] = {1, 2, 3};
    void *ptr = nums;
    printf("ptr first item: %d\n", *(int *)ptr);
    //int i = *ptr;  // wrong, void型指针不能取值，不能移动
    // -----------------------------------
    Person per;
    // 任何指针都可以用MemSet()进行初始化，所以MemSet()内是void指针
    MemSet(&per, sizeof(Person)); 
    printf("per.age: %d, sizeof(Person): %d\n", per.age, sizeof(Person));
}



int main() {
    cout << "------------------------void_ptr\n";
    grammer::void_ptr::TestMemSet();
    TestPtrSize();
    TestAcceseVoidPre();
    TestArea();
    grammer::void_ptr::TestTemplatesVoidPtr();
    grammer::void_ptr::TestMyAlloc();
    grammer::void_ptr::test_my_alloc();
    return 0;
}