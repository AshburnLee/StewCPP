# 用法
## 修饰变量，使其成为常量

`const int x = 10; // x的值不能被改变`

## 修饰指针变量

1. 指针指向的地址不能改变，但指针指向的内容可以改变

~~~cpp
int x = 10;
int *const p = &x; // p指向的地址不能改变, 就是p中的内容不能变 ***
~~~

`const p`是个整体，即这个变量 p 存储的内容不能变（这里是自然的），`int *` 表示 p 指向的地址存储内容是int

2. 指针指向的内容不能改变，但指针指向的地址可以改变。

~~~cpp
int x = 10;
int const* p = &x; // *p指向的内容不能改变
~~~

`int const` 是个整体，表示地址中存储的内容是 `const int` 的，即指针指向的内容不能变。***

3. 常量指针常量：既指针指向的地址不能改变，也不能改变指针指向的内容。

~~~cpp
int x = 10;
const int *const p = &x; // p指向的地址和内容都不能改变
~~~

## 修饰引用

防止通过引用修改原变量的值。函数传入 `&`，避免了拷贝，但是如果不希望参数被修改，要是 `const &`。

~~~cpp
void fun(const int &y) {
    // y = 20; // 错误，不能修改
}
~~~

## 修饰函数参数-防止函数内部修改参数的值：

~~~cpp
void fun(const int x) {
    // x = 20; // 错误，不能修改
}

防止函数内部修改指针指向的内容：***

void fun(const int *p) {
    // *p = 20; // 错误，不能修改
}
~~~

## 修饰函数返回值

如果函数返回的是引用或指针防止函数外部通过返回值修改数据：

~~~cpp
const int &fun() {
    static int x = 10;
    return x; // 返回一个常量引用
}

int main() {
    // fun() = 20; // 错误，不能修改
    return 0;
}
~~~

返回值是拷贝：`const int my_func() {}` 表示函数返回值不能在后续被修改，即可以读但不能被写。


## 修饰成员函数-不能修改类的成员变量

一般用于修饰**类的成员函数**， const 类对象中调用 const 方法。

~~~cpp
class MyClass {
public:
    void fun() const { // fun是常成员函数
        // this->x = 20; // 错误，不能修改成员变量
    }
private:
    int x;
};
~~~

## 修饰类成员属性

常成员函数只能在类的初始化列表中被初始化。在类对象的生命中不能被修改。

# 其他 const 相关
## const_iterator 和 iterator 的区别

`const_iterator` 和 `iterator` 都是用于遍历容器（如`std::vector`、`std::list`等）中元素的迭代器类型，它们之间的主要区别在于对容器中元素的访问权限。在编程过程中，如果你需要保证不会修改容器中的元素，建议使用 `const_iterator`，以防止意外的修改。

- `iterator` 允许修改所指向元素的值。
- `const_iterator` 用于只读访问容器中的元素，不能通过它来修改元素的值。

## c++ 中哪些方式可以将一个对象的 const 修饰去掉

~~~cpp
const int x = 10;
int& y = const_cast<int&>(x);  // 使用 const_cast 去掉 const 修饰
y = 20;  // 现在可以修改 x 的值

std::cout << "x: " << x << std::endl;  // x 现在的值是 20
~~~


## const 碎片

~~~cpp
int& a = 10;  // 错
const int& a = 10;  // 对，不过只是个 walk around：（The compiler will create a temporary object to hold the value of 10 and bind the const reference to that object.）

// 编译器会做如下操作：
int tmp = 10;
const int& a = tmp;
~~~

## const_cast 隐式从非 const 转换为 const

其实就是函数 const 形参数 可以接受非 const 实参，编译器会自动进行隐式转换。

~~~cpp
void printString(const char* str) {
  std::cout << str << std::endl;
}

int main() {
  char* str = new char[20];
  strcpy(str, "Hello, world!");

  // 隐式转换，不需要手动 const_cast
  printString(str);
  // 显式转换，使用 const_cast (不推荐)
  const char* constStr = const_cast<const char*>(str);
  printString(constStr);
}
~~~
