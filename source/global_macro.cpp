#include <iostream>

int main() {

// 有问题??
#ifdef PLATFORM
#if PLATFORM == CUDA
    std::cout << "gpu \n";
#elif PLATFORM == CPU
    std::cout << "cpu \n";
#endif
#endif

    return 0;
}
