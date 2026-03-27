## const 成员变量 初始化

初始化 const 类成员变量的方法：构造函数初始化列表: 它在构造函数体执行之前初始化 const 成员，保证了 const 成员的不可变性。这是最佳实践。


## 静态常量成员 (static const) 初始化  [编译时]

如果 const 成员对于所有类实例都是相同的，可以将其声明为 static const，并在类定义中进行初始化。

~~~cpp
class MyClass {
private:
    static const int x = 10; // 静态常量成员，在类定义中初始化
public:
    void show_x() { std::cout << "Value of constant x: " << x << std::endl; }
};
~~~

用于初始化 static const 成员的表达式必须在*编译期间*就能*计算出结果*，而不是在运行时。

因为 static const 成员是静态的，这意味着它们只存在一个副本，并且在程序的整个生命周期中都存在。编译器需要在编译时就确定它们的值，以便在程序加载时直接将这些值放入程序的内存中。


## const 成员函数 常量函数 [getter]

const 成员函数可以使用类中的所有成员变量，但是不能修改它们的值，这种措施主要目的还是为了保护数据。

通常将 get 函数设置为常成员函数。读取成员变量的函数的名字通常以 get 开头，后跟成员变量的名字，所以通常将它们称为 getter 函数。

常成员函数需要在**声明和定义**的时候在函数头部的结尾加上 const 关键字，请看下面的例子： 

~~~cpp
class Student{
public:
    Student(char *name, int age, float score);
    // *** 声明常成员函数
    char* getname() const;
    int getage() const;
    float getscore() const;
private:
    char* m_name;
    int m_age;
    float m_score;
};
//定义常成员函数
char* Student::getname() const {
    return m_name;
}
...
~~~

`getname()`、`getage()`、`getscore() `三个函数的功能都很简单，仅仅是为了获取成员变量的值，没有任何修改成员变量的企图，所以我们加了 const 限制，这是最佳实践。***

必须在成员函数的**声明和定义**处同时加上 const 关键字。`char *getname() const` 和 `char *getname()` 是两个不同的函数原型。

最后再来区分一下 const 的位置：

- 函数开头的 const 用来修饰函数的返回值，表示返回值是 const 类型，也就是不能被修改，例如`const char* getname()`，注意这例返回的是指针/引用。***
- 函数头部的结尾加上 const 表示常成员函数，这种函数只能读取成员变量的值，而不能修改成员变量的值，例如`char* getname() const`


## const char* getname()   [应用场景？]

该函数返回一个指向字符数组的**常量指针** (const char*)。这意味着你不能通过这个指针修改它指向的字符串内容（指针指向的内容不能被修改，**内容是 const**）。你可以读取字符串，但不能修改它。 该函数本身不是常量函数。这意味着函数内部可以修改类成员变量。

所以，这种函数与 `char* getname() const` 恰好是相反的。

~~~cpp
class Person {
public:
    const char* getName() { 
        return name.c_str(); 
    }
private:
    std::string name;
};

{
    Person p;
    p.name = "John Doe";

    const char* name1 = p.getName();
    // name1[0] = 'J'; // 编译错误，因为 name1 指向的是常量字符串
}
~~~

## 风格

注意：`const char* getname()` 和 `char const* getname()` 是完全等效的，只是风格不同 ***

下面把`const` 修饰指针 分清楚：

~~~cpp
const char* getname1() { return "John Doe"; }  // 指向 const char 的指针
char const* getname2() { return "John Doe"; }  // 与上面完全等价

int main() {
  const char* name1 = getname1();
  char const* name2 = getname2();

  // 下面两行都会编译错误：因为“指向的字符”是 const
  // name1[0] = 'j';
  // name2[0] = 'j';

  // 下面两行可以：指针变量本身可改指向
  name1 = "Jane";
  name2 = "Jane";

  return 0;
}
~~~

如果你要表达“指针本身不能改”，应在**变量声明处**写：

~~~cpp
const char* p1 = "John";        // 可改 p1 指向，不可改 *p1 ，实际中最常见
const char* const p2 = "John";  // 不可改 p2 指向，也不可改 *p2， 没啥实际意义
~~~

实际中最常见最有意义是 `const char*`：保护所指内容 ***


## const 对象只能调用其 const 成员函数  [确保const状态不变]

这确保了 const 对象的不可变性，这是 C++ 中一个重要的特性。


## 解惑

`const char* getname()` 并不是“返回值整体不能改”，而是“通过返回的指针，不能改它指向的字符”。

关键点：

- 若函数按值返回普通类型（如 `int`），调用方改的是副本，通常无所谓 const。
- 若函数返回指针/引用，调用方可能“透过它”改原对象；这时返回 `const T*` / `const T&` 可防止误改，保护对象状态。

解答：比如下标运算符，返回值不是 const，即返回值可被修改：

~~~cpp
// arr.operator[](i) = 3，将3写入m_ptr[i]，就是函数的返回值，
int& Array::operator[](int i) {
	return m_ptr[i];
}
~~~

在使用时 `arr[i] = 3`，本质上是`arr.operator[](i) = 3`，左边返回 arr 的 m_ptr 的第i个元素，并将3写入。所以这种情况下调的是非 `const operator[]`，返回值被修改。

总之：
- 如果返回的是值类型（比如 int、std::string 按值返回），caller 改的是副本，通常改不到原对象。
- 如果返回的是指针/引用，caller 仍然能“透过它”改原对象；这时 const 就很关键。


## 混淆 ***

- `char* const p` “*” 左边无const（可改内容），“*” 右边有const（不可改指向）
- `const char* p` 和 `char const* p` “*”左边有const，完全等价（所指内容不可改）
- `const char* const p` “*” 左右都有const（内容和指向都不可改）
- `const char const*` “*” 左边两个const，重复笔误 

以下语法不对，但是便于记忆：

`(char)* const p;` : p 前是const，即p不能改指向，*前是char，即p指向元素可以改。
`(const char)* p;` : p 前无const，即p可改指向，*前是const char，即p指向元素不能改。
`(const char)* const p` : p 是const，且指向的元素也是const。 
