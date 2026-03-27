#include <array>
#include <iostream>
#include <string>

struct TensorDesc {
    std::array<long long, 4> ne{};
    std::string name;
};

namespace detail {

// const 指针参数：可读 t0/t1，但不能通过它们修改对象内容
// 对应 内积维必须相等, 同时高维上的可广播
// 输出 矩阵shape是 (t0->ne[1] , t1->ne[1])
static inline bool can_mul_mat(const TensorDesc * t0, const TensorDesc * t1) {
    return (t0->ne[0] == t1->ne[0]) &&
           (t1->ne[2] % t0->ne[2] == 0) &&
           (t1->ne[3] % t0->ne[3] == 0);
}

} // namespace detail

class LlmMatmulPlanner {
public:
    LlmMatmulPlanner(TensorDesc a, TensorDesc b) : a_(std::move(a)), b_(std::move(b)) {}

    // 成员函数尾部 const：不允许修改当前对象状态（a_ 和 b_一起构成了对象当前状态）
    // 本来只是“检查能不能乘”，不该顺手改 shape，所以有编译时前置约束 ，所以是只读 方法
    bool can_schedule() const {
        return detail::can_mul_mat(&a_, &b_);
    }

    // 返回 const 引用：只读访问 同时 避免 string 拷贝
    const std::string & lhs_name() const { return a_.name; }

    // 返回 const char*：caller 不能通过该指针修改字符串内容
    static const char * op_name() { return "ggml_mul_mat"; }

private:
    TensorDesc a_;
    TensorDesc b_;
};

int main() {
    TensorDesc wq{{128, 4096, 1, 1}, "Wq"};
    TensorDesc x {{128, 1,    1, 1}, "X"};

    LlmMatmulPlanner ok(wq, x);
    std::cout << LlmMatmulPlanner::op_name() << " with " << ok.lhs_name()
              << " => " << (ok.can_schedule() ? "compatible" : "incompatible") << "\n";

    TensorDesc bad_x{{64, 1, 1, 1}, "BadX"};
    LlmMatmulPlanner bad(wq, bad_x);
    std::cout << LlmMatmulPlanner::op_name() << " with " << bad.lhs_name()
              << " => " << (bad.can_schedule() ? "compatible" : "incompatible") << "\n";

    return 0;
}

