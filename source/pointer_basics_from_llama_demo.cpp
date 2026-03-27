#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory>

// 结合 llama 中的工程实践做指针基础演示：
// 1) 指针大小：工程里经常依赖 sizeof(void*) 判断平台位宽
// 2) free 后置空：miniaudio 中大量出现 free(ptr); ptr = NULL;
// 3) nullptr 语义：cpp-httplib 里有 operator==(std::nullptr_t)

static void free_and_null(int *& p) {
    // 对应工程实践：释放后立刻置空，避免悬空指针被误用
    std::free(p);
    p = nullptr;
}

void pick(int) {
    std::cout << "调用 int 重载\n";
}

void pick(int *) {
    std::cout << "调用 int* 重载\n";
}

// 模拟 httplib::Result 风格：判断“内部资源是否为空”
class ResultLike {
public:
    explicit ResultLike(int* res) : res_(res) {}

    // 允许写：if (obj == nullptr)
    // 左操作数是 *this, 右操作数是 nullptr
    //等价于： bool operator==(std::nullptr_t rhs) const，rhs用不到，只要声明类型即可 ***
    bool operator==(std::nullptr_t) const { return res_ == nullptr; }
    bool operator!=(std::nullptr_t) const { return res_ != nullptr; }

    // 允许写：if (obj)
    explicit operator bool() const { return res_ != nullptr; }

private:
    int* res_ = nullptr;
};


int main() {
    std::cout << "=== pointer basics from llama patterns ===\n";

    // 技术点1：指针大小与平台位宽相关
    std::cout << "sizeof(void*): " << sizeof(void*) << " bytes\n";
    std::cout << "sizeof(int*):  " << sizeof(int*) << " bytes\n";
    std::cout << "sizeof(std::shared_ptr<int>): " << sizeof(std::shared_ptr<int>) << " bytes\n\n";

    // 技术点2：野指针（未初始化指针）——只演示，绝不解引用
    int * wild; // 未初始化：值不确定，属于野指针
    (void) wild;
    std::cout << "wild pointer 已声明但未初始化（示例中不使用）\n";

    // 推荐做法：初始化为 nullptr
    int * safe = nullptr;
    std::cout << "safe == nullptr ? " << (safe == nullptr) << "\n\n";

    // 技术点3：悬空指针及规避
    int * p = (int *) std::malloc(sizeof(int));
    *p = 42;
    std::cout << "malloc value: " << *p << "\n";
    free_and_null(p); // free 后置空（防悬空）
    std::cout << "after free_and_null, p == nullptr ? " << (p == nullptr) << "\n\n";

    // 技术点4：nullptr 与重载解析 NULL有歧义
    pick(nullptr); // 明确空指针，匹配 int* 重载
    pick(0);       // 整数字面量，匹配 int 重载
    pick(static_cast<int>(NULL)); // 显式转 int，展示 NULL 常被当整数处理

    // 技术点5：“内部资源是否为空”判断
    int value = 7;
    ResultLike ok(&value);
    ResultLike bad(nullptr);
    std::cout << "ok == nullptr ? " << (ok == nullptr) << "\n";
    std::cout << "bad == nullptr ? " << (bad == nullptr) << "\n";
    std::cout << "if(ok) => " << (ok ? "true" : "false") << "\n";
    std::cout << "if(bad) => " << (bad ? "true" : "false") << "\n";

    return 0;
}

