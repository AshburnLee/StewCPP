

### this 指针到底是啥

- `this` 是编译器为**非静态成员函数**隐式提供的 const 指针，它指向当前的对象，就是通过它访问当前对象的所有成员。
- 当前对象就是指正在使用的对象：比如`student1.show()`，`student1` 就是当前对象，`this`指向`student1`。this**只能用在类的内部**，通过 this 可以访问类的**所有成员**，包括private\protected\public属性。

准确的说：
- 在普通成员函数里，`this` 的类型近似 `Student * const`（指针本身不可改指向）。
- 在 `const` 成员函数里，`this` 的类型近似 `const Student * const`（也不能通过它改对象状态）。

只有在创建了对象后，this 才会被被编译器赋值。所以 this 是不能存在于 static 成员函数里的

## 一个直观例子：`this` 就是当前对象地址

~~~cpp
class Student {
public:
    void SetName(char * name) { this->m_name = name; } // this 是隐式的
    void SetAge(int age)      { this->m_age = age; }  // this 是隐式的
    void PrintThis() {
        std::cout << this << std::endl; // 打印 this 指针值（即当前对象地址）
    }
private:
    char * m_name = nullptr;
    int m_age = 0;
}

int main () {
    Student* stu1 = new Student;
    stu1->PrintThis();     // 0x715bd0
    cout << stu1 << endl;  // 0x715bd0

    Student* stu2 = new Student;
    stu2->PrintThis();     // 0x715bf0
    cout << stu2 << endl;  // 0x715bf0

    delete stu1;
    delete stu2;
}
~~~

可见， this 确实指向了*当前对象的首地址*，而且对于不同的对象， this 值也不同。

this 实际上是成员函数的一个形参，在调用成员函数时将*对象的地址*作为*实参*传递给 this。不过 this 这个形参是**隐式的**，它并不出现在代码中，而是在**编译阶段由编译器**默默地将它添加到参数列表中。

C++ 编译器在编译成员函数时，会隐式地为其添加一个名为 this 的参数，该参数是一个指向**调用该成员函数的对象**的指针。这个 this 指针允许成员函数访问该对象的成员变量和成员函数。 当一个成员函数被调用时，编译器会自动将对象的地址作为 this 指针传递给该成员函数。 通过 this 指针，成员函数可以访问对象的成员变量，从而实现成员函数与对象状态的关联。

## 理解：`this` 是隐式参数

可以把下面调用：
~~~cpp
obj.func(x);
~~~

近似理解成：

~~~cpp
func(&obj, x); // 第一个隐式参数就是 this
~~~
所以成员函数能访问对象状态，本质是*拿到了对象地址*。


## 类成员函数被编译成普通函数形式

- 非虚成员函数: 通常编译成与对象相关的函数，接收 this 指针作为隐式参数。 编译器优化可能使其看起来像全局函数调用，但本质上*仍然与对象相关*。
- 虚成员函数: 编译成与对象相关的函数，但通过虚函数表进行间接调用（即调用路径会经过*虚表分发*），以支持多态性。
- 静态成员函数：不依赖于任何对象实例，可以像全局函数一样直接调用。静态成员函数不接收 this 指针。不是类成员函数。


## this 更底层

对于类成员函数，编译器会生成类似于以下代码的指令：

~~~asm
; 假设 this 在寄存器 rdi，a 偏移 0，b 偏移 4

mov rax, [rdi + 0]  ; 将 a 的值加载到 rax 寄存器，即取 a
; ... (代码处理输出 a 的值) ...

mov rax, [rdi + 4]  ; 将 b 的值加载到 rax 寄存器，即取 b
; ... (代码处理输出 b 的值) ...
~~~

这段汇编代码展示了编译器如何使用 this 指针 (存储在 rdi 寄存器中) 来访问成员变量 a 和 b。 它直接通过*内存偏移量*访问成员变量。
