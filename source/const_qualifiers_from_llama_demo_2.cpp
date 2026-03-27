#include <iostream>
#include <string>
#include <vector>

// 这个示例按 LLM 推理场景整理 const 技术点。
// 对应 llama 常见模式：
// - const 引用参数：src/models/*.cpp 中大量 `const llama_model & model`
// - const 指针参数：ggml.c 中大量 `const struct ggml_tensor *`
// - const 成员函数：llama-vocab.cpp 中大量 `...::foo() const`
// - 返回 const 引用：llama-vocab.cpp `const std::string & ...::token_to_piece(...) const`

struct TensorDesc {
    int64_t ne[4] = {0, 0, 0, 0};
};

// 1) const 变量：值不可改
void demo_const_variable() {
    const int max_ctx = 4096;
    std::cout << "max_ctx=" << max_ctx << "\n";
    // max_ctx = 8192; // 编译错误
}

// 2) 指针 const 三种形态
void demo_const_pointer_forms() {
    int a = 10, b = 20;

    int* const p_fixed = &a;   // 指针本身不可改，*p 可改
    *p_fixed = 11;
    // p_fixed = &b;            // 编译错误

    const int* p_readonly = &a; // 指向内容不可改，指针可改指向
    p_readonly = &b;            // 再次赋值，没有笛梵该使用到
    (void) p_readonly;
    // *p_readonly = 30;         // 编译错误

    const int* const p_both = &a; // 指针和内容都不可改
    (void) p_both;
}

// 3) const 引用参数：避免拷贝，且不允许修改入参
void print_prompt(const std::string & prompt) {
    std::cout << "prompt: " << prompt << "\n";
    // prompt += "x"; // 编译错误
}

// 4) const 指针参数：读输入，不改输入
bool can_mul_mat(const TensorDesc* t0, const TensorDesc* t1) {
    return (t0->ne[0] == t1->ne[0]) &&
           (t1->ne[2] % t0->ne[2] == 0) &&
           (t1->ne[3] % t0->ne[3] == 0);
}

class VocabLike {
public:
    explicit VocabLike(std::vector<std::string> pieces) : pieces_(std::move(pieces)) {}

    // 5) const 成员函数：不改对象状态
    size_t n_tokens() const { return pieces_.size(); }

    // 6) 返回 const 引用：避免拷贝，禁止调用方通过返回值修改内部数据
    const std::string& token_to_piece(size_t token) const { return pieces_.at(token); }

    // 7) 返回 const 指针：调用方不能改字符串字面量内容
    static const char* model_family() { return "llama-like"; }

private:
    std::vector<std::string> pieces_;
};

// 8) const_iterator：只读遍历（避免误改）
void print_all_pieces(const std::vector<std::string> & pieces) {
    for (std::vector<std::string>::const_iterator it = pieces.begin(); it != pieces.end(); ++it) {
        std::cout << *it << " ";
        // *it = "x"; // 编译错误：const_iterator 不允许修改元素
    }
    std::cout << "\n";
}

// 9) const_cast 工程上一般不使用
void demo_const_cast_only_for_nonconst_origin() {
    int value = 7;
    const int* cp = &value;                  // 非 const 对象被const ptr 指向
    int* p = const_cast<int *>(cp);          // 去掉 const
    *p = 8;                                   // 合法：底层对象本来就是非 const
    std::cout << "const_cast value=" << value << "\n";
}

int main() {
    std::cout << "=== const keypoints in LLM inference demo ===\n";

    demo_const_variable();
    demo_const_pointer_forms();

    print_prompt("解释 KV cache 的作用");

    TensorDesc wq{{128, 4096, 1, 1}};
    TensorDesc x {{128, 1,    1, 1}};
    std::cout << "can_mul_mat=" << can_mul_mat(&wq, &x) << "\n";

    VocabLike vocab({"<bos>", "hello", "world"});
    std::cout << "family=" << VocabLike::model_family() << "\n";
    std::cout << "n_tokens=" << vocab.n_tokens() << "\n";
    std::cout << "token[1]=" << vocab.token_to_piece(1) << "\n";

    std::vector<std::string> pieces = {"a", "b", "c"};
    print_all_pieces(pieces);

    demo_const_cast_only_for_nonconst_origin();
    return 0;
}

