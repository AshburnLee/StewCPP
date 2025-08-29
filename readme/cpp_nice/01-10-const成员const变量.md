## const 成员变量 初始化

初始化 C++ const 类成员变量的方法：构造函数初始化列表: 它在构造函数体执行之前初始化 const 成员，保证了 const 成员的不可变性。这是最佳实践。

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

用于初始化 static const 成员的表达式必须在编译期间就能计算出结果，而不是在运行时。

因为 static const 成员是静态的，这意味着它们只存在一个副本，并且在程序的整个生命周期中都存在。编译器需要在编译时就确定它们的值，以便在程序加载时直接将这些值放入程序的内存中。


## const 成员函数 常量函数 [getter]

const 成员函数可以使用类中的所有成员变量，但是不能修改它们的值，这种措施主要还是为了保护数据而设置的。

我们通常将 get 函数设置为常成员函数。读取成员变量的函数的名字通常以 get 开头，后跟成员变量的名字，所以通常将它们称为 getter 函数。

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

需要强调的是，必须在成员函数的**声明和定义**处同时加上 const 关键字。`char *getname() const` 和 `char *getname()` 是两个不同的函数原型。

最后再来区分一下 const 的位置：

- 函数开头的 const 用来修饰函数的返回值，表示返回值是 const 类型，也就是不能被修改，例如`const char* getname()`
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

`const char const* getname()` 表示返回指针内容是常量，指针本身也是常量：

~~~cpp
const char* getname1() { return "John Doe"; }
char const* getname2() { return "John Doe"; }
const char const* getname3() { return "John Doe"; }

int main() {
  const char* name1 = getname1();
  char const* name2 = getname2();
  const char const* name3 = getname3();

  // 下面三行都会编译错误，因为指向的内容是常量  ***
  // name1[0] = 'j';
  // name2[0] = 'j';
  // name3[0] = 'j';

  // 下面两行只在 getname3() 中会编译错误，因为指针本身是常量   ***
  // name1 = "Jane";
  // name2 = "Jane";
  // name3 = "Jane"; // 错误 ！

  return 0;
}
~~~

## const 对象只能调用其 const 成员函数  [确保const状态不变]

这确保了 const 对象的不可变性，这是 C++ 中一个重要的特性。

## 解惑

返回值是 const 类型的函数，也就是返回值不能被修改，例如 `const char* getname()`。值已经返回了，为什么不被修改？即这种返回值不能被修改的场景有什么？一种限制，限制函数的副作用。

解答：比如下标运算符，返回值不是 const，即返回值可被修改：

~~~cpp
// arr.operator[](i) = 3，将3写入m_ptr[i]，就是函数的返回值，
int& Array::operator[](int i) {
	return m_ptr[i];
}
~~~

在使用时 `arr[i] = 3`，本质上是`arr.operator[](i) = 3`，左边返回 arr 的 m_ptr 的第i个元素，并将3写入。所以这种情况下调的是非 `const operator[]`，返回值被修改。

