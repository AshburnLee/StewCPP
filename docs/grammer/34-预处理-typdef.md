
# typedef
## typedef 和编译时的符号是什么关系？  [没关系]

在 C++ 中，`typedef` 声明不会直接影响编译生成的汇编代码或最终的可执行文件中的符号。`typedef` **仅仅是为已有的类型创建了一个别名，它只在编译器的预处理和语法分析阶段起作用，不会改变类型的底层表示**。***

让我们一步步分析：

1. 预处理阶段: 预处理器会处理源代码中的 `#include` 指令和宏定义，以及 `typedef` 声明。`typedef` 声明会将一个新的名字与已有的类型关联起来。例如： `typedef unsigned int uint;` 预处理器会将所有后续代码中出现的 `uint` 替换成 `unsigned int`。 这仅仅是**文本替换**，不会改变类型的本质。

2. 编译阶段: 编译器会将预处理后的代码转换成汇编代码。在这个阶段，**编译器已经知道** `uint` 是 `unsigned int` 的别名，它会根据 `unsigned int` 的类型信息生成相应的汇编指令。 生成的汇编代码中不会出现 `uint` 这个符号，而是 `unsigned int` 对应的机器码表示。

3. 链接阶段: 链接器会将多个目标文件（`.o` 文件）以及库文件链接成一个可执行文件。在这个阶段，**链接器处理的是符号**，例如函数名、全局变量名等。`typedef` 声明不会引入新的符号，因此它不会影响链接过程。***


## typedef [类型别名]： typedef to_be_renamed new_name

`typedef const struct my_graph_tensor *const_my_graph_tensor_t;` 表示什么？

typedef 关键字来定义了一个新的**类型别名** `const_my_graph_tensor_t`。该类型别名表示一个指向 `const struct my_graph_tensor` 结构体的常量指针.

具体来说，`const_my_graph_tensor_t`表示一个常量指针，指向结构体类型 `const struct my_graph_tensor`，在使用该类型时，指针所指向的数据是不可修改的（常量）。这种常量指针的使用可以提供一定程度的数据保护，防止在某些场景下修改数据。

---

定义类型别名的方式：
1. `typedef std::vector<int> IntVector;`
2. `using IntVector = std::vector<int>;`
3. `using ltw = logical_tensor_wrapper_t;`

使得在代码中使用更简洁的名称来表示类型。推荐使用 `using` 语法来定义类型别名，因为它提供了更好的可读性和与模板的兼容性


## 类型别名  [简化代码]

~~~cpp
typedef std::function<void(my::stream &,
        const std::vector<my::graph::tensor> &inputs,
        const std::vector<my::graph::tensor> &outputs)>
        perf_function_t;
~~~

上述代码使用 typedef 定义了一个名为 `perf_function_t` 的类型别名，它表示一个特定类型的 std::function 对象。该函数对象接受一个 `my::stream` 类型的引用和两个 `const std::vector<my::graph::tensor>` 类型的引用作为参数，返回值为 `void`。

应用场景：

- **当函数类型复杂**时，使用类型别名可以简化代码
- 如果**函数签名需要更改**，只需修改类型别名定义，而不需要修改所有使用该类型的代码
- 在需要传递或存储具有**相同签名的多个函数时**，使用类型别名可以确保接口的一致性
