#ifndef SELF_SHARED_PTR_H
#define SELF_SHARED_PTR_H

/*
shared_ptr 如何使用？
成员有什么？
行为有哪些？

    self_shared_ptr<int> ptr1(new int(10));  // 构造函数  
    self_shared_ptr<int> ptr2 = ptr1;       // 拷贝构造函数

    ptr1 和 ptr2 指向同一个对象，
    std::cout << "ptr1 use count: " << ptr1.use_count() << std::endl; // 输出 2
    std::cout << "ptr2 use count: " << ptr2.use_count() << std::endl; // 输出 2

    // 赋值运算符
    // ptr2 指向新的对象, ptr1 的引用计数减1
    // 因为 ptr2 与 ptr1 共享count_, 所以先count--，ptr1 & ptr2 的计数器都减一，
    // 然后将 ptr2 更新为新的对象的 内容
    ptr2 = self_shared_ptr<int>(new int(20)); 

    std::cout << "ptr1 use count: " << ptr1.use_count() << std::endl; // 输出 1
    std::cout << "ptr2 use count: " << ptr2.use_count() << std::endl; // 输出 1


解引用运算符 (*) 和成员访问运算符 (->): 允许像使用普通指针一样使用 

*/

#include <iostream>

template <typename T>
class self_shared_ptr {
private:
    T* ptr_;
    // 使用指针目的是在多个 self_shared_ptr 对象之间共享同一个引用计数
    int* count_;

public:
    // 构造函数
    self_shared_ptr(T* ptr = nullptr) : ptr_(ptr) {
        if (ptr_) {
            count_ = new int(1);  // int(1) 调用了int 的初始化器，相当于是构造函数
        } else {
            count_ = nullptr;
        }
    }
    // 拷贝构造函数 本质是浅拷贝 done
    self_shared_ptr(const self_shared_ptr& other) : ptr_(other.ptr_), count_(other.count_) {
        if (count_) {
            // 增加引用计数，因为共享了other的内容
            (*count_)++;
        }
    }

    // 赋值运算符 ，  done
    self_shared_ptr& operator=(const self_shared_ptr& other) {
        if (this != &other) {
            // 当前对象的指向改变了，所以减少已共享的引用计数
            if (count_ && ptr_) {
                (*count_)--;
                if (*count_ == 0) {
                    delete ptr_;
                    delete count_;
                }
            }
            // 将当前对象的指针和引用计数更新(浅拷贝)为其他对象的指针和引用计数, 所以更新后的count 要++ ***
            ptr_ = other.ptr_;
            count_ = other.count_;
            if (count_) {
                (*count_)++;
            }
        }

        return *this;
    }

    // 析构函数  done
    ~self_shared_ptr() {
        if (count_ && ptr_) {
            // 既然这个析构函数被调用，就表示一个对象被释放，故--
            (*count_)--;
            if (*count_ == 0) {
                delete ptr_;
                delete count_;
            }
        }
    }

    // 解引用运算符
    T& operator*() const { return *ptr_; }

    // -> 运算符
    T* operator->() const { return ptr_; }

    // 获取引用计数
    int use_count() const { return count_ ? *count_ : 0; }

    // 获取原始指针
    T* get() const { return ptr_; }
};

#endif  // SELF_SHARED_PTR_H
