## 静态成员变量

有时候我们希望在多个对象之间共享数据，对象 a 改变了某份数据后对象 b 可以检测到。共享数据的典型使用场景是计数，以前面的 Student 类为例，如果我们想知道班级中共有多少名学生，就可以设置一份共享的变量，每次创建对象时让该变量加 1。

~~~cpp
class Student{
public:
    Student(char *name, int age, float score);
    void show();
public:
    static int m_total;  //静态成员变量
private:
    char *m_name;
    int m_age;
    float m_score;
};
~~~

代码声明了一个静态成员变量 m_total，用来统计学生的人数。

**static 成员变量属于类，不属于某个具体的对象**，即使创建多个对象，也只为 m_total 分配一份内存，所有对象使用的都是这份内存中的数据。当某个对象修改了 m_total，也会影响到其他对象。

static 成员变量必须在类声明的外部初始化【C++17之前】，具体形式为： `int Student::m_total = 0;` 静态成员变量在初始化时不能再加 static。

C++17 之后，有其他初始化方式：C++17 引入了 inline 关键字，允许在类体内直接初始化静态成员变量，避免了类体外初始化的麻烦。 这使得代码更简洁易读。`static inline int counter = 0; // C++17 支持在类体内直接初始化`

注意：static 成员变量的内存既不是在声明类时分配，也不是在创建对象时分配，而是在（类外）初始化时分配。反过来说，没有在类外初始化的 static 成员变量不能使用。

`static` 成员变量**既**可以通过对象来访问，**也**可以通过类来访问。

注意：static 成员变量不占用对象的内存，而是在所有对象之外开辟内存，即使不创建对象也可以访问。具体来说，static 成员变量和普通的 static 变量类似，都在内存分区中的全局数据区分配内存。


几点说明：

1. static 成员变量和普通 static 变量一样，都在内存分区中的**全局数据区（数据段，不在stack和heap上）**分配内存，到程序结束时才释放。这就意味着，static 成员变量不随对象的创建而分配内存，也不随对象的销毁而释放内存。而普通成员变量在对象创建时分配内存，在对象销毁时释放内存。
2. 一个类中可以有一个或多个静态成员变量，所有的对象都共享这些静态成员变量，都可以引用它。
3. 静态成员变量必须初始化，而且只能在类体外（.cpp中）进行。【C++17之前】。初始化时可以赋初值，也可以不赋值。如果不赋值，那么会被默认初始化为 0。全局数据区的变量都有默认的初始值 0，而动态数据区（堆区、栈区）变量的默认值是不确定的，一般认为是垃圾值。
4. 静态成员变量既可以通过对象名访问，也可以通过类名访问，但要遵循 private、protected 和 public 关键字的访问权限限制。如果是private的静态成员，那么通过对象不能访问【更多相关，hold】


## 静态成员函数

静态成员函数的主要目的是访问静态成员。最佳实践，**常用于执行与类本身相关的操作，而不是与特定对象实例相关的操作**。

普通成员函数可以访问所有成员（包括成员变量和成员函数），静态成员函数**只能**访问静态成员。原理：

编译器在编译一个**普通成员函数时**，会**隐式地增加一个形参 this**，并把当前对象的地址赋值给 this，所以普通成员函数只能在创建对象后通过对象来调用，因为它需要当前对象的地址。而静态成员函数可以通过类来直接调用，编译器不会为它增加形参 this，它不需要当前对象的地址，所以不管有没有创建对象，都可以调用静态成员函数。

普通成员变量占用对象的内存，静态成员函数没有 this 指针，不知道指向哪个对象，进而无法访问对象的成员变量。所以说静态成员函数不能访问普通成员变量，只能访问静态成员变量。 ***

静态成员函数与普通成员函数的根本区别在于：普通成员函数有 this 指针，可以访问类中的任意成员；而静态成员函数没有 this 指针，只能访问静态成员（包括静态成员变量和静态成员函数）。

例：

~~~cpp
class Student2{
public:
	Student2(char *name, float score);
	void Show();
public:  // 声明静态成员函数
	static int getTotal();
	static float getPoints();
private:
	static int m_total;  //总人数
	static float m_points;  //总成绩
private:
	char *m_name;
	int m_age;
	float m_score;
};

int Student2::m_total = 0;
float Student2::m_points = 0.0;
Student2::Student2(char *name, float score): m_name(name), m_score(score) {
	m_total++;
	m_points += score;
}
void Student2::Show(){
	cout << m_name <<" age is: "<< m_age <<", score: "<< m_score << endl;
}
//定义静态成员函数
int Student2::getTotal(){
	return m_total;
}
float Student2::getPoints(){
	return m_points;
}

void TestStudent2() {
	(new Student2("Zve", 90.6)) -> Show();
	(new Student2("Coco", 80.5)) -> Show();
	(new Student2("Swiatech", 99.0)) -> Show();
	// 总人数和总分数不属于任何一个对象
	int total = Student2::getTotal();
	float points = Student2::getPoints();
	cout << "There are: " << total << " students. "<< "the average score is: " <<
	points/total << endl;
}
~~~

静态成员函数的主要目的是访问静态成员。`getTotal()`、`getPoints()` 当然也可以声明为普通成员函数，但是它们都只对静态成员进行操作，加上 `static` 语义更加明确。

和静态成员变量类似，静态成员函数在声明时要加 `static`，在定义时不能加 `static`。静态成员函数可以通过类来调用（一般都是这样做），也可以通过对象来调用。


## static 在类中的使用

static 修饰类中的变量和方法

修饰后的特点：类实例间共享，属于类而不属于具体对象

static 成员方法用于读取 static 成员变量

具体讲：

1. 不能类内初始化 `static` 类成员属性，需在类外初始化
2. `const` 修饰的 `static`类成员属性可以在类内初始化
3. 访问 `static` 类成员属性，可直接用`className::b`
4. `static` 成员属性 在所有类实例间共享
5. `static` 类方法要访问类属性，也只能访问`static`类属性，因其没有 this
6. `static` 成员函数不能用 `virtual` 修饰。`static` 成员不属于类，而 `virtual` 修饰类成员函数 ***
7. `static` 成员函数的应用场景是啥？比如统计程序中一共有多少个该类的实例化对象

见实例：

~~~cpp
class StaticObj {
public:
    int a = 1;
    //static int b = 2; // 1). 编译报错 不能类内初始化
    static int b;
    static const int c = 3;  // 2). const 修饰就可以类内初始化
    StaticObj() { b++; };  // 7). 每构造一个该类对象，b++，用于记录类对象的个数
    int GetB() {return b;}

    // static int GetBs() {return a;} // 6). static函数中只能用static类变量
    static int GetBs() { return b;}  // 返回类对象个数
};

int StaticObj::b = 2;  // 5). 只能在类声明外初始化

void TestStaticClass() {

    // std::cout<<"StaticObj::a: "<<StaticObj::a<<std::endl; // 3). error
    std::cout<<"StaticObj::b: "<<StaticObj::b<<std::endl;
    std::cout<<"StaticObj::c: "<<StaticObj::c<<std::endl;
    // ----------------------------------------

    StaticObj s1;  // b = 3
    cout<<s1.GetB()<<"\n";
    StaticObj s[3];  // b = 6
    StaticObj s2;    // b = 7
    cout<<s2.GetB()<<"\n"; // 4). 所有类实例间共享
    // ----------------------------------------

}
~~~

## static 修飾一般变量

修饰一般变量时，该变量为全局变量，见下段代码中的 `m`：

~~~cpp
// static 修饰一般变量
void _func() {
    int n = 0;
    static int m = 0;
    n++;
    m++;
    printf("non static: %zd\n", n);
    printf("static: %zd\n", m);
}

void TestStaticVar() {
    for (int i=0 ;i<5; ++i) {
        _func();
    }
}
~~~


## 静态成员函数 VS 静态函数  [hold]

静态函数 的作用域是当前源文件，静态成员函数 的作用域是这个类。
