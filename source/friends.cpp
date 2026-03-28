#include <deque>
#include <iostream>
#include <string>

// 从 llama 里抽取的两个友元案例：
// 1) llama/vendor/cpp-httplib/httplib.h: friend struct worker;
// 2) llama/src/llama-arch.h: friend bool operator==(const std::string&, ...)

// 案例1：friend struct worker（线程池内部 worker 访问私有任务队列）
class ThreadPoolLike {
public:
    void enqueue(int task_id) { tasks_.push_back(task_id); }

private:
    std::deque<int> tasks_;

    friend struct Worker; // 允许 Worker 访问 tasks_
};

struct Worker {
    static void consume_one(ThreadPoolLike & pool) {
        if (pool.tasks_.empty()) {
            std::cout << "no task\n";
            return;
        }
        int id = pool.tasks_.front();
        pool.tasks_.pop_front();
        std::cout << "consume task #" << id << "\n";
    }
};

// 案例2：friend operator==（字符串与私有名称比较）
class TensorNameLike {
public:
    explicit TensorNameLike(std::string s) : name_(std::move(s)) {}

    // 成员比较：左操作数为 *this，可比较 “同类” 或 “string 在右侧” 
    // 注意 成员操作符 与友元操作符的 
    bool operator==(const TensorNameLike& o) const { return name_ == o.name_; }
    bool operator!=(const TensorNameLike& o) const { return name_ != o.name_; }
    bool operator==(const std::string& s) const { return name_ == s; }
    bool operator!=(const std::string& s) const { return name_ != s; }

private:
    std::string name_;

    // 非成员友元：仅当 std::string 在左侧时需要（成员函数无法实现 s == tn， 故必须是 friend） ***
    // 这里不是const 函数，因为 函数改变了私有成员
    friend bool operator==(const std::string& s, const TensorNameLike& tn) {
        return s == tn.name_;
    }
    friend bool operator!=(const std::string& s, const TensorNameLike& tn) {
        return s != tn.name_;
    }
};

int main() {
    std::cout << "=== friend cases from llama ===\n";

    ThreadPoolLike pool;
    pool.enqueue(101);
    pool.enqueue(102);
    Worker::consume_one(pool);
    Worker::consume_one(pool);
    Worker::consume_one(pool);

    TensorNameLike tn("blk.0.attn_q.weight");
    TensorNameLike same("blk.0.attn_q.weight");
    TensorNameLike other("other");
    std::cout << "string left == tn? " << ("blk.0.attn_q.weight" == tn) << "\n";   // 友元
    std::cout << "tn == string right? " << (tn == std::string("blk.0.attn_q.weight")) << "\n";  // 成员

    std::cout << "tn == same object? " << (tn == same) << " tn != other? " << (tn != other) << "\n";  // 成员
    std::cout << "string left != tn? " << ("token_embd.weight" != tn) << "\n";   // 友元
    return 0;
}
