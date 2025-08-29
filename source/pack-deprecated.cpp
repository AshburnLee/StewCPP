#include <stdio.h> // printf

#pragma pack(4) // 设置 4 字节对齐
struct MyData1 {
    float value;
    char padding[2]; 
};
#pragma pack() // 取消自定义对齐


struct MyData2 {
    float value;
    char padding[2]; // 修改为 1 个字节的填充
};

struct MyData3 {
    float value;
};

struct MyData4 {
    float value;
    char padding[5]; 
};

int main() {
    printf("Sizeof MyData1: %zu\n", sizeof(struct MyData1)); // 输出 8
    printf("Sizeof MyData2: %zu\n", sizeof(struct MyData2)); // 输出 8
    printf("Sizeof MyData3: %zu\n", sizeof(struct MyData3)); // 输出 4
    printf("Sizeof MyData4: %zu\n", sizeof(struct MyData4)); // 输出 12
    return 0;
}
