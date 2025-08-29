#ifndef DFS_ALGOS_HEADER
#define DFS_ALGOS_HEADER

#pragma once
#include <assert.h>

/*
* 回溯 问题
* Permutaion 问题
* Combination 问题
* 将递归树画出来 有助理解
*/

using namespace std;

// #17. 数字对应的字母组合
// 从递归树中找结论，根据结论写代码：
// 1，当index=digits.size() 时，找到一个组合，添加到res，return
// 2，进入每个节点后，要遍历当前数字对应的所有字母，for循环，每次循环中又要构建节点，节点中再循环
// insight：通过在纸上画出函数调用返回，跳进跳出，就理解了，然后基于此记住他
class LetterCombinations {
private:
    vector<string> res;
    string letter[10] = {
            /*按键0=*/"", /*按键1=*/"", /*按键2=*/"abc", 
            /*按键3=*/"def", /*按键4=*/"ghi", /*按键5=*/"jkl", 
            /*按键6=*/"mno", /*按键7=*/"pqrs", /*按键8=*/"tuv", 
            /*按键9=*/"wxyz"};
    // dfs(原始字符串"23"，字符串中第几个元素【搜索的位置】，形成的组合), combo是res中每个元素的形成
    void dfs(string &digits, int index, string combo) {
        // 如果当前的index已经在结尾了，则添加combo到res
        if (index == digits.length()) {
            // 此时combo已经是问题的一个解了
            res.push_back(combo);
            return;
        }
        // 开始：取出当前位置对应的字母，“23”，则取出abc
        string cur = letter[digits[index] - '0']; // index=0, cur='abc'
        // 对每个字母进行尝试
        for (int i = 0; i < cur.size(); ++i) {
            dfs(digits, index + 1, combo + cur[i]);
        }
        return;
    }

public:
    // 如“23”， 则对应着“abc”和“def”字母两两组合
    vector<string> LaunchSolver(string digits) {
        if (digits.length() == 0) { return res; }
        dfs(digits, 0, "");
        return res;
    }
};

// #46. 找到所有的排列
// Input: nums = [1,2,3]
// Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

// Insight：Perms(nums[0...n-1]) = {取出一个数字} + Perms(nums[ {0...n-1} - 这个数字 ])
// 逻辑见图纸
class Permutation {
private:
    vector<vector<int>> res;
    vector<bool> used; // 判断nums[i]是否被使用过了
    // p是一个保存了index这么多个元素的排列，
    // index表示p中元素个数
    // 向这个排列的末尾添加 第index+1个 元素，获得一个有 index+1 个元素的排列
    void GeneratePerm(const vector<int> &nums, /*递归深度=*/int index, vector<int> &p) {
        // index 大小等于递归的深度
        // 如果 开始时，index个元素已经等于nums的个数了，表示找到了这样一个排列
        if (index == nums.size()) {
            res.push_back(p);
            return;
        }

        // 递归逻辑：
        // 这里的for循环代表了广度，其中有递归，所以是深度优先的
        for (int i = 0; i < nums.size(); ++i) {  // 广度
            // 当前的nums[i] 不在p中时，才进行
            if (!used[i]) {
                p.push_back(nums[i]);
                used[i] = true;
                GeneratePerm(nums, index + 1, p); // 递归函数保证自动回去，其他变量需要时得手动回去
                
                p.pop_back(); // 回溯的含义体现在此：还原 ***
                used[i] = false; // 回溯的含义体现在此：还原 ***
            }
        }
        return;
    }

public:
    vector<vector<int>> Perm(vector<int> &nums) {
        if (nums.size() == 0) { return res; }
        used = vector<bool>(nums.size(), false);
        vector<int> p; // 初始化一个空排列
        GeneratePerm(nums, 0, p);
        return res;
    }
};

// #77. Combination
// n=4,k=2, 即从1,2,3,4 中选出2个数的组合
// 进入dfs，先判断递归终止条件，后开始递归
// insight：求解所有组合，记住这个回溯的模式, 通过在纸上画出函数调用返回，跳进跳出，就理解了，然后基于此记住他
class Combination {
private:
    vector<vector<int>> res;
    //
    void BackTrack(int n, int k, int start, vector<int> &c) {
        // 先考虑终止条件
        if (c.size() == k) { // 结果中已经有两个数了，不需要再找了
            res.push_back(c);
            return;
        }
        for (int i = start; i <= n; ++i) {  // 广度
            c.push_back(i);
            BackTrack(n, k, i + 1, c);  // 从i+1 开始，因为数字不能重复选
            c.pop_back();  /// 体现了“回” ***
        }
        return;
    }

public:
    vector<vector<int>> LaunchSolver(int n, int k) {
        // 边界条件
        if (n <= 0 || k <= 0 || k > n) { return res; }
        // 进入递归
        vector<int> c;
        BackTrack(n, k, 1, c); // 进入dfs，
        return res;
    }
};

// 39. [m] Combination Sum
/*
Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
注意：同一个数字可以使用多次
体会“回”。
*/
class CombinationSum {
public:
    vector<vector<int>> LaunchSolver(vector<int>& candidates, int target) 
    {
        vector<vector<int>> res;
        vector<int> curr_combination;
        backtracing(candidates, target, 0, curr_combination, res);
        return res;
    }
private:
    void backtracing(vector<int>& candidates, 
                        int target, 
                        int start_idx, 
                        vector<int>& curr_combination,
                        vector<vector<int>>& res) 
        {
            if (target == 0 ) {
                res.push_back(curr_combination);
                return;
            }
            if (target < 0) {return;}
            for (int i = start_idx; i < candidates.size(); ++i) {
                curr_combination.push_back(candidates[i]);
                // 这里是关键，仍然是 i, 因为可以重复使用同一个元素 ***
                backtracing(candidates, target - candidates[i], i, curr_combination, res);
                curr_combination.pop_back(); /// 体现了“回” ***
            }
        }
};

// #78. 找到所有子集, 回溯BackTracking,基本题，基本方法，背下来
// 递归树是啥样的? 与#77相比，#77 是从4个中取2个，而本题是从4个中取任意个，所以循环k
// 即使不理解，也要把过程背下来
class SubSets {
private:
    vector<vector<int>> res;
    void FindASubset(vector<int> &nums, int k, int s, vector<int> &path) {
        if (path.size() == k) {
            res.push_back(path);
            return;
        }
        // 当前子集中的元素个数固定为k, i 表示从第几个元素开始起
        for (int i = s; i < nums.size(); ++i) {
            path.push_back(nums[i]);
            FindASubset(nums, k, i + 1, path);
            path.pop_back(); /// 体现了“回”
        }
    }

public:
    // 本题是从4个中取任意个，所以 for (k=0)循环，每次循环都是一个#77 问题
    vector<vector<int>> LaunchSolver(vector<int> &nums) {
        vector<int> path;
        // i表示子集中的元素个数，从0个开始，
        for (int k = 0; k < nums.size(); ++k) {
            FindASubset(nums, k, 0, path);
        }
    }
};

// #79. word search. 回溯
// 画树，明确递归函数的定义
class WordSearch {
private:
    int m_move[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    vector<vector<bool>> visited;
    int m;
    int n;

    bool is_valid(int x, int y) { return x >= 0 && x < m && y >= 0 && y < n; }

    // 从[start_x][start_y] 开始，找word中第cur_id 个元素
    bool SearchWord(vector<vector<char>> &board, string word,
                    /*char index of Word =*/int cur_id,
                    int start_x, int start_y) {
        if (cur_id == word.size() - 1) {
            return board[start_x][start_y] == word[cur_id];
        }

        if (board[start_x][start_y] == word[cur_id]) {
            visited[start_x][start_y] = true; 
            // 每个位置有 4个方向分别移动
            for (int i = 0; i < 4; ++i) {
                int new_x = start_x + m_move[i][0];
                int new_y = start_y + m_move[i][1];
                if (is_valid(new_x, new_y) && !visited[new_x][new_y]
                        && SearchWord(board, word, cur_id + 1, new_x, new_y)) {
                    return true;
                }
            }
            visited[start_x][start_y] = false;  /// 体现了“回”
        }
        return false;
    }

public:
    bool LaunchSolver(vector<vector<char>> &board, string word) {
        m = board.size();
        n = board[0].size();
        assert(m > 0 && n > 0);

        for (int i = 0; i < m; ++i) {
            visited.push_back(vector<bool>(n, false));
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (SearchWord(board, word, 0, i, j)) { return true; }
            }
        }
        return false;
    }
};

// 200 number of island
/*
本质上求图中联通分量
*/
class NumIsLands {
private:
    int num_rows;
    int num_cols;
public:
    int LaunchSolver(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;
        num_rows = grid.size();
        num_cols = grid[0].size();
        int res = 0;

        // 判断每一个位置，
        for (int i = 0; i < num_rows; ++i) {
            for (int j = 0; j < num_cols; ++j) {
                // 判断每一个是1的位置
                if (grid[i][j] == '1') {
                    res++;
                    dfs(grid, i, j);  // 从这个位置开始 dfs
                }
            }
        }
        return res;
    }
private:
    void dfs(vector<vector<char>>& grid, int x, int y) {
        if (x < 0 || x >= num_rows || y < 0 || y >= num_cols || grid[x][y] == '0' ){
            return;
        }

        // 这个实现的关键在于 DFS 函数会将与外层循环中遇到的 '1' 相邻的所有 '1' 都改为 '0'，
        // 从而避免了外层循环的重复考察。 ***
        grid[x][y] = '0';

        dfs(grid, x + 1, y);
        dfs(grid, x - 1, y);
        dfs(grid, x, y + 1);
        dfs(grid, x, y - 1);
    }
};

// #22. Generate Paretheses
/*
数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合
*/
// *** 画出回溯的树形图，总结出结论，根据结论写代码
// 找到3条结论，就有代码了。不需要所有情况，中途会剪枝
// **** 函数中的每个if都是一个节点的一个分支，两个if，则有两个分支；
// 如果if不满足，则节点没有这个分支，即剪枝***
// 注意：其中的string s是传入拷贝，保证树的每个分支得到各自的结果***
class GenerateParetheses {
private:
    // 树节点的定义：l表示“（”个数，r表示“）”个数，n为输入，s是当前的括号组合，res最终结果
    void dfs(int l, int r, int n, string s, vector<string> &res) {
        // 1). 当s的长度是n的2倍，找到了一个valid组合
        if (s.length() == 2 * n) {
            res.push_back(s);
            return;
        }
        // 2). 进入node时，“（”的个数小于n，则添加“（”
        if (l < n) { dfs(l + 1, r, n, s + "(", res); }
        // 3). 进入node时，“（”的数量大于“）”，可以添加“）”
        if (r < l) { dfs(l, r + 1, n, s + ")", res); }
    }

public:
    vector<string> LaunchSolver(int n) {
        vector<string> res;
        dfs(0, 0, n, "", res);
        return res;
    }
};

// #113. Path sum II  【返回所有路径是啥】
// dfs中节点有三种情况：空，叶子，非叶子
// 注意：**** 其中的vector<int> path是传入拷贝，保证树的每个分支得到各自的结果
class PathSumII {
private:
    // 节点定义：从当前root到叶节点，路径为target的路径是path
    void dfs(TreeNode *root, int target, vector<vector<int>> &res,
            vector<int> path) {
        if (!root) return;
        if (root->left == nullptr && root->right == nullptr) {
            if (root->val == target) {
                path.push_back(root->val);
                res.push_back(path);
            }
        }
        path.push_back(root->val);
        dfs(root->left, target - root->val, res, path);
        dfs(root->right, target - root->val, res, path);
    }

public:
    vector<vector<int>> LaunchSolver(TreeNode *root, int target) {
        vector<vector<int>> res;
        vector<int> path;
        dfs(root, target, res, path);
        return res;
    }
};

// #437. Path sumIII, 路径不一定包含root，当只能是从父节点到子节点【返回路径的个数】
// leetcode上的case integer overflow了
class PathSumIII {
private:
    // 节点定义：从node开始找到路径为sum的路径个数
    int dfs(TreeNode *node, int sum) {
        if (!node) { return 0; }
        int res = 0;
        // 如果当前节点为sum，即找到一个这样的路径。
        if (node->val == sum) { res += 1; }
        res += dfs(node->left, sum - node->val);
        res += dfs(node->right, sum - node->val);
        return res;
    }
    int FindPath(TreeNode *root, int sum) {
        if (!root) { return 0; }
        // **** 不限于从root开始，的递归方法：
        return dfs(root, sum) + FindPath(root->left, sum)
                + FindPath(root->right, sum);
    }

public:
    int LaunchSolver(TreeNode *root, int target_sum) {

        return FindPath(root, target_sum);
    }
};



#endif // DFS_ALGOS_HEADER
