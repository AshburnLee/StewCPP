#ifndef SEARCH_HEADER
#define SEARCH_HEADER
#pragma once

#include <vector>

using namespace std;

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

// #35. easy Search insert position
/*
给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，
返回它将会被按顺序插入的位置。二分查找的复杂度是O(nlogn)

insight：这个题就是为了应用二分查找，给你设计了个题，
tricky：唯一细想的是最后返回的是那个指针的位置！这个位置的决定与题目条件有关
*/
class SearchInsert {
public:
    int LaunchSolver(vector<int> &nums, int target) {
        int left = 0, right = nums.size() - 1;  
        while (left <= right) {  
            int mid = left + (right - left) / 2;  
            if (nums[mid] == target) {  
                return mid;  
            } else if (nums[mid] < target) {  
                left = mid + 1;  
            } else {  
                right = mid - 1;  
            }  
        }  
        return left;  // 要始终返回left
    }
};

// #704. #374. easy Binary search
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

// #33. search in rotated sorted array， 数组元素不重复
/*
整数数组 nums 按升序排列，数组中的值 互不相同 。
在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，
例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。
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

// #1. two sum
class TwoSum {
public:
    vector<int> LaunchSolver(vector<int> &nums, int target) {
        unordered_map</*item=*/int, /*index=*/int> mp;
        // 逻辑：遍历nums, 在map中找target-nums[i], 找到就退出，
        // 所以平均上不用遍历一遍，即可找到答案
        for (int i = 0; i < nums.size(); ++i) {
            int sec = target - nums[i];
            if (mp.find(sec) != mp.end()) { return vector<int> {i, mp[sec]}; }
            mp[nums[i]] = i; // 将没有匹配的元素放进map, 而不是一开始就创建map
        }
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
                l1 = mid1; // 是否+1
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

// #162. Find Peak Element
// 二分查找一般是应用在一个有序的序列中
// 把这个问题中根据题意，一定存在局部最优质，所以可以通过以下逻辑找到一个局部最优。
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

// 4. Median of Two Sorted Arrays。找到两个有序序列的中位数 [hard,hold...]
class MedianTwoSortedArrays {

};


#endif // SEARCH_HEADER
