#include "self_memcpy.h"  // memcpy()  memcpy_adv()
#include "helper.h"  // CheckValue<int>()

int main() {
    int src_int[] = {1, 2, 3, 4, 5};
    int dest_int[5];  //

    SelfMemcpy self_memcpy;
    self_memcpy.memcpy(dest_int, src_int, sizeof(src_int));
    std::cout << "sizeof(src_int): " << sizeof(src_int) << "\nafter copy: \n";
    for (int i = 0; i < 5; ++i) {
        std::cout << dest_int[i] << " ";
    }
    std::cout << std::endl;

    char src_char[] = "Hello, world!";  // 14 bytes 13 + '\0' 终止符
    char dest_char[20];
    self_memcpy.memcpy(dest_char, src_char, sizeof(src_char));
    std::cout << "sizeof(src_char): "<<sizeof(src_char)<< "\nafter copy: " << dest_char << std::endl;

    std::string a = "Hello, world!";
    std::cout << sizeof(a) <<"\n";    // 32 bytes

    // 2. 使用自定义的 memcpy_aligned 函数
    char src[] = "Hello, world! This is a test.";
    char dest[100];

    self_memcpy.memcpy_aligned(dest, src, std::strlen(src) + 1);

    std::cout << "Copied string: " << dest << std::endl;

    return 0;
}

