#ifndef FORBID_COPY_ASIGN_
#define FORBID_COPY_ASIGN_

class MySmartPointer {
public:
    
    MySmartPointer(int* p) : ptr_(p) {}
    ~MySmartPointer() { delete ptr_; }

    // 禁止默认构造，禁止拷贝，禁止赋值
    // 这些删除的函数确保了 MySmartPointer 对象的唯一性，防止了意外的拷贝和赋值操作，从而避免了潜在的内存管理问题。
    // 这在我们不希望对象被复制的情况下非常有用，
    // 例如，当我们的对象包含不能或不应该被复制的资源时，
    // 如文件句柄、网络连接、大内存块等
    MySmartPointer() = default;
    MySmartPointer(const MySmartPointer&) = delete;
    MySmartPointer& operator=(const MySmartPointer&) = delete;

    // 移动构造函数 和 移动赋值运算符
    MySmartPointer(MySmartPointer&& other) noexcept;
    MySmartPointer& operator=(MySmartPointer&& other) noexcept;
    int* get_ptr() const { return ptr_; }
private:
    int* ptr_;
};

MySmartPointer::MySmartPointer(MySmartPointer&& other) noexcept {
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
}

MySmartPointer& MySmartPointer::operator=(MySmartPointer&& other) noexcept {
    if (this != &other) {
        delete ptr_;
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }
    return *this;  // 支持链式复制
}

#endif  // FORBID_COPY_ASIGN_