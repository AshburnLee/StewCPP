#ifndef HEAP_SORT_HEADER
#define HEAP_SORT_HEADER

#include <iostream>
#include <vector>
#pragma once
#include <assert.h>
#include "helper.h"

namespace collection_sorting {
using namespace std;
/*
堆排序算法是一种基于堆数据结构的高效排序算法。它使用堆数据结构实现的选择排序。其核心思想是利用堆的特性，高效地找到数组中的最大值（或最小值）并将其放置到正确的位置。

堆排序算法主要分为两个步骤：

1. 建堆 (Build Heap):

将输入数组构建成一个最大堆（或最小堆）。最大堆是指父节点的值总是大于或等于其子节点的值，最小堆则相反。 
构建最大堆的过程通常使用自底向上的方法，从数组的中间节点开始，依次向上调整，确保每个节点都满足最大堆的性质。

2. 堆排序 (Heap Sort):

重复以下步骤，直到堆为空：

    交换: 将堆顶元素（最大值或最小值）与堆的最后一个元素交换。
    删除: 将堆的大小减 1，即忽略最后一个元素（已排序）。
    堆化 (Heapify): 对新的堆顶元素进行堆化操作，以维护最大堆（或最小堆）的性质。堆化操作从堆顶元素开始，向下调整，
                    确保其子树仍然满足最大堆（或最小堆）的性质。

算法步骤详解:

    构建最大堆: 将输入数组转换成最大堆。这可以通过从数组的最后一个非叶子节点开始，自底向上地进行堆化操作来实现。

    排序: 重复以下步骤，直到堆中只剩下一个元素：
        将堆顶元素（最大元素）与堆的最后一个元素交换。
        将堆的大小减 1（因为最大元素已经排好序了）。
        对新的堆顶元素进行堆化操作，以恢复最大堆的性质。

O(n log n)
*/
// TODO：在纸上画画
class HeapSort {
private:
    // 堆化以索引 i 为根的子树，使其满足最大堆的性质
    // n 是子树节点个数
    // i 是当前子树根节点索引
    template <typename T>
    void heapify(std::vector<T>& arr, int n, int i) {
        // 获取当前节点的左子节点和右子节点的索引
        int largest = i;  //  初始化最大值索引为当前节点
        int left = 2 * i + 1;   // 左子节点索引
        int right = 2 * i + 2;   // 右子节点索引

        // 如果左子节点存在且大于当前节点，则更新最大值索引
        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        // 如果右子节点存在且大于当前节点，则更新最大值索引
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        // 如果最大值索引不是当前节点，则交换当前节点和最大值节点，并递归调用 heapify 函数
        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }
public:
    template <typename T>
    void Solver(vector<T>& arr) {
        int n = arr.size();

        // 建立最大堆
        // 这个for循环是从最后一个非叶子节点开始，向上构建最大堆 ***
        // 确保每个子树都满足最大堆的性质。
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }

        // 从已排序的数组中提取元素
        for (int i = n - 1; i > 0; i--) {
            std::swap(arr[0], arr[i]); // 将当前最大元素移到数组末尾
            heapify(arr, i, 0);
        }
    }
};

} // namespace collection_sorting
#endif // HEAP_SORT_HEADER
