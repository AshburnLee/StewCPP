#ifndef STRING_ALGOS_HEADER
#define STRING_ALGOS_HEADER

#pragma once

using namespace std;

// 415. 大数相加。思路：手工计算的模拟
// 核心：将char转为int：'3' - '0' = 3
//      将int转为char：3 + '0' = '3'
// LeetCode 415 题（Add Strings）
class AddString {
public:
    string Launch(string num1, string num2) {
        string result = "";
        int i = num1.length() - 1;
        int j = num2.length() - 1;
        int carry = 0;

        while (i >= 0 || j >= 0 || carry) {
            int digit1 = (i >= 0) ? num1[i] - '0' : 0;  // 将char转为int：'3' - '0' = 3
            int digit2 = (j >= 0) ? num2[j] - '0' : 0;

            int sum = digit1 + digit2 + carry;
            carry = sum / 10;
            int digit = sum % 10;

            result += to_string(digit); // 将 int 转化为 string

            i--;
            j--;
        }

        reverse(result.begin(), result.end());
        return result;
    }
};

// LeetCode 43 题（Multiply Strings）.思路模拟手动计算
class MulString {
public:
    string Launch(string num1, string num2) {
        int m = num1.length();
        int n = num2.length();
        vector<int> product(m + n, 0);

        // 从 num1 和 num2 的末尾开始遍历
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                int digit1 = num1[i] - '0';
                int digit2 = num2[j] - '0';
                int p1 = i + j, p2 = i + j + 1;  // 每一步的结果在 product 数组中的位置，确实如此
                int sum = digit1 * digit2 + product[p2];

                product[p2] = sum % 10;
                product[p1] += sum / 10;
            }
        }

        // 构建结果字符串
        string result = "";
        for (int digit : product) {
            if (!(result.length() == 0 && digit == 0)) {
                result += to_string(digit);
            }
        }

        return result.length() == 0 ? "0" : result;
    }
};

// 最长数字串
/*
 给定一个字符串 s，其中包含字母、数字和其他字符。 
 目标是找到 s 中所有由连续数字字符组成的子串，并返回其中长度最长的那个子串。 
 如果有多个长度相同的最长数字子串，通常返回第一个找到的。
 例："a123bc4567def890" 返回 "4567"
*/

class LongestNumber {
public:
    string Solver(string ins) {
        string longest = "";
        string curr = "";

        for (auto c: ins) {
            if (isdigit(c)) {
                curr+=c;
            } else {
                if (curr.length() > longest.length()) {
                    longest = curr;
                }
                curr = "";
            }
        }

        // 到此，有两种情况，1. 最后一个字符不是数字，返回longest 2. 是数字，需要再次比较 curr和longest
        if (curr.length() > longest.length()) {
            longest = curr;
        }

        return longest;
    }
};

#endif // STRING_ALGOS_HEADER
