#include <cstdint>
#include <cstring>
#include <iostream>

// 参考 llama/ggml/src/ggml.c 的两个经典用法：
// 
// 1) 先转 char*，按“字节”移动指针
// incr_ptr_aligned: *p = (void *)((char *)ptr + size);
//    
// 2) 先转成具体类型指针，再解引用读取
// op_params 读取: ((const int32_t *) tensor->op_params)[i]
//    

// 这个函数模拟 ggml 的“内存池前进”模式， ***
static void* alloc_from_pool(void** pool, size_t size) {
    // start 指向 pool 的首地址，
    void* start = *pool; 

    // 关键点：void* 不能做 ++ / +size 指针运算
    // 必须先转成 char*（1 字节步长）再移动。
    // start 移动了 size 个位置，新的位置赋值给 pool（pool更新了首地址，因为之前的已经分配了）
    *pool = (void *) ((char *) start + size);

    // 返回 旧地址起点，就地址起点到新的pool之间的位置赢被分配
    return start;
}


// case A：知道总字节数，但暂时不知道具体类型布局（典型 void* 用途）
// 要求这个数组起始地址按 16 字节对齐（地址是 16 的倍数），
// 很多指令或数据访问在对齐时更安全/更快。
void caseA() {
    alignas(16) unsigned char raw[64] = {};
    void* pool = raw; // 泛型原始内存指针

    // 从池中分配两段内存：4个int 和 2个float
    int* ids = (int *) alloc_from_pool(&pool, 4 * sizeof(int));
    float* scores = (float *) alloc_from_pool(&pool, 2 * sizeof(float));

    // 写入数据（已经转成具体类型指针，可正常解引用）
    ids[0] = 11; 
    ids[1] = 22; 
    ids[2] = 33; 
    ids[3] = 44;
    scores[0] = 0.75f; 
    scores[1] = 0.95f;

    std::cout << "ids: " << ids[0] << ", " << ids[1] << ", " << ids[2] << ", " << ids[3] << "\n";
    std::cout << "scores: " << scores[0] << ", " << scores[1] << "\n";

    return;

}

// case B：模拟 ggml 的 op_params（void* 保存原始参数块）
// 这里模拟工程场景：写端和读端解耦，只通过一块原始字节缓冲区通信。
// 完整场景通常是这样：
//    1. 图构建阶段（写端）把各种算子参数打包进统一 op_params（void*/byte buffer）
//    2. 执行阶段（读端）只拿到这块 buffer，再按约定类型解析（int32_t*、float*）
//    3. 两阶段可能不在同一函数、甚至不在同一模块
void caseB() {

    alignas(16) unsigned char op_params[16] = {};
    int32_t params_i32[4] = {64, 128, 256, 512};

    std::memcpy(op_params, params_i32, sizeof(params_i32));

    void* p = op_params;

    // 关键点：void* 不能直接 *p；必须转成具体类型（这里是 const int32_t*）
    const int32_t nb1 = ((const int32_t *) p)[0];
    const int32_t nb2 = ((const int32_t *) p)[1];
    const int32_t nb3 = ((const int32_t *) p)[2];
    const int32_t off = ((const int32_t *) p)[3];

    std::cout << "op_params(int32): " << nb1 << ", " << nb2 << ", " << nb3 << ", " << off << "\n";
    return;
}


int main() {
    std::cout << "==== void* demo from llama patterns ====\n";
    caseA();
    caseB();

    // 下面两种写法都是错误示例：
    // std::cout << *p << "\n"; // 错：void* 不能直接解引用
    // p++;                     // 错：void* 不能直接做指针算术

    return 0;
}

