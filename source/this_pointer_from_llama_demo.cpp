#include <iostream>
#include <string>
#include <unordered_map>

// Standalone demo inspired by llama/vendor/cpp-httplib/httplib.h member style:
// Request::get_header_value_u64(...) const {
//   return detail::get_header_value_u64(headers, key, def, id);
// }
//
// 改成 LLM 实用场景：读取推理参数（max_tokens/temperature/top_p）。
// 保留技术点：
// 1) 非静态成员函数通过隐式 this 访问对象状态
// 2) const 成员函数中的 this 受 const 约束
// 3) static 成员函数无 this，用于与对象无关的通用信息

using Headers = std::unordered_map<std::string, std::string>;

namespace detail {

// 字符串 -> u64，失败则回退默认值。
static unsigned long long to_u64_or_default(const std::string & s,
                                            unsigned long long def) {
    try {
        size_t pos = 0;
        unsigned long long v = std::stoull(s, &pos);
        if (pos != s.size()) {
            return def;
        }
        return v;
    } catch (...) {
        return def;
    }
}

// 字符串 -> double，失败则回退默认值。
static double to_double_or_default(const std::string & s, double def) {
    try {
        size_t pos = 0;
        double v = std::stod(s, &pos);
        if (pos != s.size()) {
            return def;
        }
        return v;
    } catch (...) {
        return def;
    }
}

// 从 map 读取 key 并转成 u64。string -> u64
static unsigned long long get_u64(const Headers & kv,
                                  const std::string & key,
                                  unsigned long long def) {
    auto it = kv.find(key);
    if (it == kv.end()) {
        return def;
    }
    return to_u64_or_default(it->second, def);
}

// 从 map 读取 key 并转成 double。
static double get_double(const Headers & kv,
                         const std::string & key,
                         double def) {
    auto it = kv.find(key);
    if (it == kv.end()) {
        return def;
    }
    return to_double_or_default(it->second, def);
}

}  // namespace detail

class LlmRequestConfig {
public:
    // 保存“请求参数”，模拟在线服务收到的请求字段。
    // move 把资源交给 params_ ，没有拷贝
    explicit LlmRequestConfig(Headers params) : params_(std::move(params)) {}

    // const 成员函数：读取对象状态，不修改对象。
    // this 的概念类型近似：const LlmRequestConfig * const
    unsigned long long max_tokens(unsigned long long def = 256) const {
        // this->params_ 可省略成 params_
        return detail::get_u64(params_, "max_tokens", def);
    }
    double temperature(double def = 0.7) const {
        return detail::get_double(params_, "temperature", def);
    }
    double top_p(double def = 0.9) const {
        return detail::get_double(params_, "top_p", def);
    }

    // static 成员函数无 this；适合放通用规则/元信息。
    static const char * model_family() {
        return "qwen3";
    }

private:
    Headers params_;
};


int main() {
    // 场景：推理服务收到参数字典（常见于 HTTP JSON/headers/query 转换后）的Header，
    // 读数值改成 "LLM 推理参数读取"
    Headers req_params = {
        {"max_tokens", "1024"},
        {"temperature", "0.2"},
        {"top_p", "0.95"},
        {"bad_numeric", "1x2"},
    };
    LlmRequestConfig req(req_params);

    // static 调用：无 this，不依赖对象实例
    std::cout << "Model family: " << LlmRequestConfig::model_family() << "\n";

    // 非静态 const 调用：有隐式 this，读取对象状态
    std::cout << "max_tokens: " << req.max_tokens() << "\n";
    std::cout << "temperature: " << req.temperature() << "\n";
    std::cout << "top_p: " << req.top_p() << "\n";

    // 演示默认值回退（缺失字段）
    LlmRequestConfig missing_params({});
    std::cout << "default max_tokens (missing): " << missing_params.max_tokens() << "\n";
    std::cout << "default temperature (missing): " << missing_params.temperature() << "\n";

    // 演示非法字符串回退（解析失败）
    LlmRequestConfig bad_params(Headers{{"temperature", "1x2"}});
    std::cout << "default temperature (bad input): " << bad_params.temperature() << "\n";

    return 0;
}

