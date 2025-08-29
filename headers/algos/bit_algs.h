/*
*
*  *** 表示逻辑上的关键之处
*/
#ifndef BIT_ALGS_HEADER
#define BIT_ALGS_HEADER
#pragma once

#include <limits.h>  // CHAR_BIT 
#include <numeric>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;


// #67. binary sum
// insight: carry是关键，当carry=3 时，这一位的ret是3%2=1，下一位的carry是 3/2=1
class BinarySum {
public:
    string Launch(string a, string b) {
        int i = a.size() - 1;
        int j = b.size() - 1;
        int carry = 0;
        string ret = "";
        while (i >= 0 || j >= 0 || carry != 0) {
            if (i >= 0) {
                carry += a[i] == '0'? 0 : 1;
                i--;
            }
            if (j >= 0) {
                carry += b[j] == '0' ? 0 : 1;
                j--;
            }

            ret = ((carry % 2) == 0 ? "0" : "1") + ret;
            carry /= 2;
        }
        return ret;
    }
};

// #190. Reverse Bits
/*
Input: n = 00000010100101000001111010011100
Output:    964176192 (00111001011110000010100101000000)
Explanation: The input binary string 00000010100101000001111010011100 
represents the unsigned integer 43261596,

The input must be a binary string of length 32
*/
class ReverseBits {
public:
    uint32_t Launch(uint32_t n) {
        uint32_t res = 0;
        // 确定每一位
        // insight：** 列出每一步的过程，见下注释
        for (int i = 0; i < 32; ++i) {
            res =  res << 1;  // 把上一次确定了的为向左移，把这次循环的bit位置腾出来
            res = res | (n & 1);  // (n&1) 是得到n的最低位，列出32次的结果，从上到下就是n的逆序
            n = n >> 1;  // 
        }
        return res;
    }
};

// #191. Number of 1 Bits
/*
返回一个数 二进制表示中位数是1 的个数
*/
// insight: 有了#190 的理解，这个就很好理解了
class Number1Bits {
public:
    int Hamming(int n){
        int res = 0;
        for (int i = 0; i < sizeof(n) * CHAR_BIT; ++i) {
            res += (n & 1);
            n >>= 1;
        }
        return res;
    }
};


// #136. Single Number
/*
nums中, every element appears TWICE except for one. Find that single one.

Input: nums = [4,1,2,1,2]
Output: 4
*/
class SingleNumber {
public:
    int Doit(vector<int>& nums) {
        int res = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            // XOR 的性质：自反性 a XOR b XOR b = a
            // bit 同则0，不同则1
            res = res ^ nums[i];
        }
        return res;
    }
};

// #137. Single Number II
/*
nums中, every element appears Three times except for one. Find that single one.

Input: nums = [0,1,0,1,0,1,99]
Output: 99
*/
class SingleNumberII {
public:
    int Doit(vector<int>& nums) {
        int ones = 0;
        int twos = 0;
        for (auto num : nums) {
            ones = (ones ^ num) & ~twos;
            twos = (twos ^ num) & ~ones;
        }
        return ones;
    }
};

#endif // BIT_ALGS_HEADER
