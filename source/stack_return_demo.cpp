// 对比：返回指向局部栈数组的指针（错误）与安全写法。
// 编译：在 StewCPP 下 cmake --build build --target stack_return_demo.junhui
//       ASan 更容易在解引用悬空指针时立刻报错。

#include <cstring>
#include <iostream>
#include <memory>
#include <string>

// ---------- 错误写法（返回后 strs 已失效，指针悬空）----------
char* bad_init() {
    char strs[] = "Hi, there";  // 局部自动存储期数组，位于当前函数栈帧
    char* ptr = strs;           // ptr 指向上述栈上内存的首地址
    return ptr;         // 错误：返回后 strs 生命周期结束，ptr 成为悬空指针，指向的内容已被释放
}

// ---------- 修正 1：按值返回 std::string（推荐）----------
std::string good_init_string() {
    return std::string("Hi, there");
}

// ---------- 修正 2：返回字符串字面量指针（生命周期贯穿程序）----------
// 注意：返回的是字面量，不是局部数组副本。
const char* good_init_literal() {
    return "Hi, there";
}

// ---------- 修正 3：动态分配 + 调用方负责释放（或改用 unique_ptr）----------
// 注意：不能在函数内 delete[] p——否则返回悬空指针；须由接收返回值的调用方 delete[]（与 new[] 配对）。
char* good_init_heap() {
    char* p = new char[16];   // 在堆上分配；所有权随返回值转移给调用方
    std::strcpy(p, "Hi, there");
    return p;             // 不在此处释放；见 main 中 delete[] heap
}

// ---------- 修正 4：unique_ptr<char[]>，所有权随对象移动，作用域结束自动 delete[] ----------
std::unique_ptr<char[]> good_init_heap_unique() {
    auto p = std::make_unique<char[]>(16);
    std::strcpy(p.get(), "Hi, there");
    return p;
}

int main() {
    std::cout << "=== 1) 错误 bad_init（解引用为 UB，仅作教学，勿在生产依赖行为）===\n";
    char* dangling = bad_init();
    // 下面一行在 ASan 下常会报 heap-use-after-free / stack-use-after-return
    std::cout << "dangling read (UB): ";
    // 无 Sanitizer 时可能“碰巧”还能打印
    // 实际输出：dangling read (UB): Hi, therз▒
    std::cout << (dangling ? dangling : "(null)") << "\n";

    std::cout << "\n=== 2) 修正 std::string ===\n";
    std::string s = good_init_string();
    std::cout << s << "\n";

    std::cout << "\n=== 3) 修正 字面量指针 ===\n";
    const char* lit = good_init_literal();
    std::cout << lit << "\n";

    std::cout << "\n=== 4) 修正 new + delete ===\n";
    // heap 与当时的 p 指向同一块堆内存, 将p中内容拷贝给 heap，指向同一块内存
    char* heap = good_init_heap(); 
    std::cout << heap << "\n";
    delete[] heap;  // 在此 delete[]

    std::cout << "\n=== 5) 修正 unique_ptr（无需手动 delete）===\n";
    std::unique_ptr<char[]> up = good_init_heap_unique();
    std::cout << up.get() << "\n";

    return 0;
}
