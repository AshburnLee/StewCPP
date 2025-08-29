#ifndef MATH_ALGOS_HEADER
#define MATH_ALGOS_HEADER

#include <vector>
#include <unordered_set>
#pragma once
using namespace std;

// #9. 是否是回文数
/*
Input: x = 121
Output: true

Input: x = -121
Output: false

Input: x = 10
Output: false
*/
class isPalindrome {
public:
    bool Solve(int x){
        // 特殊情况先处理
        if (x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }
        // insight: 使用 x 的末尾(末尾数值是x随循环向前)构造 reverse
        // 直到x不再大于reverse们就可以判断了
        int reverse = 0;
        while (x > reverse) {
            reverse = reverse * 10 + x % 10; // *10 是进位, + x % 10 是个位
            x /= 10;
        }

        return /*当x长度是偶数*/x == reverse || /*当x长度是奇数*/x == reverse / 10;
    }
};

#endif // MATH_ALGOS_HEADER
