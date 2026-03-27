#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace grammer {
namespace llama_polymorphism {
    
// 抽象基类 printer 和 derived format-specific printers.
struct Printer {
    virtual ~Printer() = default;  // 虚析构函数: 通过 base ptr 安全删除

    // 非纯虚函数：派生类可直接继承使用
    virtual void print_header(const std::string & title) {
        std::cout << "[header] " << title << "\n";
    }

    // 纯虚函数：derived 必须实现自己的逻辑
    virtual void print_row(const std::vector<std::string> & cells) = 0;

    virtual void print_footer() {
        std::cout << "[footer] end\n";
    }
};

struct CsvPrinter : public Printer {
    static std::string escape(const std::string & s) {
        std::string out = "\"";
        for (char c : s) {
            if (c == '"') out += '"';
            out += c;
        }
        out += "\"";
        return out;
    }

    // override 告诉编译器 必须重写 base class 的虚函数，编译器会帮我校验是否重写成功
    void print_row(const std::vector<std::string> & cells) override {
        for (size_t i = 0; i < cells.size(); ++i) {
            if (i) std::cout << ",";
            std::cout << escape(cells[i]);
        }
        std::cout << "\n";
    }
};

}  // namespace llama_polymorphism
}  // namespace grammer


int main() {
    using grammer::llama_polymorphism::Printer;
    using grammer::llama_polymorphism::CsvPrinter;
    
    // 关键: upcasting + 通过 unique-ptr 的 RAII
    std::unique_ptr<Printer> printer = std::make_unique<CsvPrinter>();

    printer->print_header("llama bench style output");
    printer->print_row({"model", "tok/s"});
    printer->print_row({"qwen2.5-7b", "123.45"});
    printer->print_footer();

    return 0;
}

