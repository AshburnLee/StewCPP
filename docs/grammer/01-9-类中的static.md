## static 在类中

### 1. 静态成员变量：属于类，不属于对象

静态成员变量只有一份，所有对象共享。  
典型用途：计数器、全局配置、缓存命中统计。

~~~cpp
class Student {
public:
    Student() { ++m_total; }
    static int get_total() { return m_total; }

private:
    static int m_total;
};

int Student::m_total = 0; // C++17 之前常见写法
~~~

原理要点：

- 普通成员跟对象走（对象创建时存在，对象销毁时释放）。
- 静态成员变量不在对象里，位于*静态存储区*，生命周期通常是整个程序运行期。
- 因为不属于对象，所以可用 `Student::m_total` 访问。



### 2. 初始化规则（重点）

- **C++17 前**：`static` 数据成员通常要在类外定义一次。  
  `int Student::m_total = 0;`
- **C++17 起**：可用 `inline static` 在类内初始化。  
  `inline static int m_total = 0;`

补充：

- `static const` 整型常量在某些场景可类内给初值（历史规则），现代代码更推荐 `inline static`。

---

### 3. 静态成员函数：没有 this

静态成员函数不绑定对象，所以没有 `this`。  
它最适合表达*和类整体相关，而非某个对象相关*的行为。***

~~~cpp
class Student {
public:
    static int get_total() { return m_total; } // static 函数只能访问静态成员

private:
    static int m_total;
    int age = 0;
};
~~~

原理要点：

- 普通成员函数有隐式 `this`，可访问对象状态。
- 静态成员函数无 `this`，不能直接访问非静态成员变量/函数。
- 静态成员函数也不能是 `virtual`（虚函数机制依赖类对象与 `this`）。



### 4. 函数内 static

函数内 `static` 变量：

~~~cpp
void foo() {
    int n = 0;        // 每次调用重置
    static int m = 0; // 只初始化一次，跨调用保留
    ++n;
    ++m;
}
~~~

这类 `m` 不是类成员，函数内可见，声明周期是*静态存储期*（即程序启动后存在，到程序结束才销毁）



### 5. 静态成员函数 vs 文件内 static 函数

- 文件内 `static` 函数：强调**内部链接**，仅当前 `.cpp` 可见。
- `class` 里的 `static` 成员函数：强调**属于类且无 this**，用 `ClassName::func()` 调用。

两者都“不依赖类对象”，但语义层面不同：  一个是*链接可见性*概念，一个是类成员语义概念。



## 关键点速记

- 静态成员变量：类共享、对象外存储、程序期生命周期。
- 静态成员函数：无 `this`，只直接操作静态成员。
- 初始化：C++17 前类外定义；C++17 起优先 `inline static`。
- 区分概念：类内 `static`（成员语义） vs 文件内 `static`（内部链接）。
