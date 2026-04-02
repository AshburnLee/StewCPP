开发者可以在源码中通过许多手段与编译器“交流

## 1. 条件编译与宏（预处理）

#define / #if / #ifdef / #endif / #pragma

## 2. 立即生效的语义，属于c++的关键字

inline
constexpr
consteval
noexcept

explicit
override
final
virtual

alignas
thread_local
static

## 3. C++11+ 的属性

~~~cpp
// 调用者丢掉返回值时给出告警，提示“这个结果很重要”
[[nodiscard]]  // 编译器说：不要丢弃返回值
int compute_important() {
    return 123;
}
~~~

## 4. static_assert 

`static_assert(condition, "msg")`，编译器检查，不满足condition，就报错

## 5. 链接

- extern "C": 控制符号名与连接方式（目的是跨平台，与 C、CUDA C 兼容）

## 6. 可见性

llama.cpp 中通过 LLAMA_API 宏，来导出公共API 符号，让动态库对外提供C 接口
~~~cpp
#ifdef LLAMA_SHARED
#  define LLAMA_API __attribute__((visibility("default")))
#else
#  define LLAMA_API
#endif
~~~

或不适用宏: 

~~~cpp
__attribute__((visibility("default")))
void exported_func() {
    std::cout << "我在共享库符号表中可见\n";
}
~~~

KAQ：共享库里的符号默认是不是“可见”的？ 答：多平台默认定义成**普通全局函数/对象**就会被导出为“可见符号”。但实际中会“默认隐藏，按需导出”，所以有：

- `__attribute__((visibility("default")))`：显式导出
- `__attribute__((visibility("hidden")))`：显式隐藏

或通过编译选项 `-fvisibility=hidden` 把默认改成隐藏，再用 `__attribute__` 挑需要导出的。

KAQ：为什么要控制“可见性”？ 答：封装内部细节，减小动态符号表加速链接，避免冲突。

实例：

- 在《共享库中函数导出为公共API》中使用到
- llama 就用 `LLAMA_API/__attribute__((visibility("default")))` 来导出如 `llama_load_model_from_file` 这类函数。

## 7. 编译器专有内建

~~~cpp
GCC/Clang 内建函数 __builtin_expect（分支预测提示）
// llama / ggml 里常见 __builtin_expect 封装，用来标记“很可能 / 不太可能”
bool is_error(int code) {
    // 告诉编译器：code != 0 这条分支是“少见”的（unlikely）
    if (__builtin_expect(code != 0, 0)) {
        return true;
    }
    return false;
}
~~~

## 8. 编译器专属扩展

GCC pragma 控制告警（llama/vendor/miniaudio 有类似用法）
~~~cpp
// 关闭一小段代码的 unused-variable 告警
void pragma_demo() {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
    int x = 42;  // 正常会有“未使用变量”告警，这里被抑制
#pragma GCC diagnostic pop
}
~~~
