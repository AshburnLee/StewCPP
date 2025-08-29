## 通过宏创建   [error-handling]

~~~cpp
#define MY_GRAPH_SAFE(f, s) \
    do { \
        try { \
            f; \
        } catch (const my::error &e) { \
            if (s == CRIT || s == WARN) { \
                MY_PRINT(0, "error [%s:%d]: '%s' -> %s\n", \
                        __PRETTY_FUNCTION__, __LINE__, #f, e.what()); \
                fflush(0); \
                if (s == CRIT) exit(2); \
            } \
            return FAIL; \
        } \
    } while (0)
~~~

`MY_GRAPH_SAFE(c_partitions.emplace_back(partitions[i].compile(inputs, outputs, eng)), WARN);`
其中：
`do { ... } while (0)`: This is a common idiom used in macros to create a block of code that behaves like a single statement.

KAQ: 上述中的 e 没有通过参数传入，那么 e 是如被捕获的呢？

答：在C++中，异常捕获不仅可以通过显式的参数传递，还可以通过引用捕获异常对象。在你的代码中，异常对象 e 是通过引用捕获的。具体来说，这里使用了 `catch (const me::error &e)`，这表示**捕获一个类型为 `me::error` 的异常，而异常对象的引用被命名为 e。在捕获的过程中，系统将创建一个异常对象，然后通过引用传递给 e**。这种方式允许你在 `catch` 块中访问异常对象的信息，例如通过 `e.what()` 获取异常消息。所以，虽然在 GRAPH_SAFE 宏的定义中没有显式地传递异常对象 e，但是它通过引用捕获了异常，使得在 catch 块中能够访问异常的详细信息。

所以 e 对象的创建其实是通过继承 `std::exception` 实现的：

~~~cpp
struct error : public std::exception {
    my_status_t status;
    const char *message;

    /// Constructs an instance of an exception class.
    ///
    /// @param status The error status returned by a C API function.
    /// @param message The error message.
    error(my_status_t status, const char *message)
        : status(status), message(message) {}

    /// Returns the explanatory string.
    const char *what() const noexcept override { return message; }

    /// A convenience function for wrapping calls to C API functions. Checks
    /// the return status and throws an my::error in case of failure.
    ///
    /// @param status The error status returned by a C API function.
    /// @param message The error message.
    static void wrap_c_api(my_status_t status, const char *message) {
        if (status != my_success) MY_THROW_ERROR(status, message);
    }
};
~~~

KAQ: `error &e` 的实现是需要继承自 `std::exception` 吗？

答：异常类并不一定非要继承自 `std::exception`。然而，**继承自 std::exception 是一种良好的实践**，因为它是 C++ 标准库中异常体系结构的基类，提供了一些通用的异常处理功能。

如果你的 `me::error` 类继承自 `std::exception`，它可以从 `std::exception` 继承的成员函数，例如 `what()`，以提供关于异常的描述信息。这对于在捕获异常时获取有用的错误消息是很方便的。


## 异常类 std::exception [接口类]

这个接口类 提供了一个统一的接口来处理各种类型的异常。使用 `std::exception` 及其派生类可以使你的代码更加健壮和可维护。子类可以重写 `what()` 方法来提供更详细的错误描述。

- 所有标准异常类都继承自 `std::exception`，这使得你可以使用一个通用的 catch 块来捕获和处理不同类型的异常。
- 通过使用 `std::exception` 及其派生类，你可以**利用多态性**来处理不同类型的异常。
- `std::exception` 类提供了一个虚函数 `what()`，返回一个描述异常的 C 风格字符串。派生类可以重载这个函数，提供更具体的异常信息。
- 注意 `std::exception` 只能捕获**运行时错误**，编译时错误不适用。

~~~cpp
#include <exception>
#include <string>

class AnimalAlreadyExistsException : public std::exception {
public:
    AnimalAlreadyExistsException(const std::string& name) : name(name) {}

    const char* what() const noexcept override {
        return ("Animal " + name + " already exists in the zoo").c_str();
    }

private:
    std::string name;
};

#include <set>
#include <string>

class Zoo {
public:
    void addAnimal(const std::string& name) {
        if (animals.find(name) != animals.end()) {
            throw AnimalAlreadyExistsException(name);
        }
        animals.insert(name);
    }

private:
    std::set<std::string> animals;
};

int main() {
    Zoo zoo;
    try {
        zoo.addAnimal("Lion");
        zoo.addAnimal("Lion");  // 这将抛出一个异常
    } catch (const AnimalAlreadyExistsException& e) {  // 如果捕获异常，会在将其保存在e中
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
~~~

上述是自定义的异常派生类，标准库中提供了其他的派生类，可用

`override` 表示重写了基类中的虚函数，表示这是个覆盖函数。此情况下推荐使用。

## c++ 中的 exit 函数是什么？与异常处理有什么关系？[不使用exit，使用异常处理]

在C++中，exit 函数是一个用于立即终止程序的函数，它是由C标准库提供的。当调用 exit 函数时，程序将立即停止执行，并返回一个状态码给操作系统.

~~~cpp
#include <cstdlib> // 包含exit函数

int main() {
    // ... 一些代码 ...

    if (/* 某些错误条件 */) {
        exit(EXIT_FAILURE); // 立即终止程序，并返回一个失败状态码
    }

    // ... 更多代码 ...
    return 0; // 正常结束程序
}
~~~

然而，exit 函数与 C++ 的异常处理机制有一个重要的区别：当调用 exit 函数时，当前作用域中的对象不会被析构。这意味着如果你的程序使用了 RAII（Resource Acquisition Is Initialization）模式来管理资源（例如，使用智能指针来管理动态分配的内存），那么这些资源可能不会被正确释放。

相比之下，当抛出一个异常时，**C++ 会确保所有在异常被抛出的作用域中创建的对象都会被正确析构**。这就是为什么在C++中，通常推荐使用异常来处理错误，而不是使用exit函数。

