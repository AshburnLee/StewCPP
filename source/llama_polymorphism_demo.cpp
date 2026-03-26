#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "llama_polymorphism.h"

using grammer::llama_polymorphism::Printer;
using grammer::llama_polymorphism::CsvPrinter;

int main() {
    // 关键: upcasting + 通过 unique-ptr 的 RAII
    std::unique_ptr<Printer> printer = std::make_unique<CsvPrinter>();

    printer->print_header("llama bench style output");
    printer->print_row({"model", "tok/s"});
    printer->print_row({"qwen2.5-7b", "123.45"});
    printer->print_footer();

    return 0;
}

