#include <cctype>
#include <iostream>
#include <string>
#include <vector>

namespace grammer{
namespace inline_demo {

static inline bool is_base64(unsigned char c) {
    return std::isalnum(c) || c == '+' || c == '/';
}

enum class StopType {
    EOS,
    WORD,
    LIMIT,
    UNKNOWN,
};

// Small mapper function: typical pattern in production code.
static inline const char * stop_type_to_str(StopType type) {
    switch (type) {
        case StopType::EOS:   return "eos";
        case StopType::WORD:  return "word";
        case StopType::LIMIT: return "limit";
        default:              return "unknown";
    }
}

static inline int count_base64_chars(const std::string & s) {
    int cnt = 0;
    for (unsigned char c : s) {
        if (is_base64(c)) {
            ++cnt;
        }
    }
    return cnt;
}

}  // namespace inline_demo
}  // namespace grammer

int main() {
    using grammer::inline_demo::StopType;

    std::vector<StopType> types = {
        StopType::EOS,
        StopType::WORD,
        StopType::LIMIT,
        StopType::UNKNOWN
    };  

    for (StopType t : types) {
        std::cout << "  " << grammer::inline_demo::stop_type_to_str(t) << "\n";
    }

    std::string sample = "Q2hhdEdQVA==";
    std::cout << "  input: " << sample << "\n";
    std::cout << "  valid base64 chars: " << grammer::inline_demo::count_base64_chars(sample) << "\n";

    return 0;
}

