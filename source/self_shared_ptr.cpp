#include "self_shared_ptr.h"
#include <memory>  // shared_ptr
#include "helper.h"  // CheckValue<int>()

int main() {

    // 1. 构造函数
    self_shared_ptr<int> ptr1(new int(10));
    // 2. 拷贝构造函数
    self_shared_ptr<int> ptr2 = ptr1;
    self_shared_ptr<int> ptr3 = ptr1;

    std::shared_ptr<int> std_ptr1(new int(40));
    std::shared_ptr<int> std_ptr2 = std_ptr1;
    std::shared_ptr<int> std_ptr3 = std_ptr1;

    CheckValue<int>(ptr1.use_count(), (int)std_ptr1.use_count());
    CheckValue<int>(ptr2.use_count(), (int)std_ptr2.use_count());
    CheckValue<int>(ptr3.use_count(), (int)std_ptr3.use_count());

    //ptr1 和 ptr2 指向同一个对象，
    std::cout << "ptr1 use count: " << ptr1.use_count() << std::endl; // 输出 3
    std::cout << "ptr2 use count: " << ptr2.use_count() << std::endl; // 输出 3
    std::cout << "ptr3 use count: " << ptr3.use_count() << std::endl; // 输出 3
    std::cout << "std_ptr1 use count: " << std_ptr1.use_count() << std::endl; // 输出 3
    std::cout << "std_ptr2 use count: " << std_ptr2.use_count() << std::endl; // 输出 3
    std::cout << "std_ptr3 use count: " << std_ptr3.use_count() << std::endl; // 输出 3



    // 3. 赋值运算符
    ptr3 = self_shared_ptr<int>(new int(20)); // ptr2 指向新的对象, ptr1 的引用计数减1
    std_ptr3 = std::shared_ptr<int>(new int(20));

    CheckValue<int>(ptr3.use_count(), (int)std_ptr3.use_count());
    std::cout << "ptr1 use count: " << ptr1.use_count() << std::endl; // 输出 2
    std::cout << "ptr2 use count: " << ptr2.use_count() << std::endl; // 输出 2
    std::cout << "ptr3 use count: " << ptr3.use_count() << std::endl; // 输出 1
    std::cout << "std_ptr1 use count: " << std_ptr1.use_count() << std::endl; // 输出 2
    std::cout << "std_ptr2 use count: " << std_ptr2.use_count() << std::endl; // 输出 2
    std::cout << "std_ptr3 use count: " << std_ptr3.use_count() << std::endl; // 输出 1

    // 匿名对象拷贝给命名对象
    self_shared_ptr<int> ptr4 = self_shared_ptr<int>(new int(30));
    std::shared_ptr<int> std_ptr4 = std::shared_ptr<int>(new int(30));

    CheckValue<int>(ptr4.use_count(), (int)std_ptr4.use_count());
    std::cout << "ptr4 use count: " << ptr4.use_count() << std::endl; // 输出 1
    std::cout << "std_ptr4 use count: " << std_ptr4.use_count() << std::endl; // 输出 1

    return 0;
}

