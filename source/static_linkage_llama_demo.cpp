#include <cstddef>
#include <iostream>

// =============================================================================
// 1) static 全局常量（内部链接）
// 场景：本 .cpp 负责「字节数 → MiB」等换算，Ki/Mi 只在这一份实现里用。
// 为何 static：避免在全局命名空间扔 KiB/MiB，防止别的 .cpp 也定义同名宏/常量时冲突；
//             调用方只通过 to_mib() 拿结果，不需要、也不该依赖你的「除数到底是多少」。
// =============================================================================
static const std::size_t Ki = 1024;
static const std::size_t Mi = Ki * Ki;
// 对外
std::size_t to_mib(std::size_t bytes) {
    return bytes / Mi;
}

// =============================================================================
// 2) static 全局函数（内部链接）
// 场景：加载模型要很多小步骤（读魔数、校验、读索引…），名字在工程里很常见（parse、read_hdr…）。
// 为何 static：这些符号不必、也不该给其他 .cpp 用；另一份 .cpp 里同样可以 static bool parse()
//             互不冲突。对外只保留一个「是否加载成功」的入口（类比 llama_load_model_from_file）。
// =============================================================================
static bool rd_magic() {
    return true;
}

static bool rd_index() {
    return true;
}

// 对外
bool model_ok() {
    return rd_magic() && rd_index();
}

// =============================================================================
// 3) static 函数 + static 全局「接口表」（内部链接的函数指针聚合）
// 场景：解码循环里要统一调用「某一种 sampler」（temperature / top-k …），用同一套 void(*apply)(...) 调用。
// 为何 static：apply_temp、apply_wrap、g_tbl 都不导出；只有 step() 暴露。表在 .o 里一份，
//             不占「全程序可见符号」，
// =============================================================================
struct Tmp {
    float temp;
};

static void apply_t(void* ctx, float* v, int n) {
    // static_cast 把「无类型指针」转成「指向 Tmp 的指针」
    // 编译时 行为，检查转换的可行性
    auto* t = static_cast<Tmp*>(ctx);
    if (t->temp <= 0.f) {
        return;
    }
    for (int i = 0; i < n; ++i) {
        v[i] /= t->temp;
    }
}

static void bridge(void* ctx, float* v, int n) {
    apply_t(ctx, v, n);
}

struct Slot {
    void (*run)(void*, float*, int);
};

static Slot g_tbl = { bridge };

void step(void* ctx, float* logits, int n) {
    g_tbl.run(ctx, logits, n);
}

// =============================================================================
// 4) 匿名命名空间（与文件 static 等价的内部链接习惯）
// 场景：词表查找前要做「规范化」（去空格、小写），只服务于本文件的 lookup()。
// 为何用匿名 namespace：把 norm()、桶函数等整坨「实现细节」包在一起，比给每个函数写 static 更整齐；
//             主推理树里 ggml 子树常见此写法（如 sgemm 周边）。
// =============================================================================
// 对内，只服务于本文件的 lookup_stub
namespace {
const char* norm(const char* w) {
    return (w && w[0]) ? w : "(empty)";
}

unsigned mix(const char* s) {
    unsigned h = 0;
    for (const char* p = s; *p; ++p) {
        // 编译时 做类型转换的可行性检查
        h = h * 31u + static_cast<unsigned char>(*p);
    }
    return h;
}
} // namespace

// 对外
int lookup_stub(const char* word) {
    const char* k = norm(word);
    // 转换从 unsigned 到 int
    return static_cast<int>(mix(k) % 10000);
}

// =============================================================================
int main() {
    // 1) 打印「张量占了多少 MiB」—— 调用方不关心 Mi 常量是否导出
    const std::size_t blob = 500u * Mi;
    std::cout << "[1] tensor bytes=" << blob << " -> " << to_mib(blob) << " MiB (only to_mib is public)\n";

    // 2) 加载 —— 多步 static，对外一句 model_ok
    std::cout << "[2] model_ok=" << (model_ok() ? "yes" : "no") << " (rd_* hidden in this .cpp)\n";

    // 3) 采样一步 —— 表驱动，实现符号不污染全局
    Tmp z{ 2.f };
    float L[] = { 1.f, 4.f };
    step(&z, L, 2);
    std::cout << "[3] logits after step: " << L[0] << " " << L[1] << " (expect 0.5 2)\n";

    // 4) 查找 —— norm/mix 不外泄
    std::cout << "[4] lookup(\"hello\")=" << lookup_stub("hello") << " (norm/mix in anon ns)\n";

    return 0;
}
