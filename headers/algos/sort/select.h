#ifndef SELECT_SORT_HEADER
#define SELECT_SORT_HEADER

#include <iostream>
#include <vector>
#pragma once
#include <assert.h>
#include "helper.h"

namespace collection_sorting {
using namespace std;
/*
选择排序算法是一种简单的排序算法，其基本思想是：在未排序的数组中找到最小（或最大）的元素，将其与数组的第一个元素交换位置，
然后在剩余的未排序数组中重复这个过程，直到整个数组排序完毕。

以下是选择排序算法的逻辑步骤：(就是这两个步骤，记住他)

    1. 找到最小元素: 遍历未排序数组，找到最小元素及其索引。

    2. 交换元素: 将最小元素与未排序数组的第一个元素交换位置。


示例：

假设我们有一个未排序的数组 [64, 25, 12, 22, 11]。

第一轮迭代:

    找到最小元素：最小元素是 11，其索引是 4。
    交换元素：将 11 与 64 交换，数组变为 [11, 25, 12, 22, 64]。

第二轮迭代:

    找到最小元素：在剩余的未排序数组 [25, 12, 22, 64] 中，最小元素是 12，其索引是 1。
    交换元素：将 12 与 25 交换，数组变为 [11, 12, 25, 22, 64]。

继续迭代，直到数组排序完毕： [11, 12, 22, 25, 64]

O(n^2)
*/
// DONE：在纸上画画
class SelectSort {
public:
    template <typename T>// 快速排序主函数
    void Solver(vector<T>& arr) {
        for (size_t i = 0; i < arr.size(); ++i) {
            // 找到未排序部分中的最小元素, 用j找找最小元素
            size_t min_idx = i; // 记录寻找过程中最小值的idx
            for (size_t j = i + 1; j < arr.size(); ++j) {
                if (arr[j] < arr[min_idx]) {
                    min_idx = j;
                }
            }
            // 将最小元素与未排序部分的第一个元素交换
            if (min_idx != i) {
                swap(arr[i], arr[min_idx]);
            }
        }
    }
};

} // namespace collection_sorting
#endif // SELECT_SORT_HEADER
