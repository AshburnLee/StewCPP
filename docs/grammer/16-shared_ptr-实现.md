
实现一个简化的 `shared_ptr` 需要考虑引用计数和内存管理。见 self_`shared_ptr`.h

---

## 手写实现 `shared_ptr` 

`shared_ptr` 的行为：它的主要行为是共享所有权 (shared ownership)，允许多个 `shared_ptr` 实例指向同一个对象，并自动管理对象的生存期

引用计数，一旦 T 类型对象的引用计数为0，就释放该对象。构造函数负责计数器++和分配内存，析构函数负责引用计数--和释放内存。

核心行为：

- 引用计数: `shared_ptr` 内部维护一个引用计数，记录有多少个 `shared_ptr` 实例指向同一个对象。
- 共享所有权: 多个 `shared_ptr` 可以指向同一个对象，它们共享对象的所有权。
- 自动销毁: 当最后一个指向对象的 `shared_ptr` 被销毁或重置时，引用计数变为 0，`shared_ptr` 会自动销毁对象并释放其内存。

- **自定义删除器**: 可以指定自定义删除器，用于控制对象销毁的方式，例如使用 `delete[]` 销毁数组，或调用对象的特定析构函数。
- 线程安全： `shared_ptr` 的控制块 (引用计数) 的操作是线程安全的，但指向的对象本身的操作不是线程安全的。


简化的实现，需要有构造函数，拷贝构造函数，赋值运算符，引用计数器，共享所有权，自动销毁。

重点：

1. 构造函数：构造函数负责计数器++和分配内存。
2. 拷贝构造函数：对于资源是**浅拷贝**，对于计数器首先也是**浅拷贝**，然后是增加计数器。对于指针类型，浅拷贝仅复制指针指向内容，使得源对象与目标对象共享同一块内存资源。
3. 赋值运算符：首先原有计数器--，然后复制新资源的指针地址，并增加计数器。


## 语法补充
### 1. `count_ = new int(10);`  

- `int(10)` 调用了 int 的初始化器，相当于是构造函数，分配足够存储一个 int 类型的内存空间。
- 然后它告诉编译器使用值 10 来初始化新分配的 int 变量。
- 最后 new 运算符返回一个指向新分配并初始化了的 int 变量的指针。

new 运算符用于动态分配内存

~~~cpp
SelfMemcpy* sss = new SelfMemcpy[10];
for (int i = 0; i < 10; ++i) {
    std::cout << "sizeof(sss[i]): " << sizeof(sss[i]) << "; "<<&sss[i] << "\n";
}
delete[] sss;
~~~


### 2. 智能指针的**策略组件** （policy）

`unique_ptr` 默认删除器 vs 自定义**删除器**

下面这个例子把你问的两句写完整，并体现核心点：  
**`D` 是策略位（deleter 类型）**，默认是 `default_delete<T>`，也可以替换成你自己的释放策略。

~~~cpp
#include <iostream>
#include <memory>

// 自定义删除器：打印日志 + delete
struct MyDeleter {
    void operator()(int* p) const {
        std::cout << "[MyDeleter] deleting int at " << p
                  << ", value=" << *p << "\n";
        delete p;
    }
};

int main() {
    // 1) D 自动使用 default_delete<int>
    std::unique_ptr<int> p1(new int(42));
    std::cout << "p1 value = " << *p1 << "\n";
    // 作用域结束时，调用 default_delete<int>{}(p1.get())，等价 delete

    // 2) D 显式替换为 MyDeleter
    std::unique_ptr<int, MyDeleter> p2(new int(99));
    std::cout << "p2 value = " << *p2 << "\n";
    // 作用域结束时，调用 MyDeleter{}(p2.get())
    // 你会看到自定义日志，证明释放策略已被替换

    return 0;
}
~~~

核心点：
- `unique_ptr<T, D>` 的第二个模板参数 `D` 决定“怎么释放资源”。
- 默认不写 `D` 时，`D = default_delete<T>`，普通 `delete`。
- 写成 `unique_ptr<T, MyDeleter>` 后，释放行为由 `MyDeleter::operator()` 接管。




