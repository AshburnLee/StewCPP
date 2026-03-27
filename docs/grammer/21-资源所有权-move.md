1. 需要一个真实场景来消化unique_ptr 和其支持的move 语义

===

## 垃圾回收（GC）

垃圾回收机制是一种自动内存管理的技术，它可以自动释放程序不再使用的内存（识别并回收垃圾）。 C++ 没有内置的垃圾回收机制，而是采用手动内存管理的方式，并提供了智能指针来简化内存管理。

## RAII   [重要编程理念]

构造函数获取资源，析构函数释放资源，当 RAII 对象存在时，资源可用；当 RAII 对象销毁时，资源被自动释放。 这使得资源管理变得简单而安全。

C++ 中 RAII 的体现示例:

- 智能指针 (Smart Pointers): `std::unique_ptr`, `std::shared_ptr` 等智能指针是 RAII 的典型应用。它们管理动态分配的内存，在对象**析构时自动释放内存**，避免内存泄漏。
- `std::lock_guard` 和 `std::unique_lock`: 这些类用于管理互斥锁，在构造函数中获取锁，在**析构函数中释放锁**，确保锁的正确释放，即使发生异常也能保证锁被释放，避免死锁。
- 文件流: `std::ofstream` 和 `std::ifstream` 等文件流对象也体现了 RAII。它们在构造函数中打开文件，在**析构函数中关闭文件**，确保文件被正确关闭，即使发生异常也能保证文件被关闭。

RAII 的优势:

- 避免资源泄漏: RAII 保证了资源的正确释放，**即使发生异常也能确保资源得到清理**。
- 简化代码: RAII 将**资源管理与对象生命周期绑定在一起**，简化了代码，减少了出错的可能性。
- 提高代码可读性: RAII 使代码更易于理解和维护。
- 增强异常安全性: RAII 确保**即使发生异常，资源也能得到正确释放**，提高了程序的健壮性。


## unique_ptr & shared_ptr [所有权]

- unique_ptr: 防止内存泄漏，防止忘记 delete 内存，没有 GC(垃圾回收)。不能有两个 unique_ptr 同时指向同一个对象。
- shared_ptr: 当想让多个指针指向同一个对象；或想让指针在函数间专递。
- 主要区别在于所有权：unique_ptr 具有独占所有权，而 shared_ptr 允许多个指针共享所有权。
- 性能：unique_ptr 的开销比 shared_ptr 小，因为它不需要引用计数。

一般来说，优先考虑 unique_ptr。只有在确实需要**共享所有权**时才使用 shared_ptr。

## 资源的所有权 [所有权]

资源的所有权指的是对资源（例如动态分配的内存、文件句柄、网络连接、互斥锁等）的管理责任。 它决定了哪个对象负责获取、使用和释放资源，以及如何处理资源的生命周期。

C++ 提供了几种机制来管理资源所有权：

- RAII (资源获取即初始化): 这是 C++ 中管理资源所有权的核心原则。智能指针是 RAII 的一个重要应用。RAII 将**资源的获取与对象的创建绑定**在一起，并将资源的释放与对象的销毁绑定在一起。
- 智能指针: 智能指针是 RAII 的一种实现方式，它们是包装原始指针的对象。
- 手动内存管理 (使用 new 和 delete): 这是最底层的资源管理方式。易出错。
- Ownership Transfer (所有权转移): 这指的是将资源的所有权从一个对象转移到另一个对象。这可以通过移动语义 (`std::move`) 或其他机制来实现。 例如，使用 `std::move` 可以将 `unique_ptr` 的所有权转移到另一个 `unique_ptr`。
- Ownership Models (所有权模型): 不同的所有权模型描述了资源在不同对象之间的关系： `unique_ptr` 是单一所有权， `shared_ptr` 是共享所有权，还有无所有权，如 `const T&` , 表示对象不拥有资源，只是读取资源。

所有权转移的实例：

~~~cpp
auto ptr = std::make_unique<int>(10); // *ptr 是 10
// 所有权转移 (unique_ptr)
auto ptr2 = std::move(ptr); // ptr2 现在拥有资源 10，ptr 现在为空
~~~

## unique_ptr 支持移动语义  [所有权]

unique_ptr 的移动语义是其核心特性之一，允许高效地转移所有权，**避免了复制和潜在的内存泄漏**。而且 unique_ptr 之间的拷贝是不允许的，但是可以移动资源所有权的。

可以方便地将所有权从一个 unique_ptr 转移到另一个 unique_ptr。这在函数参数传递和返回值时非常有用：

~~~cpp
std::unique_ptr<int> ptr1(new int(5));
std::unique_ptr<int> ptr2 = std::move(ptr1); // 使用move转移所有权 ptr1 不再拥有任何资源
~~~

函数参数传递：

~~~cpp
#include <iostream>
#include <memory>

void processData(std::unique_ptr<int> data) {
  if (data) {
    std::cout << "Processing data: " << *data << std::endl;
  }
}

int main() {
  std::unique_ptr<int> ptr(new int(42));
  processData(std::move(ptr)); // 将所有权转移到 processData 函数
  // ptr 现在为空，不能再访问它指向的内存
  if (!ptr) {
    std::cout << "ptr is now null" << std::endl;
  }
  return 0;
}
~~~

在这个例子中， `processData` 函数接受一个 `unique_ptr<int>` 作为参数。`std::move(ptr)` 将 `ptr` 的所有权转移到 `processData` `函数。processData` 函数处理数据后，`ptr` 在 `main` 函数中变为空指针。 关键在于 `std::move`，它将 `unique_ptr` 转换为右值引用，允许移动构造函数执行，从而高效地转移所有权。

函数返回值:

~~~cpp
std::unique_ptr<int> createData(int value) {  // 还没有任何对象被创建，因此还没有任何所有者。
  return std::make_unique<int>(value); // 创建了一个 int 对象，并将其所有权交给一个新的 std::unique_ptr<int> 对象。
} // std::unique_ptr<int> 对象作为返回值被返回。 所有权转移到调用 createData 的地方

int main() {
  // 这个 std::unique_ptr<int> 对象被赋值给 ptr。 现在，ptr 拥有 int 对象的所有权。 
  // 原来的 std::unique_ptr<int> 对象（在 createData 函数内部创建的）的生命周期结束，
  // 它所管理的资源（int 对象）的所有权被转移给了 ptr。
  std::unique_ptr<int> ptr = createData(100); // 返回一个 std::unique_ptr<int> 对象,它拥有 int 对象所有权
  std::cout << "Data from createData: " << *ptr << std::endl;
  return 0;
} // main 函数结束，ptr 对象的生命周期结束。 ptr 的析构函数被调用，它自动释放 int 对象占用的内存
~~~

`createData` 函数返回一个 `unique_ptr<int>`。`std::make_unique` 是一个方便的辅助函数，它直接创建一个 `unique_ptr` 并初始化它指向的内存。 返回值的 `unique_ptr` 的所有权被转移到 `main` 函数中的 `ptr`。[是的，代码注释也是这个意思]


## 在 C++ 中移动语义是什么  [资源管理]

移动语义是一种**资源管理技术**，它允许在不进行内存复制的情况下将资源（例如堆分配的内存）从一个对象转移到另一个对象。这可以通过使用**右值引用**和**移动构造函数**来实现。**移动语义可以提高程序的性能，因为它避免了不必要的内存分配和复制。**

`std::move`的作用是将一个**左值**强制转换为**右值引用**，从而可以使用**移动语义**
`std::move`通常在需要将一个对象的所有权从一个对象转移到另一个对象时使用，比如在实现**移动构造函数**和**移动赋值运算符**时
`std::move`的优势在于避免了不必要的内存分配和复制，提高了程序的性能

## 右值引用 int&&

左值引用（例如 `int&` ）可以绑定到左值，它们表示对一个已经存在的对象的引用。

右值引用（例如 `int&&` ）则可以绑定到将要销毁的临时对象（右值），它们允许你安全地修改这些临时对象，或者将它们的资源“移动”到另一个对象中，而不是进行复制。

这种区分是为了支持 C++11 中引入的移动语义（move semantics）和完美转发（perfect forwarding）。移动语义允许资源（如动态分配的内存）从一个对象转移到另一个对象，而不需要进行资源的复制。完美转发允许函数模板将参数以原始的值类别（左值或右值）转发给其他函数。

实例表达了右值引用如何与move语义使用：

~~~cpp
void takeOwnership(std::string&& str) {
    // 这里，str是一个右值引用，我们可以获取它的资源而不复制字符串
}

std::string createString() {
    return "temporary string";
}

int main() {
    std::string s = createString(); // createString返回一个临时字符串，是一个右值
    takeOwnership(std::move(s)); // 使用std::move将左值s转换为右值引用
    // 此时，s的资源已经被移动到takeOwnership的参数中，s不再拥有这些资源!!!
    return 0;
}
~~~

你希望代码的行为是这样的，才会这样写。品品上述注释。(`std::move(s)` 的类型是`xxx &&`)

## 完美转发