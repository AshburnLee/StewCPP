
## 指针的大小

在 64 位系统上，每个指针占用 8 个字节，`shared_ptr` 的大小通常为 16 个字节。在 32 位系统上，每个指针占用 4 个字节，`shared_ptr` 的大小通常为 8 个字节。

## 悬空指针 & 野指针

野指针和悬空指针都是指向无效内存地址的指针，但它们的产生原因不同。

- 悬空指针(*Dangling Pointer*)：指向已经被释放的内存空间的指针。为了避免这种情况，应该在不再需要时将指针设置为 nullptr 或者让其超出作用域自动销毁。

- 野指针(Wild Pointer)：是指未初始化的指针，即指针变量声明后未被赋予任何有效的内存地址。这种指针可能指向任意内存地址，甚至可能是随机的垃圾数据。

“野指针”的成因主要有3种：

指针变量没有被初始化。任何指针变量刚被创建时不会自动成为 `nullptr` 指针，它的缺省值是随机的，它会乱指一气。所以，指针变量在创建的同时应当被初始化，要么将指针设置为 `nullptr` ，要么让它指向合法的内存。

避免野指针：

1. 初始化指针为 `nullptr`
2. 用 malloc 分配空间
3. 用已有的合法的地址对指针赋值
4. 用完后将指针赋值 `nullptr`


## nullptr  c++11

nullptr 的类型是 std::nullptr_t，这是一个特殊的类型，它可以隐式转换为任何指针类型（就是可以与任何类型的指针比较如 `if (ptr == nullptr)`），但不能隐式转换为整数类型。 在需要明确指定空指针类型时，可以使用 std::nullptr_t。

NULL: NULL 是一个宏，通常定义为 0。 在某些情况下，NULL 会被隐式转换为整数 0，这可能导致类型安全问题。

最佳实践是 将旧代码中的 NULL 和 0 替换为 nullptr。

为什么 NULL 会有歧义：

~~~cpp
void func(int x) { std::cout << "int version: " << x << std::endl; }
void func(int* p) { std::cout << "pointer version: " << (p ? *p : 0) << std::endl; }

int main() {
  func(nullptr);       // 调用 pointer version
  func(0);             // 调用 int version (潜在的歧义)
  func(NULL);          // 调用 int version (潜在的歧义)  NULL 通常被定义为0
}
~~~

