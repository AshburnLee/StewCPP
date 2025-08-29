#include <iostream>
#include <memory>


class ErrorPopup {
public:
    ErrorPopup() {
        std::cout << "ErrorPopup created" << std::endl;
    }
};

class StateField {
public:
    StateField() {
        std::cout << "StateField created" << std::endl;
    }
    void update() {
        std::cout << "StateField updated" << std::endl;
    }
};

class PRB_T {
public:
    PRB_T() {
        std::cout << "PRB_T created" << std::endl;
    }
};

class prb_wrapper_base_t {
public:
    virtual ~prb_wrapper_base_t() = default;
    // 这里使得get() 返回一个指向 PRB_T 的指针，实际 PRB_T 是什么，会在
    // 这个函数被调用时给出
    template <typename PRB_T>
    const PRB_T *get() const;
};

// A template class to wrap shared pointer of prb obj
template <typename PRB_T>
class prb_wrapper_t : public prb_wrapper_base_t {
public:
    prb_wrapper_t(const std::shared_ptr<PRB_T> prb) { prb_ = prb; }
    // get raw pointer of prb object
    const PRB_T *get() const { return prb_.get(); }

private:
    std::shared_ptr<PRB_T> prb_;
};

template <typename PRB_T>
inline const PRB_T *prb_wrapper_base_t::get() const {
    return dynamic_cast<const prb_wrapper_t<PRB_T> &>(*this).get();
}

int main() {
    ErrorPopup errorPopup;

    StateField stateField;
    stateField.update();

    PRB_T prb;
    std::shared_ptr<PRB_T> prbPtr = std::make_shared<PRB_T>(prb);
    prb_wrapper_t<PRB_T> prbWrapper(prbPtr);
    const PRB_T *myprb = prbWrapper.get();  // 右边是const，所以返回的也是const
    std::cout << "PRB_T object obtained through prb_wrapper_t: " << myprb << std::endl;

    return 0;
}
