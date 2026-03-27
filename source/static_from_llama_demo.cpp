#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// 更换为“采样器”场景（贴近 llama-sampling.cpp）：
// 1) 文件内 static 函数：模块内部 logits 工具函数
// 2) 类内 static 成员：记录全局采样统计（总采样次数）
// 3) 函数内 static 局部变量：一次性初始化并跨调用保存配置

namespace {

// 技术点1：文件内 static 函数（内部链接）
// 只在本 .cpp 内可见，类似 llama-sampling.cpp 的一组 static helper。
static int argmax_token(const std::vector<float>& logits) {
    int best = 0;
    for (int i = 1; i < static_cast<int>(logits.size()); ++i) {
        if (logits[i] > logits[best]) {
            best = i;
        }
    }
    return best;
}

} // namespace

class SamplerStats {
public:
    static void on_sample() { ++total_samples_; }
    static int total_samples() { return total_samples_; }

private:
    // 技术点2：类内 static 成员（属于类而非对象）
    static int total_samples_;
};

int SamplerStats::total_samples_ = 0;

// 技术点3：函数内 static 局部变量（只初始化一次，后续复用）
static float get_temperature() {
    static float temperature = 0.7f; // 首次调用初始化，后续保留
    return temperature;
}

int main() {
    std::cout << "=== static keypoints (LLM sampler case) ===\n";

    std::vector<std::vector<float>> logits_steps = {
        {0.1f, 1.2f, 0.3f, 0.9f},
        {0.4f, 0.2f, 1.5f, 0.8f},
        {1.1f, 0.7f, 0.6f, 0.5f},
    };

    std::cout << "temperature=" << std::fixed << std::setprecision(1) << get_temperature() << "\n";

    // 采样返回每一组中值最大的索引值
    for (int step = 0; step < static_cast<int>(logits_steps.size()); ++step) {
        int token = argmax_token(logits_steps[step]); // 文件内 static helper
        SamplerStats::on_sample();                    // 类内 static 统计
        std::cout << "step " << step << " -> pick token " << token << "\n";
    }

    std::cout << "total samples=" << SamplerStats::total_samples() << "\n";
    return 0;
}

