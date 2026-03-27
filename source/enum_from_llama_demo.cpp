#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// LLM 推理相关 enum 技术点（对应 llama 常见工程写法）：
// 1) enum 为整数值命名（如 server task / stop type）
// 2) switch(enum) -> 文本（如 server.cpp 的 stop_type_to_str）
// 3) enum class 强类型 + 作用域隔离
// 4) enum 作为 unordered_map key（自定义 hash，跨标准更稳）
// 5) 位标志按位组合与判断（&）

// 技术点1：传统 enum（与 C API / 旧代码兼容性好）
enum StopType {
    STOP_EOS   = 0,
    STOP_WORD  = 1,
    STOP_LIMIT = 2,
};

// 技术点2：switch(enum) 做文本映射（贴近 llama server 写法）
static const char* stop_type_to_str(StopType t) {
    switch (t) {
        case STOP_EOS:   return "eos";
        case STOP_WORD:  return "word";
        case STOP_LIMIT: return "limit";
        default:         return "unknown";
    }
}

// 技术点3：enum class（强类型，即不能隐式转换 + 作用域）
enum class TaskType : uint8_t {
    Completion = 0,
    Embedding  = 1,
    Rerank     = 2,
};

// 技术点4：作为 unordered_map key（自定义 hash）
struct TaskTypeHash {
    size_t operator()(TaskType t) const noexcept {
        return std::hash<uint8_t>{}(static_cast<uint8_t>(t));
    }
};

// 技术点5：位标志（与文档中的 FLAG_DAT/FLAG_FWD 类似）
enum DecodeFlags : uint32_t {
    FLAG_NONE      = 0,       // 0000
    FLAG_USE_KV    = 1u << 0, // 0001
    FLAG_USE_FLASH = 1u << 1, // 0010
    FLAG_STREAMING = 1u << 2, // 0100
};

static bool has_flag(uint32_t flags, DecodeFlags f) {
    return (flags & static_cast<uint32_t>(f)) != 0;
}

int main() {
    std::cout << "=== enum keypoints in LLM inference demo ===\n";

    // 1) enum + switch 文本映射
    StopType stop = STOP_LIMIT;
    std::cout << "stop type: " << stop_type_to_str(stop) << "\n";

    // 2) enum class 强类型（不能隐式转 int）
    TaskType task = TaskType::Completion;
    // int x = task; // 编译错误：需显式转换
    int task_id = static_cast<int>(task);
    std::cout << "task id: " << task_id << "\n";

    // 3) enum 作为哈希容器 key（key 任务 到 默认 batch 大小 的映射）
    std::unordered_map<TaskType, int, TaskTypeHash> default_batch = {
        {TaskType::Completion,  1},
        {TaskType::Embedding,  64},
        {TaskType::Rerank,     16},
    };
    std::cout << "embedding default batch: "
              << default_batch[TaskType::Embedding] << "\n";

    // 4) 位标志组合（一个整数同时表达多个值）
    uint32_t flags = FLAG_NONE;
    flags |= FLAG_USE_KV;
    flags |= FLAG_STREAMING;
    // flags = 0101 ，同时表达 FLAG_USE_KV 和 FLAG_STREAMING 

    std::cout << "use_kv? " << has_flag(flags, FLAG_USE_KV) << "\n";
    std::cout << "use_flash? " << has_flag(flags, FLAG_USE_FLASH) << "\n";
    std::cout << "streaming? " << has_flag(flags, FLAG_STREAMING) << "\n";

    return 0;
}

