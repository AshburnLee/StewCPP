#ifndef BUBBLE_SORT_HEADER
#define BUBBLE_SORT_HEADER

#include <iostream>
#include <vector>
#pragma once
#include <assert.h>
#include "helper.h"

namespace collection_sorting {
using namespace std;
/*
冒泡排序是一种简单的排序算法，它重复地遍历要排序的列表，比较相邻的元素，如果它们的顺序错误就把它们交换。这个过程重复进行，直到列表排序完毕。

算法逻辑步骤：

    1. 比较相邻元素: 从列表的第一个元素开始，依次比较相邻的两个元素。
    2. 交换元素: 如果一对相邻元素的顺序错误（例如，在升序排序中，前面的元素大于后面的元素），则交换它们的位置。
    3. 遍历列表: 重复步骤 1 和 2，直到遍历整个列表。
    4. 重复过程: 重复步骤 1 到 3，直到列表完全排序。 在每次遍历后，最大的未排序元素都会“冒泡”到其正确的位置。

优化:

可以对冒泡排序进行优化，以减少不必要的比较次数。例如，如果在一次遍历中没有发生任何交换，则表示列表已排序，可以提前结束算法。

示例：

假设我们要对以下列表进行升序排序：[5, 1, 4, 2, 8]

    第一轮遍历:
        比较 5 和 1，交换它们：[1, 5, 4, 2, 8]
        比较 5 和 4，交换它们：[1, 4, 5, 2, 8]
        比较 5 和 2，交换它们：[1, 4, 2, 5, 8]
        比较 5 和 8，它们已排序。
    第二轮遍历:
        比较 1 和 4，它们已排序。
        比较 4 和 2，交换它们：[1, 2, 4, 5, 8]
        比较 4 和 5，它们已排序。
    第三轮遍历:
        比较 1 和 2，它们已排序。
        比较 2 和 4，它们已排序。

*/
// DONE：在纸上画画。回忆动画中的过程。
class BubbleSort {
public:
    template <typename T>
    void Solver(std::vector<T>& arr) {
        size_t n = arr.size();
        bool swapped;
        for (size_t i = 0; i < n - 1; ++i) {  // i 其实是对应两个连续的元素，所以 i 不超过 n-1
            swapped = false;
            for (size_t j = 0; j < n - i - 1; ++j) { // n - i - 1: i 是已排序的个数
                // 从做到右，将大的移到右边，升序排列，右边逐渐有序，不纳入考虑
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            // 如果一轮遍历后没有交换，说明数组此时已经排序完成, 跳出外层循环
            if (!swapped) {
                break;
            }
        }
    }
};

} // namespace collection_sorting
#endif // BUBBLE_SORT_HEADER
