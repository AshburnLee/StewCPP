#ifndef DP_ALGOS_HEADER
#define DP_ALGOS_HEADER

#include <vector>
#include <unordered_set>
#include <functional>
#pragma once
using namespace std;

/*
* DP, 想不通时，****还是画递归树，画递归树，画递归树****
*/

/*
[121 E]. Best Time to Buy and Sell Stock
选一天买，选另一天卖

Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.

这个问题 DP 并不优, 选择贪心
*/
class BestTime2BuyAndSellStock {
public:
    // O(n) O(1) 
    // 一次遍历法，在遍历的同时，记录当前时间最小 price 和最大 profit
    int Solver(vector<int>& prices) {
        int maxProfit = 0;
        int minPrice = INT_MAX;
        for (int price : prices) {
            minPrice = min(minPrice, price); // 更新最低买入价格
            maxProfit = max(maxProfit, price - minPrice); // 更新最大利润
        }

        return maxProfit;
    }
    // DP O(n) O(n) 
    // int LaunchSolverDP(vector<int>& prices) {
    //     int n = prices.size();
    //     if (n <= 1) return 0;
        
    //     // 记录第i天卖出的最大利润
    //     std::vector<int> dp(n, 0);
    //     int min_price = prices[0];

    //     for (int i{1}; i < n; ++i) {
    //         // 更新目前为止最低价格
    //         min_price = std::min(min_price, prices[i - 1]);
    //         // 计算第i天卖出时的最大利润
    //         dp[i] = std::max(dp[i - 1], prices[i] - min_price);
    //     }
    //     return dp[n - 1];
    // }
};




/*  状态机DP State Machine DP
[123 H]. Best Time to Buy and Sell Stock III
给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。
设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。

Input: prices = [3,3,5,0,0,3,1,4]
Output: 6

Key：记住这个
*/

class BestTime2BuyAndSellStockIII {
public:
    // DP : O(n) O(1)
    int Solver(vector<int>& prices) {
        // 状态： 定义，全部是收益
        int buy1 = INT_MIN; // 第一次买入股票时的 最大收益
        int sell1 = 0;      // 第一次卖出股票后的 最大收益。
        int buy2 = INT_MIN; // 第二次买入股票时的 最大收益（基于第一次卖出后的收益）。
        int sell2 = 0;      // 第二次卖出股票后的 最大收益。
        // 状态转义：
        for (int price : prices) {
            buy1 = max(buy1, -price);         // 第一次不买入，buy1；买入，收益为 -price (因为花钱买入)。
            sell1 = max(sell1, buy1 + price); // 第一次不卖出；sell1；卖出，收益为之前的 buy1 加上当前价格。
            buy2 = max(buy2, sell1 - price);  // 第二次不买入，buy2；买入，收益为之前的 sell1 减去当前价格。
            sell2 = max(sell2, buy2 + price); // 第二次不卖出；sell2；卖出，收益为之前的 buy2 加上当前价格。
        }
        return sell2;
    }
};


// 188. Best Time to Buy and Sell Stock IV (最多 K 次交易) HUAWEI
    

/*
[70 E] climbing stairs
给定一个楼梯的阶数 n，每次可以爬 1 阶或 2 阶，求有多少种不同的方法可以爬到楼顶
画出递归树 理解状态和状态转移方程

Insight: 
    发现 dp[i] 只与 dp[i-1] 和 dp[i-2] 有关，因此我们只需要
    保存当前状态的前两个状态即可，不需要使用一个数组来保存所有的状态。
*/
class ClimbStairs {
public:
    int Solveri(int n) {
        // 走num节台阶有多少种做法
        function<int(int)> func = [&](int num){
            if (num == 0 || num == 1) return 1;
            return func(num-1) + func(num - 2);
        };
        return func(n);
    }

    // 根据递归实现，发现含有重复计算的子问题，后改为DP：
    // 状态定义：mem[i]走i阶台阶有多少中走法
    // insight: 因为每次可以爬 1 或 2 个台阶，所以到达第 i 阶楼梯的方法数等于:
    // 到达第 i-1 阶楼梯的方法数和到达第 i-2 阶楼梯的方法数之和。即 mem[i] = mem[i-1] + mem[i-2]。
    int Solverii(int n) {
        vector<int> mem(n + 1, -1);
        mem[0] = 1;
        mem[1] = 1;
        for (int i = 2; i <= n; ++i) {
            //  【走n-1阶再走一步】+ 【走n-2阶再走两步】
            mem[i] = mem[i - 1] + mem[i - 2];
        }
        return mem[n];
    }

    // 优化方法
    // 如此空间复杂度优化为 O(1)。
    int Solveriii(int n) {
        if (n <= 1) return 1;
        // 初始化斐波那契数列的前两个数
        // 初始的 pre = f(0), curr = f(1)
        int pre = 1, curr = 2;
        for (int i = 3; i <= n; ++i) {
            int tmp = pre + curr;
            // 更新pre和curr的值，为计算下一个斐波那契数做准备
            pre = curr;
            curr = tmp;
        }
        return curr;
    }
};

// #120. [mid] 三角型从顶到底最短路径和
// 注意审题：只能走到下一层相邻的节点
class Triangle {

public:
    int LaunchRecursion(vector<vector<int>> &triangle) {
        // 走到底层[0][0] 的最短路径长是：
        return solver(triangle, 0, 0);
    }

public:
    // inplace DP, 自底向上的DP, O(1) space
    int LaunchSolverDP1(vector<vector<int>> &triangle) {
        int n = triangle.size();
        // 从 n-2 开始，即倒数第二行开始，因为最后一行的+1越界。
        for (int i = n - 2; i >= 0; --i) {
            for (int j = 0; j < triangle[i].size(); ++i) {
                triangle[i][j] += min(triangle[i + 1][j], triangle[i + 1][j + 1]);
            }
        }
        return triangle[0][0];
    }

    // non-inplace DP, O(n) space
    int LaunchSolverDP3(vector<vector<int>>& triangle) {
        int n = triangle.size();
        // 初始化为triangle的最后一行
        vector<int> dp(triangle[n - 1]);  // 这个triangle[n-1] 是triangle的最后一行 ***
        for (int i = n - 2; i>=0; --i) {
            for (int j = 0; j <= i; ++j) {
                // 通过一个实例 感受为什么写入 dp[j] ***
                dp[j] = triangle[i][j] + min(dp[j], dp[j+1]);
            }
        }
        return dp[0];
    }

    // const DP, 自底向上的DP
    int LaunchSolverDP2(vector<vector<int>> &triangle) {
        int n = triangle.size();
        // mem，用于存储从三角形底部到当前行的最小路径和
        vector<int> mem(n, -1); // init
        for (int i = 0; i < n; ++i) {
            mem[i] = triangle[n - 1][i];
        }
        // 动态转移方程：三角形底部到当前行的最小路径和=triangle当前位置值 + min(mem[j], mem[j+1])
        for (int i = n - 2; i >= 0; --i) {
            for (int j = 0; j <= i; ++j) {
                mem[j] = triangle[i][j] + min(mem[j], mem[j + 1]);
            }
        }
        return mem[0];
    }

private:
    // ***画出递归树，逻辑就有了，子顶向下
    int solver(vector<vector<int>> &tri, /*行index=*/int i, /*列index=*/int j) {
        if (i > tri.size() - 1) { return 0; }
        return min(solver(tri, i + 1, j), solver(tri, i + 1, j + 1)) + tri[i][j];
    }
};

// [64 M] Minimum Path Sum, 二维 grid 从左上角到右下角，路径和，求最短 
// 定义状态：dp[i][j]:从左上角到[i][j]的最短路径sum
// step1, 矩形grid 先计算第一行和第一列
// step2, grid[i][j] = grid[i][j] + min(grid[i][j-1], grid[i-1][j]);
// step3, 返回 grid[n-1][m-1]
class MinPathSum {
public:
    // inplace DP , O(1) space
    int LaunchSolver(vector<vector<int>> &grid) {
        int m = grid.size();
        int n = grid[0].size();
        // 第一行
        for (int i = 1; i < m; i++)
            grid[i][0] += grid[i - 1][0];
        // 第一列
        for (int i = 1; i < n; i++)
            grid[0][i] += grid[0][i - 1];

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++)
                grid[i][j] += min(grid[i][j - 1], grid[i - 1][j]);
        }
        return grid[m - 1][n - 1];
    }
};

/*
[62 m] Unique Paths，一个机器人在一个二维的 grid 中，从左上角走到右上角，有多少种不同的路径
状态定义：dp[i][j]: 从左上角到[i][j] 有多少条路径
step1, 矩形grid 先计算第一行和第一列  
step2, grid[i][j] = grid[i][j-1] + grid[i-1][j];
step3, 返回 grid[n-1][m-1]
*/
class UniquePath {
public:
    // in place DP, O(1) space
    int LaunchSolver(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            dp[i][0] = 1;
        }
        for (int i = 0; i < n; ++i) {
            dp[0][i] = 1;
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
            }
        }
        return dp[m - 1][n - 1];
    }
};

/*
[198 M] 抢房子，不能连抢相邻的房子

对于每个房子，我们有两个选择：抢或不抢。
如果我们选择抢第i个房子，那么我们就不能抢第i-1个房子，因此最高金额为 dp[i-2] + nums[i]。
如果我们选择不抢第i个房子，那么最高金额就是 dp[i-1]。
我们取这两个选择中的较大值作为 dp[i] 的值。

Key: 状态的定义：dp[i]表示抢 house[0...i] 可获得最大受益
Key：状态转移方程：i>=2时，max_p[i] = max(max_p[i-2] + nums[i], max_p[i-1]);
Insight: 
    计算 dp[i] 只需要 dp[i-1] 和 dp[i-2] 的值。
    这意味着我们不需要保存所有 dp[0] 到 dp[i] 的值，只需要保存最近的两个值即可。
*/

class RobHouse {
public:
    // 解法一  O(n) space
    // 状态的定义：dp[i]表示抢 house[0...i] 可获得最大受益 ***
    int SolverDP1(vector<int> &nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        vector<int> dp(n, 0);
        dp[0] = nums[0];
        dp[1] = max(dp[0], nums[1]);
        for (int i = 2; i < n; ++i) {
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
        }
        return dp[n - 1]; // 不要迷糊了，dp 的长度是n，
    }

    // 解法二  O(1) space 优
    /*
    观察解法一 依赖关系：
    
    计算 dp[i] 只需要 dp[i-1] 和 dp[i-2] 的值。
    这意味着我们不需要保存所有 dp[0] 到 dp[i] 的值，只需要保存最近的两个值即可。 ***
    */
    int SolverDP2(vector<int> &nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        int pre_max = nums[0];
        int curr_max = max(nums[0], nums[1]);
        for (int i = 2; i < n; ++i) {
            int tmp = curr_max;
            curr_max = max(pre_max + nums[i], curr_max);
            pre_max = tmp;
        }
        return curr_max;
    }
};

// #96. Unique BST
// *** 不要纠结于bst，这是个DP问题。由子问题求最终问题
class UniqueBST {
public:
    int NumTree(int n) {
        // 定义mem[n]表示以[1~n]为nodes的BST有多少个
        vector<int> mem(n + 1, 0); // 需要考虑mem[0]，所以n+1
        mem[0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; j++) {
                mem[i] += mem[j] * mem[i - j - 1];
            }
        }
        return mem[n];
    }
};

/*
二维DP
[221 M]. Maximum square
给定一个由 '0' 和 '1' 组成的二维矩阵，找到只包含 '1' 的最大正方形，返回其面积
Input: matrix = [
  ["1","0","1","0","0"],
  ["1","0","1","1","1"],
  ["1","1","1","1","1"],
  ["1","0","0","1","0"]
]
Output: 4  // 2×2 正方形

状态定义：dp[i][j]: 以 (i, j) 为右下角的全 '1' 正方形的最大边长
step1. 确定第一行第一列
step2. 状态的确定：
   当 m[i][j]==0, dp[i][j]=0;
   当 m[i][j]!=0, dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])+1;
*/
class MaximumSquare {
public:
    int LaunchSolver(vector<vector<char>> &matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int res = 0;

        for (int i = 0; i < n; ++i) {
            dp[0][i] = matrix[0][i] - 48;
            res = max(res, dp[0][i]);
        }
        for (int i = 0; i < m; ++i) {
            dp[i][0] = matrix[i][0] - 48;
            res = max(res, dp[i][0]);
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = matrix[i][j] == '0'
                        ? 0
                        : min(min(dp[i - 1][j], dp[i - 1][j - 1]), dp[i][j - 1]) + 1;
                res = max(res, dp[i][j]);
            }
        }
        return res * res;
    }
};

/*
[300 M]. Longest Increasing SubSequence  贪心
*** dp[i]表示以 nums[i] 结尾的最长递增序列

注意这里的子序列是指保持元素原来相对位置的序列
[0,1,0,3,2,3] 的递增子序列可以是：
[0,1,2,3]，每个元素在原来的序列中并不一定连续。
*/
class LIS {
public:
/*
case：nums = [10,9,2,5,3,7,101,18]
x	  tail（变化）	    说明
--------------------------------------------------
10	  [10]	           初始
9	  [9]	           替换 10（长度1的末尾可更小）
2	  [2]	           替换 9
5	  [2,5]	           5 > 2，接在末尾 → 长度2
3	  [2,3]	           替换 5（长度2的末尾从5→3，更优）
7	  [2,3,7]	       7 > 3，接末尾 → 长度3
101	  [2,3,7,101]	   接末尾 → 长度4
18	  [2,3,7,18]	   替换 101（长度4末尾从101→18）

Insight：不关心具体子序列，只维护各长度下的最优（最小）末尾，以最大化扩展潜力

Key：
    nums = [1, 2, 2, 2, 3, 4]
    lower_bound(2) -> index1, 第一个 >= 2 的位置
    upper_bound(2) -> index4，第一个 > 2 的位置
*/
    int Sovler(vector<int>& nums) {
        vector<int> rise;
        for (int num : nums) {
            // lower_bound 返回第一个 ≥ x 的迭代器
            auto itr = lower_bound(rise.begin(),rise.end(),num);

            if (itr == rise.end()){
                rise.push_back(num);
            } else {
                *itr = num;
            }
        }
        return rise.size();
    }

    int LaunchSolver(vector<int> &nums) {
        if (nums.size() == 0) { return 0; }
        // dp[i]表示以nums[i]结尾的最长递增序列，初始化为1表示每个元素自身都构成一个长度为1的递增子序列
        vector<int> dp(nums.size(), 1);

        int max_length = 1; // 记录最长的递增子序列长度
        for (int i = 1; i < nums.size(); ++i) {
            // insight: 理解状态转移方程，你要首先理解什么是子序列**
            for (int j = 0; j < i; ++j) {
                if (nums[i] > nums[j]) {
                    // 如果nums[i]大于nums[j]，那么我们可以将nums[i]添加到
                    // 以nums[j]结尾的递增子序列中，从而得到一个更长的递增子序列。
                    // 这句话是由内而外的总结。而不是根据它来实现算法的 **
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            max_length = max(dp[i], max_length); // update max-length
        }

        return max_length;
    }

};

// #139. Word Break
/*
Input: s = "applepenapple", wordDict = ["apple","pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
*/
// 状态定义：dp[i] 表示字符串 s 的前 i 个字符能否被拆分
class WordBreak {
public:
    bool Solver(string s, vector<string>& wordDict) {
        int n = s.length();
        vector<bool> dp(n+1, false);
        dp[0] = true; // 空串可以被拆分，最小子问题，从这里出发
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());

        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                // insight: 状态转移方程
                // 如果前缀 j 可以被拆分，且子串在字典中
                if (dp[j] && wordSet.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n];
    }
};

/*
[53 M]. Max subarray

最序列是连续的子序列
Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: The subarray [4,-1,2,1] has the largest sum 6.

子数组：连续的一段元素（不是子序列）
最大和：所有可能的连续子数组中和的最大值

Kadane's Algorithm 是一种动态规划算法，用于寻找一维数组中 最大子序列和的问题
Key：当前的最大值，要么重新开始，要么延续
*/
class MaxSubArray {
public:
    int Solver(const vector<int> &nums) {
        int n = nums.size();
        if (n == 0) return 0;

        int max_global = nums[0]; // 记录全局最大
        int max_curr = nums[0];   //记录以当前位置为结尾的最大子序列之和

        for (int i = 1; i < n; ++i) {
            // Key: dp 的核心意思是 这里的 max_curr 一直保存着前面的值
            max_curr = max(/*扩展=*/max_curr + nums[i], /*重新开始=*/nums[i]);
            // max_global 始终将现在是max 与之前的max作比较
            max_global = max(max_global, max_curr);  
        }

        return max_global;
    }
};


/*
[322 M]. Coin Change
给定不同面额的硬币 coins 和总金额 amount，计算凑成总金额所需的最少硬币个数；若无法凑出，返回 -1

Input: coins = [1,2,5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1

状态定义：dp[i] 表示凑成金额i的最少硬币数量
状态转义方程：是个循环，for (auto coin: coins) {}，
dp[0] = 0
*/
class CoinChange {
public:
    int LaunchSolver(vector<int>& coins, int amount) {
        // amount+1 表示不可达的状态，因为面值最小是1，所以dp[i] 最大可以是amount
        vector<int> dp(amount+1, amount+1);
        dp[0] = 0; // 构成金额0，所需要的硬币数为dp[0]=0
        for (int i = 1; i <= amount; ++i) {
            for (auto coin: coins) {
                if (i >= coin) {
                    // 为什么求 dp[i] 要与dp[i], dp[i-coin]+1 取最小值？因为 dp[i] 的值可能是个局部值。
                    // 注意这里有个内循环 ***
                    dp[i] = min(dp[i], dp[i-coin]+1);
                }
            }
        }
        // 如何最后这个值 仍然是不可达的最大值，返回-1
        return dp[amount] > amount ? -1 : dp[amount];
    }
};

/*
二维DP
[1143 M]. Longest Common Subsequence
定两个字符串 text1 和 text2，返回它们最长公共子序列的长度.
注意：子序列：不改变字符相对顺序，但可删除部分字符得到的新序列  

Input: text1 = "abcde", text2 = "ace" 
Output: 3  ，The longest common subsequence is "ace"

状态定义：dp[i][j]：text1[0:i] 与 text2[0:j] 的LCS长度  
状态转义方程：相同则左上角的值+1，不同则取 max(上, 左)
主持状态：初始：dp[0][:] = dp[:][0] = 0

Key：
     a b c d e
  ------------
  |0 0 0 0 0 0 
a |0 1 1 1 1 1
c |0 1 1 2 2 2
e |0 1 1 2 2 3

Key：问题转化为二维数组
*/
class LongestCommonSubsequence {
public:
    int LaunchSolver(string text1, string text2) {
        int m = text1.size(), n = text2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (text1[i-1] == text2[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;  // 字符相同，LCS长度+1
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);  // 取较大值
                }
            }
        }
        return dp[m][n];
    }
};

#endif // DP_ALGOS_HEADER
