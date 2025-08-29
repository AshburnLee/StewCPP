
## OMP

需要充分了解程序的实现细节之后，才能进行并行处理

并行区重构(compiler 中常见的变换)：

- 并行区合并（将相邻的两个并行区合并为一个更大的并行区）
- 并行区扩张（将函数结构中的并行区提出来，放到函数结构之外）

`#pragma omp single` 包含了同步

`#pragma omp single` 用于标识只有一个线程会执行该指令之后的代码块，而其他线程将跳过该代码块，等待单个线程执行完毕。
`#pragma omp master`

`#pragma omp parallel shared(k)`
`#pragma omp parallel firstprivate(k)`
`#pragma omp for reduce(+: sum1)`

`#pragma omp paralle for`
`#pragma omp paralle`
`#pragma omp for`

向量化技术与硬件规格密切相关，所以需要了解硬件和指令集的细节信息。

`#pragma omp simd`
`#pragma omp for simd`
