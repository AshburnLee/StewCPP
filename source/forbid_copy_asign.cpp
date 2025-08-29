#include "forbid_copy_asign.hpp"
#include <iostream>

int main () {
    MySmartPointer p0(new int(20));
    // below, comple error at compile time
    // "error: use of deleted function"
    /*

    MySmartPointer obj2(obj0);  // error 因为拷贝构造函数被删除
    MySmartPointer obj3 = obj0;  // error 因为赋值构造函数被删除
    */
    MySmartPointer p1 = std::move(p0);  // 使用移动构造函数
    MySmartPointer p2;
    p2 = std::move(p1);  // 使用移动赋值运算符，其等价于 p2.operator=(std::move(p1));


    std::cout << "p1.ptr: " << p0.get_ptr() << std::endl;
    std::cout << "p2.ptr: " << p1.get_ptr() << std::endl;
    std::cout << "p3.ptr: " << p2.get_ptr() << std::endl;

    return 0;
}
