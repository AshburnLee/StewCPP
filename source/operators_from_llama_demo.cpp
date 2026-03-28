// 工程常见运算符重载汇总（单文件演示），并对照 llama 仓库里的写法。
// 编译：cmake --build build --target operators_from_llama_demo.junhui
//
// llama 中的实例（可打开对照）：
// - llama/src/llama-arch.h
//   LLM_TN_IMPL：operator std::string()、friend operator== / !=（左侧 std::string）
//   LLM_TN：重载 operator() 生成 LLM_TN_IMPL（工厂/命名习惯）
// - llama/tools/server/utils.hpp server_tokens
//   operator[]（const / 非 const）、= delete 拷贝赋值、= default 移动
// - llama/src/llama-sampling.cpp probs_iterator
//   ==、!=、*、前置++/后置++（与 std::discrete_distribution 配合）
// - llama/vendor/minja/minja.hpp Value
//   比较、算术、一元 -、hash 用 operator()
// - llama/vendor/cpp-httplib/httplib.h
//   operator*、operator->（类似智能指针）、operator<<、与 nullptr 比较
// - llama/tests/test-chat.cpp：全局 operator<< 打日志

#include <cstddef>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

//  1) 算术 + 比较 + 输出
struct Vec2 {
    double x, y;

    Vec2 operator+(const Vec2& o) const { return { x + o.x, y + o.y }; }
    Vec2 operator-(const Vec2& o) const { return { x - o.x, y - o.y }; }
    Vec2 operator-() const { return { -x, -y }; }
    Vec2& operator+=(const Vec2& o) {
        x += o.x;
        y += o.y;
        return *this;
    }

    bool operator==(const Vec2& o) const { return x == o.x && y == o.y; }
    bool operator!=(const Vec2& o) const { return !(*this == o); }

    // ?
    friend std::ostream& operator<<(std::ostream& os, const Vec2& v) {
        return os << "(" << v.x << ", " << v.y << ")";
    }
};

//  2) 下标 []：非 const 须返回引用才能 ts[i] = x（按值返回 int 则 ts[i] 是右值，不能赋值）
struct TokenSpan {
    std::vector<int> tokens;

    int& operator[](size_t i) { return tokens[i]; }
    const int& operator[](size_t i) const { return tokens[i]; }
};

//  3) 模拟“句柄”：* 、-> 、bool
struct IntBox {
    int v;
    explicit IntBox(int n) : v(n) {}
};

class IntHandle {
    IntBox* p;

public:
    explicit IntHandle(IntBox* q) : p(q) {}
    IntBox& operator*() const { return *p; }
    IntBox* operator->() const { return p; }
    explicit operator bool() const { return p != nullptr; }
};

//  4) 函数调用 operator()：工厂 / functor
struct TagMaker {
    std::string prefix;

    std::string operator()(const char* name) const { return prefix + std::string(name); }
    std::string operator()(const char* name, int id) const {
        return prefix + std::string(name) + "_" + std::to_string(id);
    }
};

struct LessByFirst {
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const {
        return a.first < b.first;
    }
};

//  5) 左侧非本类型：friend ==
struct Label {
    std::string s;
    explicit Label(std::string t) : s(std::move(t)) {}
    std::string str() const { return s; }
    
    // 必须是 friend，类成员不能实现 string == Label.s 
    friend bool operator==(const std::string& left, const Label& right) { return left == right.s; }
    friend bool operator!=(const std::string& left, const Label& right) { return left != right.s; }
};

//  6) 简易迭代器：==、!=、*、++（llama probs_iterator）
struct IntIter {
    const int* data;
    bool operator==(const IntIter& o) const { return data == o.data; }
    bool operator!=(const IntIter& o) const { return data != o.data; }
    const int& operator*() const { return *data; }
    IntIter& operator++() {
        ++data;
        return *this;
    }
    IntIter operator++(int) {
        IntIter t = *this;
        ++data;
        return t;
    }
};

//  7) 哈希用 operator()（unordered_map / minja Value hash）
struct PairHash {
    std::size_t operator()(const std::pair<std::string, std::string>& p) const noexcept {
        return std::hash<std::string>()(p.first) ^ (std::hash<std::string>()(p.second) << 1);
    }
};

//  8) 拷贝赋值 + 移动赋值（深拷贝资源时手写；此处演示自赋值与 Rule of 3/5 思想）
class Buffer {
    int* m_ptr;
    size_t m_len;

public:
    Buffer() : m_ptr(nullptr), m_len(0) {}
    explicit Buffer(size_t n) : m_ptr(new int[n]()), m_len(n) {}
    ~Buffer() { delete[] m_ptr; }

    // 拷贝构造（深拷贝堆数组）
    Buffer(const Buffer& o) : m_ptr(o.m_len ? new int[o.m_len] : nullptr), m_len(o.m_len) {
        if (m_len) {
            std::memcpy(m_ptr, o.m_ptr, m_len * sizeof(int));
        }
    }
    // 拷贝赋值（先释放再按 o 深拷贝）
    Buffer& operator=(const Buffer& o) {
        if (this == &o) {
            return *this;
        }
        delete[] m_ptr;
        m_len = o.m_len;
        m_ptr = m_len ? new int[m_len] : nullptr;  // 先 new，再写入
        if (m_len) {
            std::memcpy(m_ptr, o.m_ptr, m_len * sizeof(int));
        }
        return *this;  // 支持链式拷贝
    }

    // 移动拷贝
    Buffer(Buffer&& o) noexcept : m_ptr(o.m_ptr), m_len(o.m_len) {
        o.m_ptr = nullptr;
        o.m_len = 0;
    }
    // 移动赋值
    Buffer& operator=(Buffer&& o) noexcept {
        if (this == &o) {
            return *this;
        }
        delete[] m_ptr;
        m_ptr = o.m_ptr;
        m_len = o.m_len;
        o.m_ptr = nullptr;
        o.m_len = 0;
        return *this;
    }

    int& operator[](size_t i) { return m_ptr[i]; }
    size_t size() const { return m_len; }
};

//  9) 类型转换运算符（文档中的 operator double；此处用 explicit bool 更符合现代习惯）
struct Flag {
    bool on;
    explicit operator bool() const { return on; }
};

int main() {
    Vec2 a{ 1, 2 }, b{ 3, 4 };
    std::cout << "Vec2: " << (a + b) << " " << (-a) << " eq? " << (a == a) << "\n";

    TokenSpan ts;
    ts.tokens = { 10, 20, 30 };
    ts[1] = 99;
    std::cout << "TokenSpan [1] " << ts.tokens[1] << " const ref " << static_cast<const TokenSpan&>(ts)[2] << "\n";

    IntBox box(42);
    IntHandle h(&box);
    if (h) {
        std::cout << "Handle ->v " << h->v << " *v " << (*h).v << "\n";
    }

    TagMaker mk{ "tn_" };
    std::cout << "TagMaker " << mk("w") << " " << mk("b", 2) << "\n";

    Label L("hello");
    std::cout << "Label friend== " << (std::string("hello") == L) << "\n";

    int arr[] = { 1, 2, 3 };
    IntIter it{ arr }, end{ arr + 3 };
    int s = 0;
    for (; it != end; ++it) {
        s += *it;
    }
    std::cout << "IntIter sum " << s << "\n";

    std::unordered_map<std::pair<std::string, std::string>, int, PairHash> um;
    um[{ "a", "b" }] = 7;
    std::cout << "PairHash map " << um[{ "a", "b" }] << "\n";

    std::map<std::pair<int, int>, int, LessByFirst> m;
    m[{ 2, 0 }] = 1;
    m[{ 1, 9 }] = 2;
    std::cout << "map begin key " << m.begin()->first.first << "\n";

    Buffer buf1(2);
    buf1[0] = 5;
    Buffer buf2;
    buf2 = buf1;
    Buffer buf3 = std::move(buf2);
    std::cout << "Buffer buf3[0] " << buf3[0] << " size " << buf3.size() << "\n";

    Flag f{ true };
    std::cout << "explicit bool " << (f ? 1 : 0) << "\n";

    return 0;
}
