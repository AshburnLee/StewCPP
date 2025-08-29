#ifndef QUICK_SORT_HEADER
#define QUICK_SORT_HEADER

#include <iostream>
#include <vector>
#pragma once
#include <assert.h>
#include "helper.h"

namespace collection_sorting {
using namespace std;
/*
快速排序 (Quicksort) 是一种高效的排序算法，基于分治策略。其核心思想是：

    选择基准 (Pivot): 从数组中选择一个元素作为基准。选择基准的方法有很多，例如选择第一个元素、最后一个元素、中间元素，
                     或者随机选择一个元素。基准的选择会影响算法的性能，但通常情况下，随机选择基准可以避免最坏情况的发生。

    划分 (Partition): 将数组划分成两个子数组：一个子数组包含所有小于基准的元素，另一个子数组包含所有大于基准的元素。 
                      划分过程中，基准元素最终会处于其排序后的正确位置。有多种划分方法，但目标都是将小于基准的元素放在基准左边，大于基准的元素放在基准右边。

    递归排序 (Recursive Sort): 递归地对两个子数组进行快速排序。 当子数组只有一个元素或为空时，递归结束，该子数组已排序。

O(nlogn)
*/
// TODO：在纸上画画
class QuickSort {
private:
    // 分区函数，选择最后一个元素作为基准
    // 使得基准元素处于其排序后的正确位置，即pivot前小于pivot，pivot后大于pivot
    template <typename T>
    int partition(vector<T>& arr, int low, int high) {
        T pivot = arr[high];
        int i = (low - 1); // i 指向小于基准的元素的最后一个位置

        for (int j = low; j <= high - 1; j++) {
            // 如果当前元素小于或等于基准
            if (arr[j] <= pivot) {
                i++; // 将 i 向前移动一位
                swap(arr[i], arr[j]); // 交换 arr[i] 和 arr[j]
            }
        }
        swap(arr[i + 1], arr[high]); // 将基准放置到正确的位置
        return (i + 1);
    }

public:
    template <typename T>// 快速排序主函数
    void quick_sort(vector<T>& arr, int low, int high) {
        if (low < high) {
            // 分：pi 是分区索引，arr[pi] 现在位于正确的位置
            int pi = partition(arr, low, high);

            // 治：分别对左右子数组进行排序
            quick_sort(arr, low, pi - 1);
            quick_sort(arr, pi + 1, high);
        }
    }
};

} // namespace collection_sorting
#endif // QUICK_SORT_HEADER
