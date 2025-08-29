/*
*
*  *** 表示逻辑上的关键之处
*/
#ifndef ARRAY_ALGS_HEADER
#define ARRAY_ALGS_HEADER
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

// 27 思路：快慢双指针
/*
Input: nums = [0,1,2,2,3,0,4,2], val = 2
Output: 5, nums = [0,1,4,0,3,_,_,_]
Explanation: Your function should return k = 5, with the first five elements of nums containing 0, 0, 1, 3, and 4.
Note that the five elements can be returned in any order.
It does not matter what you leave beyond the returned k (hence they are underscores).
*/

class RemoveElement {
public:
    int LaunchSolver(std::vector<int>& nums, int val) {  
        int k = 0;  // 指针 k 记录不等于 val 的元素应该放置的位置  
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != val) { 
                nums[k] = nums[i];  // 将不等于 val 的元素放到位置 k  
                ++k;  // 指针 k 前移, 保证k之前的元素都不是val
            }  
        }
        return k;  // 返回不等于 val 的元素个数, 同时保证 nums 前介个元素不是val
    }
};

// 26 快慢双指针
/*
一个有序数组，删除其中的重复元素，返回唯一数的个数
Input: nums = [0,0,1,1,1,2,2,3,3,4]
Output: 5, nums = [0,1,2,3,4,_,_,_,_,_]
Explanation: Your function should return k = 5, with the first five elements of nums being 0, 1, 2, 3, and 4 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).
*/
class RemoveDuplicates {
public:
    int LaunchSolver(std::vector<int>& nums) {
        int k = 1;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != nums[i - 1]) {
                nums[k++] = nums[i];
            }
        }
        return k;
    }
};

// 80 快慢指针
/**
输入是一个有序数组
Input: nums = [0,0,1,1,1,1,2,3,3]
Output: 7, nums = [0,0,1,1,2,3,3,_,_]
Explanation: Your function should return k = 7, with the first seven elements of nums being 0, 0, 1, 1, 2, 3 and 3 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores). 
*/
class RemoveDuplicatesII {
public:
    int LaunchSolver(vector<int>& nums) {
        if (nums.empty() || nums.size() < 2) {
            return nums.size();
        }
        int k = 2;
        for (int i = 2; i < nums.size(); ++i) {
            if (nums[i] != nums[k - 2]) {
                nums[k++] = nums[i]; 
            }
        }
        return k;
    }
};

// 169
/*
Given an array nums of size n, return the majority element.
The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.

Input: nums = [2,2,1,1,1,2,2]
Output: 2
*/
class MajorityElements {
public:
    // 时间O(n), 空间O(n)
    int LaunchSolver(vector<int>& nums) {
        unordered_map<int, int> hash;
        for (auto i : nums) {
            hash[i]++;
        }
        // itr 记录出现次数最多的元素
        auto most_itr = hash.begin();
        for(auto itr = most_itr; itr != hash.end(); itr++){
            if (itr->second > most_itr->second) {
                most_itr = itr;
            }
        }
        return most_itr->first;
    }

    // 简化后的 Boyer-Moore 投票算法  如恶化理解 ??
    // 实践O(n), 空间O(1)
    int LaunchSolverII(std::vector<int>& nums) {  
        int candidate = 0;
        int count = 0;
        for (int num : nums) {  
            if (count == 0) {  
                candidate = num;  
            }  
            count += (num == candidate) ? 1 : -1; 
        }  
        return candidate;  // 返回候选人作为多数元素  
    }
};

// 189. Rotate Array
// 多种解法
/*
Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]
*/
class RotateArray {
public:
    // 解法一：使用额外的空间，计算读与写的索引 O(n), O(n)
    // 在纸上画出来，思路马上出来，高效
    void LaunchSolver(vector<int> &nums, int k) {
        int n = nums.size();
        k = k % n;  // ? 取余， 3%7=3
        vector<int> tmp(nums.begin(), nums.end());

        for (int i = 0; i < n - k; ++i) {
            nums[i + k] = tmp[i];
        }
        for (int i = n - k; i < n; ++i) {
            nums[i - (n - k)] = tmp[i];
        }
        return;
    }
    // 解法二：三次排序，先逆序排，分别对于前k个元素和剩余元素，再逆序排列
    // O(2n),O(0.5n)
    void LaunchSolver2(vector<int> &nums, int k) {
        int n = nums.size();
        k = k % n;
        Reverse(nums, 0, n - 1);
        Reverse(nums, 0, k - 1);
        Reverse(nums, k, n - 1);
        return;
    }

private:
    // 翻转nums中[l,...,r]闭区间元素
    void Reverse(vector<int> &nums, int l, int r) {
        // 思路：头尾指针，交换元素，后更新位置，重复这个过程
        while (l < r) {
            int tmp = nums[l];
            nums[l] = nums[r];
            nums[r] = tmp;
            l++;
            r--;
        }
    }
};

// 121. Best Time to Buy and Sell Stock
/*
Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
*/
// 解法见 dp_algos.h


// 122. Best Time to Buy and Sell Stock II
// 思路 Greedy
// 贪心策略: 因为不限制次数，所以在每个上涨的子区间（即 prices[i] < prices[i+1]）都进行交易。 
// 也就是说，只要今天的价格比昨天的价格高，就在昨天买入，今天卖出。 这种策略可以保证获得所有可能的利润。
/*
 Input: prices = [7,1,5,3,6,4]
 Output: 7
 Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
 Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.
 Total profit is 4 + 3 = 7.
*/
class BestTime2BuyAndSellStockII {
public:
    // O(n) O(1)
    int LaunchSolver(vector<int>& prices) {
        int max_profit = 0;
        for (int i{1}; i < prices.size(); ++i) {
            // 只要今天的价格比昨天高，就计算利润并累加到总利润中
            if (prices[i] > prices[i - 1]) {
                max_profit += prices[i] - prices[i - 1];
            }
        }
        return max_profit;
    }
};

// 55 JumpGame
// Greedy & DP
/*
You are given an integer array nums. You are initially positioned at the array's first index,
and each element in the array represents your maximum jump length at that position.
Input: nums = [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
*/
class JumpGame{
public:
    // Greedy：关键思路是：从前往后遍历数组，同时维护一个变量来记录当前能够到达的最远位置。
    // 如果在遍历过程中，发现某个位置的最远跳跃距离能够到达或超过数组的最后一个索引，则返回 true；
    // 如果遍历完数组都没有找到这样的位置，则返回 false。
    bool LaunchSolver(const vector<int>& nums) {
        int n = nums.size();

        int farthest = 0; // 维护这个变量 表示当前能够到达的最远距离  
        for (int i = 0; i < n - 1; ++i) {
            farthest = std::max(farthest, i + nums[i]); // 维护 最远距离 * 
            // 如果当前位置已经超出了当前能够到达的最远距离，则无法继续跳跃  
            if (i >= farthest) {  
                return false;  
            } 
            // 如果在遍历过程中，最远距离已经能够到达或超过最后一个位置，则可以提前返回true  
            if (farthest >= n - 1) {  
                return true;  
            }  
        }  

        return true; // 当数组长度是1时，始终返回true
    }
};

// 45 jump game ii
/*
给定一个非负整数数组，你最初位于数组的第一个位置。
数组中的每个元素代表你在该位置可以跳跃的最大长度。
你的目标是使用最少的跳跃次数到达数组的最后一个位置。返回跳跃次数
Greedy : 贪心算法的基本思想是每一步都选择最优（或看起来最优）的选择，从而希望最终能得到全局最优解。

// 不理解，很不好理解
*/
class JumpGameII{
public:
    int LaunchSolver(vector<int>& nums) {
        int n = nums.size();  
        if (n <= 1) return 0;  // 如果数组长度小于等于1，则不需要跳跃  
        int jumps = 0;  
        int currentEnd = 0;  // 当前能够到达的最远位置  
        int farthest = 0;    // 在当前跳跃范围内能够到达的最远位置

        for (int i = 0; i < n - 1; ++i) {
            farthest = std::max(farthest, i + nums[i]);  // 更新在当前跳跃范围内能够到达的最远位置
            // 如果当前位置达到了当前能够到达的最远位置
            if (i == currentEnd) { 
                ++jumps;  // 需要进行一次新的跳跃
                currentEnd = farthest;  // 更新当前能够到达的最远位置 
                // 如果当前最远位置已经到达或超过数组的最后一个位置，可以提前结束循环 
                if (currentEnd >= n - 1) break;
            }
        }
        return jumps;
    }
};

// 274 记住这个解法，没啥逻辑
/* 
给你一个整数数组 citations ，其中 citations[i] 表示研究者的第 i 篇论文被引用的次数。计算并返回该研究者的 h 指数。
h 指数的定义：h 代表“高引用次数” ，一名科研人员的 h 指数 是指他（她）至少发表了 h 篇论文，
并且 至少 有 h 篇论文被引用次数大于等于 h 。
如果 h 有多种可能的值，h 指数 是其中最大的那个
*/
class HIndex {
public:
    int Launch(vector<int>& nums){
        // 首先对数组进行降序排序
        std::sort(nums.begin(), nums.end(), std::greater<int>());
        int h = 0;
        for (int i = 0; i < nums.size(); ++i) {
            // * 记住，没啥原因
            if (nums[i] >= i + 1) {
                h = i + 1;
            } else {
                break;
            }
        }
        return h;  
    }
};

// 238. Product of Array Except Self
// 思路很直接
class Product {
public:
    // 不使用除法， 看不懂  神奇** 
    std::vector<int> LaunchII(std::vector<int>& nums) {  
        int n = nums.size(); 
        std::vector<int> res(n, 1);  

        // 左侧乘积数组  
        int leftProduct = 1;  
        for (int i = 0; i < n; ++i) {  
            res[i] *= leftProduct;  
            leftProduct *= nums[i]; 
        }  

        // 右侧乘积数组，并同时计算最终结果 
        int rightProduct = 1;  
        for (int i = n - 1; i >= 0; --i) {  
            res[i] *= rightProduct;  
            rightProduct *= nums[i];  
        }  
        return res;  
    }

    // 右侧乘积数组，Time Limit Exceeded x
    std::vector<int> LaunchIII(std::vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, 1);
        for (int i = 0; i < n; ++i) {
            int left = acc(nums, 0, i-1);
            int right = acc(nums, i+1, n-1);
            res[i] = left * right;
        }
        return res;
    }
private:
    int acc(vector<int>& nums, int l, int r) {
        long long res = 1;
        if (l > r) return res;
        for (int i = l; i <= r; ++i) {
            res *= nums[i];
        }
        return res;
    }
};

// 13 hashmap 
/*
罗马数字包含以下七种字符: I， V， X， L，C，D 和 M。

字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000

例如， 罗马数字 2 写做 II ，即为两个并列的 1 。12 写做 XII ，即为 X + II 。 27 写做  XXVII, 即为 XX + V + II 。

通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 IIII，而是 IV。数字 1 在数字 5 的左边，
所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：

    I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
    X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。 
    C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。

测试用例皆符合罗马数字书写规则
*/
// 核心： 从右向左，如果当前值小于前一个值，则用减法，否则是加法。记住就好了，** 
class RomanToInt {
public:
    int Launch(string s) {
        // 创建一个映射表来存储罗马字符和对应的整数值  
        unordered_map<char, int> romanMap = {  
            {'I', 1}, 
            {'V', 5},  
            {'X', 10},  
            {'L', 50},  
            {'C', 100},  
            {'D', 500},  
            {'M', 1000} 
        };  
        int result = 0; 
        int prevValue = 0;  

        // 从右到左遍历字符串（这样更容易处理减法规则）  
        for (int i = s.length() - 1; i >= 0; --i) {  
            int currentValue = romanMap[s[i]];  
            // 如果当前值小于前一个值，说明需要应用减法规则  
            if (currentValue < prevValue) {  
                result -= currentValue;  
            } else {  
                result += currentValue;  
            }  
            prevValue = currentValue;  
        }  
        return result; 
    }
};

// 12 
/*
七个不同的符号代表罗马数字，其值如下：
符号	值
I	1
V	5
X	10
L	50
C	100
D	500
M	1000
罗马数字是通过添加从最高到最低的小数位值的转换而形成的。将小数位值转换为罗马数字有以下规则：

    如果该值不是以 4 或 9 开头，请选择可以从输入中减去的最大值的符号，将该符号附加到结果，减去其值，然后将其余部分转换为罗马数字。
    如果该值以 4 或 9 开头，使用 减法形式，表示从以下符号中减去一个符号，例如 4 是 5 (V) 减 1 (I): IV ，9 是 10 (X) 减 1 (I)：IX。仅使用以下减法形式：4 (IV)，9 (IX)，40 (XL)，90 (XC)，400 (CD) 和 900 (CM)。
    只有 10 的次方（I, X, C, M）最多可以连续附加 3 次以代表 10 的倍数。你不能多次附加 5 (V)，50 (L) 或 500 (D)。如果需要将符号附加4次，请使用 减法形式。

*/
class IntToRoman {
public:
    string Launch(int num) {
        // 定义一个罗马数字和对应整数值的映射表, 这个映射表是有序的
        vector<pair<int, string>> romanValues = {
            {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},  
            {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},  
            {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"},  
            {1, "I"}  
        };  

        string roman = "";  
        // 从最高值开始遍历映射表 * 记住这个算法
        for (const auto& rv : romanValues) {
            while (num >= rv.first) {  
                roman += rv.second;  
                num -= rv.first;
            }  
        }
        return roman;  
    }
};

// 125
/*
如果在将所有大写字符转换为小写字符、并移除所有非字母数字字符之后，短语正着读和反着读都一样。则可以认为该短语是一个 回文串 。

字母和数字都属于字母数字字符。

输入: s = "A man, a plan, a canal: Panama"
输出：true
解释："amanaplanacanalpanama" 是回文串。
*/
class ValidPalindrome {
public:
    bool Launch(string s) {
        // 用于存储处理后的字符串
        string processed;  

        // 遍历输入字符串, 如果字符是字母或数字，则转换为小写并添加到处理后的字符串中  
        for (char c : s) {
            if (isalnum(static_cast<unsigned char>(c))) {  
                processed += tolower(static_cast<unsigned char>(c));  
            }
        }

        // 使用双指针法检查处理后的字符串是否是回文  
        int left = 0;  
        int right = processed.size() - 1;  
        while (left < right) {  
            if (processed[left] != processed[right]) {  
                return false;  
            }  
            left++;  
            right--;  
        }  

        return true;  
    }
};

// 3 [m] Longest Substring Without Repeating Characters
/*
输入: s = "abcbacbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。

这个实现的更新过的，更新前的很难理解
*/
// 滑动窗口 Set
class LongestSubstringWithoutRepeatingCharacters {
public:
    int Launch(string s) {
        int n = s.length();  
        unordered_set<char> seen;  
        int max_length = 0;  
        int left = 0; // 左指针  
        int right = 0; // 右指针

        while (right < n) {
            if (seen.find(s[right]) == seen.end()) {
                seen.insert(s[right]);
                max_length = max(max_length, right - left + 1); // 更新最大长度  
                right++;
            } else {
                seen.erase(s[left]);
                left++;
            }
        }

        return max_length;  
    }
};

// 159 [mid] Longest Substring with At Most Two Distinct Characters
/*
 滑动窗口 Map
 输入: s = "eceba"
 输出: 3，"ece" 是长度为 3 的最长子串，且最多只有 2 个不同字符。
*/

class LongestSubstringwithAtMostTwoDistinctCharacters {
public:
    int LaunchSolver(string s) {
        int n = s.length();
        int left = 0;
        int right = 0;
        unordered_map<char, int> count; // 记录当前窗口中字符及出现次数
        int max_length = 2;
        if (n < 3) return n;

        while (right < n) {
            count[s[right]]++;

            while (count.size() > 2) {
                count[s[left]]--;
                if (count[s[left]] == 0) {
                    count.erase(s[left]);
                }
                left++;
            }

            max_length = max(max_length, right - left + 1); // 更新最大长度  
            right++;
        }

        return max_length;
    }
};

// 438 [m] Find All Anagrams in a String
/*
固定长度滑动窗口 + 辅助容器（非map非set） ***
输入: s = "cbaebabacd", p = "abc"
输出: [0,6]
*/
class FindAllAnagramsinaString {
public:
    vector<int> LaunchSolver(string s, string p) {
        vector<int> res;
        int s_l = s.length();
        int p_l = p.length();
        vector<int> s_rec(26,0);
        vector<int> p_rec(26,0);

        for (int i = 0; i < p_l; ++i) {
            s_rec[s[i]-'a']++;
            p_rec[p[i]-'a']++;
        }

        for (int i = 0; i <= s_l - p_l; ++i) {
            if (s_rec == p_rec) {
                res.push_back(i);
            }

            if (i < s_l - p_l) { // 防止越界
                s_rec[s[i]-'a']--;  // 移除左边界元素   
                s_rec[s[i+p_l]-'a']++;  // 添加右边界元素 
            }
 
        }
        return res;
    }
};

// 228 
/*
输入：nums = [0,1,2,4,5,7]
输出：["0->2","4->5","7"]
解释：区间范围是：
[0,2] --> "0->2"
[4,5] --> "4->5"
[7,7] --> "7"
*/
// 理解：返回若干个区间，其中每个区间中的数值是连续的
class SummaryRanges{
public:
    vector<string> Launch(vector<int>& nums) {
        vector<string> res;
        if (nums.empty()) return res;
        for (int i = 0; i < nums.size(); ++i) {
            int start = nums[i];
            while (i + 1 < nums.size() && nums[i+1] == nums[i] + 1 ) {
                ++i;
            }
            int end = nums[i];

            //找到一个符合条件的区间后，放入res中
            if (start == end) {
                res.push_back(to_string(start));
            } else {
                res.push_back(to_string(start) + "->" + to_string(end));
            }
        }
        return res;
    }
};


// 209. *** Minimum Size Subarray Sum. 无序数组找元素和大于等于target的最小长度
// 思路：滑动窗口, 理解这个窗口是如何滑动的
// mid, O(n), O(1)
class MinSubArrayLenSolver {
public:
    int LaunchSolver(int target, const vector<int> &nums) {
        int l = 0;
        int r = 0;
        int sum = nums[l]; // 维护sum的定义：sum表示从l到r所有元素之和
        int res = INT_MAX;
        while (l < nums.size() && r < nums.size()) {
            if (sum >= target) {
                res = min(r - l + 1, res);
                if (l == r) return res;
                sum -= nums[l++];  // 符合条件，但是没有到头, 移动l
            } else {
                r++;
                if (r >= nums.size()) break;
                sum += nums[r];  // 不符合条件，移动r
            }
        }
        return res == INT_MAX ? 0 : res;
    }
};

// 3. *** 最长无重复子序列 O(n)
class LongestSubString {
public:
    int LaunchSolver(string s) {
        int i = 0;
        int j = 0;
        int res = 0;
        // ***维持map的定义: map<字符，该字符最晚出现的位置>
        unordered_map<char, int> mp;
        for (; i < s.length(); ++i) {
            // 如果map中含有当前字符
            if (mp.find(s[i]) != mp.end() && mp[s[i]] >= j) {
                j = mp[s[i]] + 1; // ***将j移到当前字符上一次出现的位置再+1
                mp[s[i]] = i; // ***更新当前字符最迟出现的位置
                // 如果map中没有当前字符
                // ***[实现时，先实现map不存在该字符的情况，更容易形成逻辑]
            } else {
                mp[s[i]] = i;
                res = max(res, i - j + 1);
            }
        }
        return res;
    }
};

// #88 merge sorted array,
// input: nums1 = [2,5,6,0,0,0], m = 3, nums2 = [1,2,3], n = 3
// output: [1,2,2,3,5,6]
// 逻辑是：两个数组分别作有效数尾部向头部滑动，比较当前两个位置的大小，将大的移动到数组1的尾部
// 后更新指针。
class MergeSortedArray {
public:
    void LaunchSolver(vector<int> &nums1, int m, vector<int> &nums2, int n) {
        int i = m - 1;
        int j = n - 1;
        int k = m + n - 1;

        while (i >= 0 && j >= 0) {
            if (nums1[i] > nums2[j]) {
                nums1[k--] = nums1[i--];
            } else {
                nums1[k--] = nums2[j--];
            }
        }
        // 剩下的如果nums2 还有元素，直接放进nums1 中即可，因为最初两个数组都是排序好的
        while (j >= 0) {
            nums1[k--] = nums2[j--];
        }
    }
};

// 283. Move zeroes
// 维护变量的定义，
class MoveSeores {
public:
    void LaunchSolver(vector<int> &nums) {
        int k = 0; // ***[0...k) 中均为非零元素，
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != 0) {
                swap(nums[i], nums[k]);
                k++;
            }
        }
    }
};

// 75. Sort Color
// 思路1：技术排序。当匀速种类很小时，用一个数组记录每种的个数
// O(n). O(k)
class SortColor {
public:
    void LauncSolver(vector<int> &nums) {
        int freq[3] = {0};
        for (int i = 0; i < nums.size(); ++i) {
            freq[i]++;
        }

        // 有了每种颜色的频数，相同颜色的放在一起
        int global_id = 0; // 全局id，写入的唯一地址
        for (int i = 0; i < freq[0]; ++i) {
            nums[global_id++] = 0; // 第一个颜色
        }
        for (int i = 0; i < freq[1]; ++i) {
            nums[global_id++] = 1; // 第二个颜色
        }
        for (int i = 0; i < freq[2]; ++i) {
            nums[global_id++] = 2; // 第三个颜色
        }
    }

    // 思路2：三路快排。***有了示意图后，细心维护变量定义就没有难度***
    // 记住快排的示意图，以下逻辑就出来了
    // O(n). O(1)
    void LaunchSolver2(vector<int> &nums) {
        int zero = -1; // [0,...,zero] 都为0
        int two = nums.size(); // [two,...,n-1] 都为0
        // i 指向当前元素
        for (int i = 0; i < nums.size() - 1;) {
            if (nums[i] == 1) {
                i++;
            } else if (nums[i] == 0) {
                swap(nums[i++], nums[++zero]);
            } else {
                swap(nums[i], nums[--two]);
            }
        }
    }
};

// #11. container with most water
/*
思路：***insight：由于每次移动指针，容器的宽度都会减小，
因此我们只需要考虑高度较小的那个指针向中间移动，才有可能得到更大的面积。
如果将高度较大的指针向中间移动，那么新的容器高度一定不会超过原来的高度，
而宽度却变小了，因此面积一定会变小。
*/ 
// mid, O(n), O(1)
class MaxWater {
public:
    int LaunchSolver(vector<int> &height) {
        int max_area = 0;
        int left = 0, right = height.size() - 1;
        
        while (left < right) {
            int area = min(height[left], height[right]) * (right - left);
            max_area = max(max_area, area);
            
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        
        return max_area;
    }
};

// 34. Find first and last position of Elem in a Sorted array
// 思路：通过BS找到第一个target的位置m；然后从m开始向前向后分别移动一个指针，找到起始位置
/*
Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]
*/
class SearchRange {
public:
    vector<int> Solver(vector<int> &nums, int target) {
        if (nums.size() == 0) return vector<int> {-1, -1};
        int head = 0;
        int tail = nums.size() - 1;
        while (head <= tail) {
            int mid = head + (tail - head) / 2;
            if (nums[mid] == target) {
                return SearchStartEnd(nums, mid);
            } else if (nums[mid] < target) {
                head = mid + 1;
            } else {
                tail = mid - 1;
            }
        }
        return vector<int> {-1, -1};
    }

private:
    // def：从nums的m位置开始分别向前、向后移动一个指针，找到起始位置
    // m: 通过BS找到的target的一个位置
    vector<int> SearchStartEnd(vector<int> &nums, int m) {
        int m_l = m;
        int m_r = m;
        while (m_l - 1 >= 0 && nums[m_l] == nums[m_l - 1])
            m_l--;
        while (m_r + 1 < nums.size() && nums[m_r] == nums[m_r + 1])
            m_r++;
        return vector<int> {m_l, m_r};
    }
};


// 215. Kth largest elements
// insight: 使用最大堆，pop出第k个就是了结果了。很直接的逻辑，但是你要知道这个数据结构
// O(n), O(n)
class KthLargest {
public:
    // 解法一：最大堆 
    int Solver(vector<int> &nums, int k) {
        // 1) max healp
        priority_queue<int, vector<int>, /*用小于运算符 < */less<int>> pq;
        for (auto itr = nums.begin(); itr != nums.end(); itr++) {
            pq.push(*itr);
        }

        // 2) pop出前k个元素
        for (int i = 1; i < k; ++i) {
            pq.pop();
        }
        return pq.top();
    }
    // 解法二：https://leetcode.com/submissions/detail/357548105/
    // TODO
};

// 31. 下一个permutation
// 找规律题，****记住这个规律
// 找到这个结论，代码就有了****
class NextPermutaion {
public:
    void LaunchSolver(vector<int> &nums) {
        int n = nums.size();
        // 1). 从右向左找到递增序列第一处下降的位置delt
        int delta = -1;
        for (int i = n - 2; i >= 0; --i) {
            if (nums[i] < nums[i + 1]) {
                delta = i;
                break;
            }
        }

        if (delta == -1) {
            reverse(nums, 0, n - 1);
        } else {
            // 2). 从delt右边，找到比[delta]大的最小元素[gamma]，swap两者
            int gamma = n - 1;
            for (int i = n - 1; i > delta; --i) {
                if (nums[i] > nums[delta]) {
                    gamma = i;
                    break;
                }
            }

            swap(nums[delta], nums[gamma]);
            // 3). delt右边元素reverse
            reverse(nums, delta + 1, n - 1);
        }
    }

private:
    void reverse(vector<int> &nums, int l, int r) {
        while (l < r) {
            swap(nums[l++], nums[r--]);
        }
    }
};

#include <algorithm>
// 56. [m] Merge intervals
/*
Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
*/
// 逻辑有了，代码就有了。注意1).lambda函数的使用 2).
class MergeIntervals {
public:
    vector<vector<int>> Solver(vector<vector<int>> &intervals) {
        vector<vector<int>> res;
        if (intervals.size() == 0) return res;
        if (intervals.size() == 1) {
            res.push_back(intervals[0]);
            return res;
        }
        // 使用 lambda 和自定义比较函数
        auto compare = [](vector<int> &a, vector<int> &b) { return a[0] < b[0]; };
        sort(intervals.begin(), intervals.end(), compare);

        res.push_back(intervals[0]);

        int i = 1;
        // insight: 这里使用 while 循环的目的是 过程中的 intervals 大小可能会变
        while (i < intervals.size()) {
            // 语义上last会被修改，所以此处last为ref ***
            vector<int> &last = res.back();
            // 如果当前区间与last不重叠，则添加到res中
            if (last[1] < intervals[i][0]) {
                res.push_back(intervals[i]);
            } else { // 如果有重叠，则更新last
                last[1] = max(last[1], intervals[i][1]);
            }
            i++;
        }
        return res;
    }
};

// 435. Non-overlapping Intervals
/*
删除最少个数的区间，使得剩下的区间不重叠。

For example, [1, 2] and [2, 3] are non-overlapping.
Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
Output: 1
Explanation: [1,3] can be removed and the rest of the intervals are non-overlapping.
*/
/*
如何识别基于排序的贪心算法题目：

    求最大/最小： 题目通常要求求最大值、最小值、最多、最少等。
    局部最优： 可以通过选择局部最优解来达到全局最优解。
    排序预处理： 通常需要对输入数据进行排序，才能应用贪心策略。

*/
class EraseOverlapIntervals {
public:
    int Solver(vector<vector<int>>& intervals) {
        // 先排序
        auto compare = [](const vector<int>& a, const vector<int>& b){ return a[1] < b[1]; };
        sort(intervals.begin(), intervals.end(), compare);

        // greedy
        int count = 0;
        int end = intervals[0][1];
        for (int i{1}; i < intervals.size(); ++i) {
            if (intervals[i][0] < end) {
                count++;
            } else {
                end = intervals[i][1];
            }
        }

        return count;
    }
};


// 1909. [m] Remove One Element to Make the Array Strictly Increasing
// 给你一个下标从 0 开始的整数数组 nums，如果恰好删除 一个 元素后，剩余元素的序列是 严格递增 的，
// 那么请你返回 true，否则返回 false。如果数组本身已经是严格递增的，也返回 true。
class CanBeIncreasing {
public: 
    bool Solver(vector<int>& nums) {
        bool flag = false;
        if (nums.size() == 1) return true;
        for (int i{1}; i< nums.size(); ++i) {
            if (nums[i] <= nums[i - 1]) {
                if (flag) return false;

                // 判断 nums[i], nums[i-1], nums[i-2]  ***
                if (i - 2 >=0 && nums[i] <= nums[i - 2]) {
                    nums[i] = nums[i - 1];
                    flag = true;
                } else {
                    // 不需要显式地删除 nums[i-1]， 
                    // 但 flag = true 确保了我们已经进行了一次“删除”操作，
                    // 后续如果再遇到不递增的情况，函数就会直接返回 false。
                    flag = true;
                }
            }
        }
        return true;
    }
};

#endif // ARRAY_ALGS_HEADER
