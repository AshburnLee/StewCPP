#ifndef INSERTION_SORT_HEADER
#define INSERTION_SORT_HEADER

#include <iostream>
#include <vector>
#pragma once
#include <assert.h>
#include "helper.h"

namespace collection_sorting {
using namespace std;
/*
逻辑 （记住这个逻辑）
1. 第一个元素被认为已排序
2. 接下来，选择下一个元素，并将其插入到前面已排序子列表中的正确位置

假设我们要排序数组 [5, 2, 4, 6, 1, 3]

    迭代 1: [5, 2, 4, 6, 1, 3] 已排序子列表为 [5]。 键为 2。 2 < 5，所以将 2 插入到 5 之前，得到 [2, 5, 4, 6, 1, 3]。

    迭代 2: [2, 5, 4, 6, 1, 3] 已排序子列表为 [2, 5]。 键为 4。 4 < 5，但 4 > 2，所以将 4 插入到 5 之前，得到 [2, 4, 5, 6, 1, 3]。

    迭代 3: [2, 4, 5, 6, 1, 3] 已排序子列表为 [2, 4, 5]。 键为 6。 6 > 5，所以 6 保持在原位，得到 [2, 4, 5, 6, 1, 3]。

    迭代 4: [2, 4, 5, 6, 1, 3] 已排序子列表为 [2, 4, 5, 6]。 键为 1。 1 < 6, 1 < 5, 1 < 4, 1 < 2，所以将 1 插入到开头，得到 [1, 2, 4, 5, 6, 3]。

    迭代 5: [1, 2, 4, 5, 6, 3] 已排序子列表为 [1, 2, 4, 5, 6]。 键为 3。 3 < 6, 3 < 5, 3 < 4, 但 3 > 2，所以将 3 插入到 4 之前，得到 [1, 2, 3, 4, 5, 6]。


O(n^2)
*/
// DONE：在纸上画画
class InsertionSort {
public:
    template <typename T>// 快速排序主函数
    void Solver(vector<T>& arr) {
        int n = arr.size();

        for (int i = 1; i < n; i++) {
            int key = arr[i];
            int j = i - 1;  // j 记录前面已排序中最后一个数的idx

            // 将 key 与它左边的每个元素进行比较，直到找到比它小的元素。
            while (j >= 0 && arr[j] > key) {
                // 不必担心arr[j+1] 被覆盖，因为 arr[j+1] 就是 arr[i], 它已经被保存到副本 key 中。
                arr[j + 1] = arr[j--];  
            }

            // 将 key 放在比它小的元素之后。
            arr[j + 1] = key;
        }
    }
};

} // namespace collection_sorting
#endif // INSERTION_SORT_HEADER
