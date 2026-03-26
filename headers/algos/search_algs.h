#ifndef SEARCH_HEADER
#define SEARCH_HEADER
#pragma once

#include <vector>

using namespace std;


/*
[1 E]. two sum

Key：固定一个值，找另一个
将没有匹配的元素放进 map, 而不是一开始就创建 map
*/
class TwoSum {
public:
    vector<int> LaunchSolver(vector<int> &nums, int target) {
        unordered_map</*item=*/int, /*index=*/int> mp;
        // 逻辑：遍历nums, 在map中找 target-nums[i], 找到就退出，
        // 所以平均上不用遍历一遍，即可找到答案
        for (int i = 0; i < nums.size(); ++i) {
            int sec = target - nums[i];
            if (mp.find(sec) != mp.end()) { return vector<int> {i, mp[sec]}; }
            // 将没有匹配的元素放进 map, 而不是一开始就创建 map
            mp[nums[i]] = i; 
        }
        return vector<int>{};
    }
};


// 4. Median of Two Sorted Arrays。找到两个有序序列的中位数 [hard,hold...]
class MedianTwoSortedArrays {

};


#endif // SEARCH_HEADER
