#ifndef MERGE_SORT_HEADER
#define MERGE_SORT_HEADER

#include <iostream>
#include <vector>
#pragma once
#include <assert.h>
#include "helper.h"

namespace collection_sorting {
using namespace std;
/*
归并排序是一种基于分治策略的高效排序算法。其核心思想是将待排序的数组不断分成更小的子数组，
直到每个子数组只包含一个元素（此时已排序），然后将这些已排序的子数组合并成更大的已排序数组，最终得到整个已排序的数组。

以下是归并排序算法的逻辑步骤：

1. 分解 (Divide):

    将待排序的数组递归地分成两个大小大致相等的子数组，直到每个子数组只包含一个元素。

2. 征服 (Conquer):

    每个包含单个元素的子数组本身就是已排序的。

3. 合并 (Combine):

    递归地将已排序的子数组合并成更大的已排序数组。合并操作的关键在于比较两个子数组中的元素，并将较小的元素放入新的已排序数组中。

示例:

假设我们要排序数组 [8, 3, 1, 7, 0, 10, 2]。

    分解: 数组被分成 [8, 3, 1, 7] 和 [0, 10, 2]。 然后继续分解，直到得到 [8], [3], [1], [7], [0], [10], [2]。

    征服: 这些单元素数组已经是排序的。

    合并:
        [8] 和 [3] 合并成 [3, 8]。
        [1] 和 [7] 合并成 [1, 7]。
        [3, 8] 和 [1, 7] 合并成 [1, 3, 7, 8]。
        [0] 和 [10] 合并成 [0, 10]。
        [2] 单独存在。
        [0, 10] 和 [2] 合并成 [0, 2, 10]。
        最后，[1, 3, 7, 8] 和 [0, 2, 10] 合并成 [0, 1, 2, 3, 7, 8, 10]。

O(nlogn)
*/
// TODO：在纸上画画
class MergeSort {
private:
    template <typename T>
    void merge(std::vector<T>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<T> L(n1), R(n2);

        // L 和 R 都是有序的
        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, /*k记录原来序列的索引*/k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k++] = L[i++];
            } else {
                arr[k++] = R[j++];
            }
        }

        while (i < n1) {
            arr[k++] = L[i++];
        }

        while (j < n2) {
            arr[k++] = R[j++];
        }
    }
public:
    template <typename T>
    void mergeSortRecursive(std::vector<T>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2; // 防止溢出
            // 分 （递归理解为左右两部分均已排好序）
            mergeSortRecursive(arr, left, mid); // 处理元素从 arr[left] 到 arr[mid]
            mergeSortRecursive(arr, mid + 1, right); // 处理元素从 arr[mid+1] 到 arr[right]
            // 治 （两个排好序的序列做merge）
            merge(arr, left, mid, right);
        }
    }
};

} // namespace collection_sorting
#endif // MERGE_SORT_HEADER
