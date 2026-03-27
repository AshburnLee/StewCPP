#include <iostream>
#include <string>

// 参考 llama 的工程用法：
// 1) extern 变量声明（如 common/common.h 里的 LLAMA_BUILD_NUMBER / LLAMA_COMMIT）
// 2) extern "C" 接口（如 include/llama.h / ggml/*.h 对外 C ABI）
//
// 3个用法：
// - extern 声明：告诉编译器“定义在别处”
// - 真正定义：只出现一次，负责分配存储
// - extern "C"：导出 C 风格符号，便于跨语言调用

// ---------- extern 变量声明区（模拟头文件） ----------
extern int g_decode_threads;           // 声明：不分配内存
extern const char * g_model_family;    // 声明：不分配内存

// 多次 extern 声明是允许的（仍不分配内存）
extern int g_decode_threads;
extern int g_decode_threads;
extern int g_decode_threads;

// ---------- extern "C" 接口声明区（模拟对外 API 头文件） ----------
extern "C" int inference_score_c_api(int token_id, float logit);

// ---------- extern 变量定义区（模拟某个 .cpp 的定义） ----------
int g_decode_threads = 8;              // 定义：分配内存
const char * g_model_family = "llama-like";

// ---------- extern "C" 接口定义 ----------
extern "C" int inference_score_c_api(int token_id, float logit) {
    // 这里用一个简单规则模拟“推理打分接口”
    return (token_id % 2 == 0 && logit > 0.0f) ? 1 : 0;
}

static void run_inference_step(int token_id, float logit) {
    // 使用 extern 变量（来自“全局配置”）
    std::cout << "[infer] model=" << g_model_family
              << ", threads=" << g_decode_threads
              << ", token=" << token_id
              << ", logit=" << logit << "\n";

    // 使用 extern "C" 接口（对齐 llama 的 C ABI 风格）
    int ok = inference_score_c_api(token_id, logit);
    std::cout << "  c_api score pass? " << ok << "\n";
}

int main() {
    std::cout << "=== extern keypoints from llama inference style ===\n";

    run_inference_step(128, 0.42f);

    // 修改 extern 全局配置：各处共享同一份数据
    g_decode_threads = 16;
    run_inference_step(129, -0.05f);

    return 0;
}

