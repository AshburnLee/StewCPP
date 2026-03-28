#ifndef BINARY_SEARCH_HEADER
#define BINARY_SEARCH_HEADER

#include <vector>
#include <cmath>
#include <unordered_set>
#pragma once
using namespace std;

// 二分查找的本质不是“有序”，而是“每一次比较都能排除一半解空间”，
// 只要问题具有决策单调性（或称“二段性”），即可二分——哪怕数组无序！
// Insight: BS 细分为两个类型：【找左边界】 & 【找右边界】
//      “找第一个满足条件的”→ 用 left < right + 下取整 + right = mid / left = mid+1

// 左边界 / 右边界 : while (left < right)
// 精确查找        : while (left <= right)
// int mid = left + (right - left) / 2;
// 或：
// int mid = left + (right - left + 1) / 2;
// left = mid + 1
// 或：
// left = mid
// right = mid - 1
// 或：
// right = mid



// 模版一：精准查找
// int left = ..., right = ...;
// while (left <= right) {
//     int mid = left + (right - left) / 2;   // ✅ 下取整
//     if (nums[mid] == target) return mid;
//     else if (nums[mid] < target) left = mid + 1;
//     else right = mid - 1;
// }
// return -1;  // not found


// 模版二：最后一个 ≤ target。在非递减数组中，找下标最大的那个元素，它的值 小于或等于 target。
// int left = ..., right = ...;
// while (left < right) {
//     int mid = left + (right - left + 1) / 2;  // ✅ 上取整（+1）
//     if (nums[mid] <= target) {      // check: 
//         left = mid;        // ✅ 保留 mid
//     } else {
//         right = mid - 1;   // ✅ 跳过 mid
//     }
// }
// return left;


// 模版三：第一个 ≥ target。在非递减数组中，找下标最小的那个元素，它的值 大于或等于 target。
// int left = ..., right = ...;
// while (left < right) {
//     int mid = left + (right - left) / 2;   // ✅ 下取整（+0）
//     if (nums[mid] >= target) {      // check: 
//         right = mid;       // ✅ 保留 mid
//     } else {
//         left = mid + 1;    // ✅ 跳过 mid
//     }
// }
// return left;


/*
[704 E]. [374 E]. Easy Binary Search
标准的二分查找，没啥技巧，背下来
*/
class BinarySearch {
public:
    int LaunchSolver(vector<int> &nums, int target) {
        int l = 0;
        int r = nums.size() - 1;

        while (l <= r) {
            int mid = l + (r - l + 1) / 2;
            if (nums[mid] == target)
                return mid;
            else if (nums[mid] < target)
                l = mid + 1;
            else
                r = mid - 1;
        }
        return -1;
    }
};

/*
[278 E]. First Bad Version
版本号连续递增，从某一个版本号开始，出现问题，找打这个版本号，提供API判断版本的好坏： bool isBadVersion(int version);

Insight: 
    存在一个临界点 k，使得 [1, k-1] 全好，[k, n] 全坏 → 典型“二段性”！
    第一个满足 isBadVersion(x) == true 的 x，即 左边界（lower_bound）。

    若 mid 是坏版本 ⇒ 第一个坏版本 ≤ mid ⇒ right = mid  
    若 mid 是好版本 ⇒ 第一个坏版本 > mid ⇒ left = mid + 1
*/
// class FirstBadVersion {
// private:
//     static isBadVersion(int);
// public:
//     int Solver(int n){
//         int  left = 1;
//         int right = n;
//         while(left < right) {
//             int mid = left + (right - left) / 2;
//             if (isBadVersion(mid)) {
//                 right = mid;    // 由题意不 +1
//             } else {
//                 left = mid + 1; // 由题意 +1
//             }
//         }
//         return left;             // left == right
//     }
// };

/*
[35 E]. Search insert position
给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，
返回它将会被按顺序插入的位置。二分查找的复杂度是O(nlogn)

Example 1:
Input: nums = [1,3,5,6], target = 5
Output: 2

Example 2:
Input: nums = [1,3,5,6], target = 2
Output: 1


Insight：这个题就是为了应用二分查找，给你设计了个题，
Insight：唯一细想的是最后返回的是那个指针的位置！
循环条件是 while (left <= right)，当它退出时即没有找到时, left > right, 有：
    所有 nums[0...right] 都 < target
    所有 nums[left...n-1] 都 >= target
所以最后一定是放在 第一个 >= target 的位置，即left! 这个是 BS 的灵魂

*/
class SearchInsert {
public:
    int LaunchSolver(vector<int> &nums, int target) {
        int left = 0, right = nums.size() - 1;  
        while (left <= right) {  
            int mid = left + (right - left + 1) / 2;   // Key 1
            if (nums[mid] == target) {                 // Key 2
                return mid;  
            } else if (nums[mid] < target) {  
                left = mid + 1;                        // Key 3
            } else {  
                right = mid - 1;                       // Key 3
            }  
        }  
        return left;                                   // 由题意返回 left
    }
};


// #153. find min in rotated sorted array, 数组元素不重复
class FindMinInRotate {
public:
    int LaunchSolver(vector<int> &nums) {
        if (nums.size() == 1) return nums[0];
        int l = 0;
        int r = nums.size() - 1;
        // 如果没有rotate
        if (nums[l] < nums[r]) return nums[l];
        //
        while (l <= r) {
            int mid = l + (r - l) / 2;

            // ***有两种情况需要返回，此时一定在断点附近
            if (mid < nums.size() - 1 && nums[mid] > nums[mid + 1]) return nums[mid + 1];
            if (mid >= 0 && nums[mid - 1] > nums[mid]) return nums[mid];

            // ***如果没有返回，说明断点未被找到，所以需要移动l和r
            // 此时 最小值一定在右半边，所以更新l
            if (nums[mid] > nums[l]) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return -1; // 一定能找到
    }
};

/*
[33 M]. search in rotated sorted array， 数组元素不重复
整数数组 nums 按升序排列，数组中的值互不相同。
在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，
例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2]。
给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 

输入：nums = [4,5,6,7,0,1,2], target = 0
输出：4
*/
class FindTargetInRotate {
public:
    // insight: 变种的BS，有意思，体会记住这个方法
    int LaunchII(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;

        while(left <= right) {
            int mid = left + (right - left)/2;
            if (nums[mid] == target) return mid;
            
            // insight: 当左半边有序时，一定满足 nums[left] <= nums[mid]
            if (nums[left] <= nums[mid]) {
                // 如果target在左边有序区间内
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1; // 那么只需要移动right，保证target跑不了
                } else {
                    left = mid + 1; // 否则，更新left，重新来一遍
                }
            } else { // insight: 同上
                // 如果target在右边有序区间内
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
};

// #74. Search in a 2D matrix
// 每一行元素大小递增， 每一列元素也递增
// 这一行的第一个数大于上一行的最后一个数
// *** 难点：更新l&r时，是否要+1。这是根据问题的实际情况的。根据实例判断是否+1
class SearchMatrix2 {
public:
    bool LaunchSolver(vector<vector<int>> &matrix, int target) {
        int n = matrix.size();
        int m = matrix[0].size();

        int l1 = 0;
        int r1 = n - 1;
        // 1st col BS
        // binary search
        while (l1 < r1) {
            int mid1 = l1 + (r1 - l1 + 1) / 2; // 是否+1
            if (matrix[mid1][0] == target) {
                return true;
            } else if (matrix[mid1][0] < target) {
                l1 = mid1;                     // 是否+1
            } else {
                r1 = mid1 - 1;
            }
        }

        // target row BS
        int l2 = 0, r2 = m - 1;
        while (l2 < r2) {
            int mid2 = l2 + (r2 - l2 + 1) / 2;
            if (matrix[l1][mid2] == target) {
                return true;
            } else if (matrix[l1][mid2] < target) {
                l2 = mid2;
            } else {
                r2 = mid2 - 1;
            }
        }
        // 对于只有一行或一列
        if (matrix[l1][l2] == target)
            return true;
        else { return false; }
    }
};

/*
[162 M]. Find Peak Element
二分查找一般是应用在一个有序的序列中
把这个问题中根据题意，一定存在局部最优质，所以可以通过以下逻辑找到一个局部最优。

note: nums[-1] = nums[n] = -∞
note: 相邻元素不相等 nums[i] != nums[i + 1] for all valid i.
Input: nums = [1,2,3,1]
Output: 2, index是2

Key:
    若 nums[i] < nums[i+1]：
    → 右侧是上升趋势，且右边界为 -∞，必定存在一个峰值在右侧
    
    若 nums[i] > nums[i+1]：
    → 左侧是上升趋势（或 i 本身是峰），且左边界为 -∞，必定存在一个峰值在左侧（含 i）
    
    因此，每次都能排除一半区间——这正是二分的基础！
*/
class FindPeak {
public:
    int Solver(vector<int> &nums) {
        int l = 0;
        int r = nums.size() - 1;
        while (l < r) {
            int mid = l + (r - l) / 2;
            // 如果 mid 位置的元素小于其右侧的元素，说明峰值在 mid+1 到 right 之间
            if (nums[mid] < nums[mid + 1]) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        return l;
    }
};

// #240， search target in a matrix
// 每一行递增，每一列递增
class SearchMatrix {
public:
    bool LaunchSolver(const vector<vector<int>> &matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        // 边界处理
        if (m == 0 || n == 0) return false;
        if (matrix[0][0] > target || matrix[m - 1][n - 1] < target)
            return false;

        int j = 0;
        for (int i = m; i > 0 && j < n; --i) {
            if (matrix[m][j] == target) {
                return true;
            } else if (matrix[m][0] > target) {
                continue;
            } else {
                j++;
            }
        }
        return false;
    }
};


/*
[69 E] 计算一个数的平方根。向下取整，即找到一个整数r，即要满足 r*r <= x

Key：用除法代替乘法，避免溢出
Key: 更新 l/r 时要更新成 mid+1/mid-1 ，若更新成 mid，可能进入死循环 l=mid,l<r。就死循环了 
Insight: 需要一两个case 验证细节的正确性
*/
class Solution {
public:
    int Solver(int x) {
        if (x == 0) return 0;
        
        int left = 1, right = x;
        while (left <= right) {
            int mid = left + (right - left) / 2;  // 避免 (left + right) 溢出
            
            // Key：用除法代替乘法，防止 mid * mid 溢出（尤其当 mid > sqrt(INT_MAX) 时）
            if (mid <= x / mid) {  // 等价于 mid * mid <= x，且无溢出风险
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        // 循环结束时 right 是最大的满足 r*r <= x 的整数
        return right;  
        // 下面返回的是 平方最接近 x 的整数。不符合题意
        // return abs(right*right-x) - abs(left*left-x) > 0 ? left:right;
    }
};




#endif  // BINARY_SEARCH_HEADER
