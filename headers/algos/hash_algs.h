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

// #383. [e] Random note
/*
给出 连个string，ransomNote,  magazine，问是否可以用magazine中的字符拼出完整的ransomNote
 Input: ransomNote = "aa", magazine = "aab"
 Output: true
*/
// map 基本用法
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

// 128.  [mid] Longest Consecutive Sequence
/*
Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: 最长连续元素序列是 [1, 2, 3, 4]. 所以返回 4.
*/
class LogestConsecutiveSequence {
public:
    int LaunchSolver(vector<int>& nums) {
        unordered_set<int> record(nums.begin(), nums.end());
        int res = 0;

        for (auto num : nums) {
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

#endif // HASH_ALGS_HEADER
