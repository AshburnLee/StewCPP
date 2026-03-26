/*
*
*  *** 表示逻辑上的关键之处
*/
#ifndef HASH_ALGS_HEADER
#define HASH_ALGS_HEADER
#pragma once

#include <limits.h>
#include <numeric>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

/*
[383 E]. [e] Random note
给出两个string，ransomNote和magazine，问是否可以用magazine中的字符拼出完整的ransomNote
 Input: ransomNote = "aa", magazine = "aab"
 Output: true

map 基本用法, 注意:Key: 'a' 不存在map中时，自动插入 m['a'] = 0（int{} = 0）
注意：map.count() 用于判断某个键是否在map中，避免在map中不判断就直接访问
*/

class RandomNote {
public:
    bool Solver(string ransomNote, string magazine) {
        unordered_map<char, int> m;
        for (auto c : magazine) {
            m[c]++;
        }
        for (auto c : ransomNote) {
            if (--m[c] < 0) {
                return false;
            }
        }
        return true; // 如果没有返回false，则返回true
    }
};

/*
[128 M] Longest Consecutive Sequence

Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: 最长连续元素序列是 [1, 2, 3, 4]. 所以返回 4.

Key：由题意，与元素相对顺序无关，元素是否重复也无关，所以使用 unordered_set，即可
Key: 首先判断 num-1 的那个数知否存在，如果不存在，表示 num 是一个连续序列的第一个数，然后，num 一定在 set 中，循环判断连续的值是否存在。
Key: 对 set 做循环遍历，而非原数组。因为set 已经去重了。
*/
class LogestConsecutiveSequence {
public:
    int LaunchSolver(vector<int>& nums) {
        unordered_set<int> record(nums.begin(), nums.end());
        int res = 0;
        // Key: 循环遍历的对象是set 而非原数组。
        for (auto num : record) {
            if (record.find(num - 1) == record.end()) {
                int curr_num = num;
                int curr_long = 1;

                while(record.find(curr_num + 1) != record.end()) {
                    curr_num++;
                    curr_long++;
                }
                res = max(res, curr_long);
            }
        }
        return res;
    }
};


/*
[599 E]. Minimum Index Sum of Two Lists
两个字符串数组 list1 和 list2，找出在两个数组中都出现的字符串，使得它们的索引和最小，返回所有这样的字符串。

list1 = ["Shogun", "Tapioca Express", "Burger King", "KFC"]  
list2 = ["KFC", "Shogun", "Burger King"]

→ 共同字符串：
  "Shogun": 0+1=1
  "Burger King": 2+2=4  
  "KFC": 3+0=3
→ 最小索引和=1 → 结果：["Shogun"]

使用 map 记录 {string:index} 映射
*/
class MinimunIndexSumLists{
public:
    vector<string> Solver (vector<string>& list1, vector<string>& list2) {
        unordered_map<string, int> string2id;
        for (int i = 0; i<list1.size(); ++i){
            string2id[list1[i]] = i;
        }

        int min_sum = INT_MAX;
        vector<string> res;
        for (int j = 0; j < list2.size(); ++j) {
            // 首先要在map里面，才能比较
            if (string2id.count(list2[j])) {
                int sum = string2id[list2[j]] + j;
                if (sum < min_sum) {
                    min_sum = sum;
                    res = {list2[j]};  // 清空之前的 res，将当前更小的加入
                } else if (sum == min_sum) {
                    res.push_back(list2[j]); // 记录相同小的sum
                } else {
                    // 啥也不干
                }
            }
        }
        return res;
    }
};


#endif // HASH_ALGS_HEADER
