// file: my_error_demo.cpp
#include <exception>
#include <iostream>

// 典型 C 风格错误码
enum class Status {
    Ok = 0,
    NotFound,
    IOError,
};

// 模拟 调用，返回状态码
Status c_api_read(int id) {
    if (id == 0) return Status::NotFound;
    if (id < 0)  return Status::IOError;
    return Status::Ok;
}

// 自定义异常类型
class MyError : public std::exception {
public:
    MyError(Status s, const char* msg) noexcept
        : status_(s), msg_(msg) {}

    // error 信息和 error code
    const char* what() const noexcept override { return msg_; }
    Status code() const noexcept { return status_; }

    // 错误就抛异常
    static void check(Status s, const char* msg) {
        if (s != Status::Ok) {
            throw MyError{s, msg};
        }
    }

private:
    Status status_;
    const char* msg_;
};

int main() {
    try {
        Status s = c_api_read(0);    // step1, 返回状态码
        MyError::check(s, "read failed");  // step2，不 Ok 就 throw
        std::cout << "read ok\n";
    } catch (const MyError& e) {   // step3，log error 信息 和 code
        std::cerr << "MyError: " << e.what()
                  << " (code=" << static_cast<int>(e.code()) << ")\n";
    }
}
