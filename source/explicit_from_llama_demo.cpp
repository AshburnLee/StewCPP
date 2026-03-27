#include <iostream>
#include <string>
#include <utility>

// LLM 推理相关的 explicit 使用案例：
// 参考 llama/src/llama-model.h:
//   explicit llama_model(const struct llama_model_params & params);
//
// 设计意图：避免把“看起来能转”的值（如字符串、数字）隐式变成复杂对象。

struct ModelParams {
    std::string model_path;
    int n_gpu_layers = 0;
};

class LlamaModelLike {
public:
    // 对应 llama 的风格：参数对象构造模型，且必须显式调用构造
    explicit LlamaModelLike(const ModelParams & params)
        : params_(params) {}

    void load() const {
        std::cout << "[load] model=" << params_.model_path
                  << ", n_gpu_layers=" << params_.n_gpu_layers << "\n";
    }

private:
    ModelParams params_;
};

struct SamplingConfig {
    double temperature = 0.7;
};

class InferenceRequest {
public:
    // 核心点1：禁止 std::string -> InferenceRequest 隐式转换
    explicit InferenceRequest(std::string prompt)
        : prompt_(std::move(prompt)) {}

    // 核心点2：禁止 double -> SamplingConfig 的链式隐式转换
    explicit InferenceRequest(SamplingConfig cfg)
        : prompt_("<hi there!>"), cfg_(cfg) {}

    void set_sampling(SamplingConfig cfg) { cfg_ = cfg; }

    void run() const {
        std::cout << "[infer] prompt=\"" << prompt_
                  << "\", temperature=" << cfg_.temperature << "\n";
    }

private:
    std::string prompt_;
    SamplingConfig cfg_;
};

void run_request(const InferenceRequest& req) {
    req.run();
}

int main() {
    std::cout << "=== explicit in LLM inference demo ===\n";

    ModelParams params{"qwen3-8b.gguf", 40};
    LlamaModelLike model(params);
    model.load();

    // 因为explicit，所以必须加 std::string()
    InferenceRequest req(std::string("解释一下 KV cache 的作用"));
    req.set_sampling(SamplingConfig{0.2});
    run_request(req);

    run_request(InferenceRequest(std::string("给我一个 C++ move 语义例子")));

    // 因为有explicit，所以必须严格传递
    run_request(InferenceRequest(SamplingConfig{0.99}));
    

#if 0
    // 如果去掉 核心点2 处的 explicit，下面“隐式转换”会通过，容易造成语义不清：
    // run_request(SamplingConfig{0.99});  
    // 
    // 回复explicit 后，上述报错：
    // error: invalid initialization of reference of type ‘const InferenceRequest&’ from 
    // expression of type ‘SamplingConfig’ 
    //                          79 |     run_request(SamplingConfig{0.99});

    //
    // 这就是 explicit 的价值：
    // 让调用方必须显式写出构造意图，避免“看起来能跑但语义不清”的隐式链式转换。
#endif

    return 0;
}

