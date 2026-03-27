#include <iostream>
#include <string>
#include <vector>

// 参考 llama 片段（tools/server/utils.hpp）:

// server_tokens(const server_tokens&) = delete;
// server_tokens& operator=(const server_tokens&) = delete;

// server_tokens(server_tokens&&) = default;
// server_tokens& operator=(server_tokens&&) = default;

// 示例保留同样思想：禁拷贝，允许移动 ***

class TokenBuffer {
public:
    TokenBuffer() = default;

    explicit TokenBuffer(std::vector<int> data, std::string tag)
        : data_(std::move(data)), tag_(std::move(tag)) {}

    // 禁止拷贝：避免无意的大对象复制
    TokenBuffer(const TokenBuffer &) = delete;
    TokenBuffer & operator=(const TokenBuffer &) = delete;

    // 允许移动构造：用于“创建新对象时”转移资源
    TokenBuffer(TokenBuffer && other) noexcept
        : data_(std::move(other.data_)), tag_(std::move(other.tag_)) {
        std::cout << "[触发] 移动构造\n";
    }

    // 允许移动赋值：用于“已存在对象”接管另一个对象资源
    TokenBuffer & operator=(TokenBuffer && other) noexcept {
        std::cout << "[触发] 移动赋值\n";
        if (this != &other) {
            data_ = std::move(other.data_);
            tag_  = std::move(other.tag_);
        }
        return *this;
    }

    void print_state(const std::string & name) const {
        std::cout << name << " -> tag: '" << tag_ << "', size: " << data_.size() << "\n";
    }

private:
    std::vector<int> data_;
    std::string tag_;
};

int main() {
    TokenBuffer src(std::vector<int>{1, 2, 3, 4}, "source-buffer");
    src.print_state("src(初始)");

    // 场景1：创建“新对象”并接管 src 资源 => 调用移动构造
    TokenBuffer created_by_move(std::move(src));
    created_by_move.print_state("created_by_move");
    src.print_state("src(被移动后)");

    TokenBuffer another(std::vector<int>{9, 9}, "another-buffer");
    another.print_state("another(赋值前)");

    // 场景2：给“已存在对象”赋值 => 调用移动赋值
    another = std::move(created_by_move);
    another.print_state("another(移动赋值后)");
    created_by_move.print_state("created_by_move(被移动后)");

    return 0;
}

