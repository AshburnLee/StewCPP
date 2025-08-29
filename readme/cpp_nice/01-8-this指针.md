

### this 指针到底是啥

`this` 是**一个 const 指针**，它指向当前的对象，通过它可以访问当前对象的所有成员。当前对象就是指正在使用的对象，比如`student1.show()`，`student1` 就是当前对象，`this`指向`student1`。this**只能用在类的内部**，通过 this 可以访问类的**所有成员**，包括private\protected\public属性。

注意， this 是个指针，需要使用`->`来访问成员变量和成员函数。

this 虽然用在类内部，但是**只有在创建了对象后，this 才会被被编译器赋值。所以 this 是不存在于 static 成员函数里的，**

~~~cpp
class Student {
public:
    void GetName(char* name);
    void GetAge(int age);
    void PrintThis();
private:
    char* m_name;
    int m_age;
};

void Student::GetName(char* name) {
    this->m_name = name;
}
void Student::GetAge(int age) {
    this->m_age = age;
}

void Student::PrintThis() {
    std::cout << this << std::endl;
}

int main () {
    Student* stu1 = new Student;
    // this 确实指向了当前对象的首地址
    stu1->PrintThis();
    cout << stu1 << endl;

    // 对于不同的对象， this值不同
    Student* stu2 = new Student;
    stu2->PrintThis();
    cout << stu2 << endl;
}
~~~

运行结果：

~~~bash
0x715bd0
0x715bd0
0x715bf0
0x715bf0
~~~

可见， this 确实指向了当前对象的首地址，而且对于不同的对象， this 值也不同。

this 实际上是成员函数的一个形参，**在调用成员函数时将对象的地址作为实参传递给 this**。不过 this 这个形参是**隐式的**，它并不出现在代码中，而是在**编译阶段由编译器**默默地将它添加到参数列表中。

C++ 编译器在编译成员函数时，会隐式地为其添加一个名为 this 的参数，该参数是一个指向**调用该成员函数的对象**的指针。这个 this 指针允许成员函数访问该对象的成员变量和成员函数。 当一个成员函数被调用时，编译器会自动将对象的地址作为 this 指针传递给该成员函数。 通过 this 指针，成员函数可以访问对象的成员变量，从而实现成员函数与对象状态的关联。


## 类成员函数被编译成与类无关的函数？错：  [类成员函数隐式接受this]

- 非虚成员函数: 通常编译成与对象相关的函数，接收 this 指针作为隐式参数。 编译器优化可能使其看起来像全局函数调用，但本质上仍然与对象相关。
- 虚成员函数: 编译成与对象相关的函数，但通过虚函数表进行间接调用，以支持多态性。
- 静态成员函数：不依赖于任何对象实例，可以像全局函数一样直接调用。静态成员函数不接收 this 指针。不是类成员函数。

## this

对于类成员函数，编译器会生成类似于以下代码的指令：

~~~asm
; 假设 a 和 b 分别在对象内存偏移量 0 和 4 处
; 并且 this 指针存储在寄存器 `rdi` 中

mov rax, [rdi + 0]  ; 将 a 的值加载到 rax 寄存器
; ... (代码处理输出 a 的值) ...

mov rax, [rdi + 4]  ; 将 b 的值加载到 rax 寄存器
; ... (代码处理输出 b 的值) ...
~~~

这段汇编代码展示了编译器如何使用 this 指针 (存储在 rdi 寄存器中) 来访问成员变量 a 和 b。 它直接通过内存偏移量访问成员变量。
