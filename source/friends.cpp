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

private:
    std::string name_;

    // 友元比较函数直接读取私有 name_
    friend bool operator==(const std::string & s, const TensorNameLike & tn) {
        return s == tn.name_;
    }
    friend bool operator!=(const std::string & s, const TensorNameLike & tn) {
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
    std::cout << "match? " << ("blk.0.attn_q.weight" == tn) << "\n";
    std::cout << "not match? " << ("token_embd.weight" != tn) << "\n";
    return 0;
}
