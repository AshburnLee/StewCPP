#ifndef METHOD_CHAIN_
#define METHOD_CHAIN_

class Calculator {
public:
    Calculator() : result_(0) {}
    Calculator& add(int num) {
        result_ += num;
        return *this;  // 支持链式调用运算符
    }
    Calculator& sub(int num) {
        result_ -= num;
        return *this;  // 支持链式调用运算符
    }
    int GetResult() const {
        return result_;
    }
private:
    int result_;
};

#endif // METHOD_CHAIN_
