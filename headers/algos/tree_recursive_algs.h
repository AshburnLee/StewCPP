#ifndef RECURSION_ALGS_HEADER
#define RECURSION_ALGS_HEADER
#pragma once

#include <vector>
#include "../utils/tree_node.h"
using namespace std;

// #50. pow(x, n) 求x的n次幂
class RecursivePow {
public:
    double LaunchSolver(double x, int n) {
        // 递归终止
        if (n == 0) return 1.f;
        // 特例
        if (x == 0.f) return 1.f;
        // 当n为负数时，n当然可以是负数
        if (n < 0) {
            n = -n;  // error: -2147483648 cannot be represented in type 'int
            x = 1.0 / x;
        }
        // 递归主体
        double half = LaunchSolver(x, n / 2);
        double res = half * half;
        return n % 2 == 0 ? res : res * x;
    }
};

// #104. easy 二叉树最大深度
// 理解关键：画出树形结构，*** 树形结构节点定义是啥，那么这个函数就应该写成啥。
// insight: 递归函树中调用自己的位置，理解为这个位置的子问题已经被解决。***
class MaxDepth {
private:
    int CalculateMax(TreeNode *root) {
        // 当节点为空时的定义：
        if (!root) { return 0; }
        // 节点定义：1加上左右子树深度的最大值
        return 1 + max(CalculateMax(root->left), CalculateMax(root->right));
    }

public:
    int LaunchSolver(TreeNode *root) { return CalculateMax(root); }
};

// #226. Invert BT
/*
一个节点的左右子树换位置
*/
// Insight: 递归函数中调用自己的位置，表示对应的子问题已经得到解决，基于此，解决当前问题。
class InvertBT {
private:
    TreeNode *Invert(TreeNode *root) {
        // 终止条件
        if (root == nullptr) return nullptr;

        // 关键：*** 先swap root，后递归；或者先递归，后swap
        swap(root->left, root->right);
        Invert(root->left);
        Invert(root->right);

        return root; // 反转之后，root不变
    }

public:
    TreeNode *LaunchSolver(TreeNode *root) { return Invert(root); }
};

// #112. Path sum. 
/*
判断该树中是否存在 根节点到叶子节点 的路径，这条路径上所有节点值相加等于目标和 targetSum
*/
class PathHasSum {
private:
    // 节点定义：以当前节点为根的子树是否含有路径和为sum的路径
    bool CheckSum(TreeNode *root, int sum) {
        // 当前节点有3中情况
        // 1. 递归终止条件，当cur root为空
        if (root == nullptr) return false;

        // 2. root不是空，且没有子节点
        if (root->left == nullptr && root->right == nullptr) {
            return sum == root->val;
        }
        // 3. 当root 有子节点，insight: 递归判断有无 sum - root->value 这个值
        return CheckSum(root->left, sum - root->val)
                || CheckSum(root->right, sum - root->val);
    }

public:
    bool LaunchSolver(TreeNode *root, int sum) { return CheckSum(root, sum); }
};

// #100. same tree
class IsSameTree {
public:
    bool LaunchIsSameTree(TreeNode *root1, TreeNode *root2) {
        // 递归终止
        if (!root1 && !root2) {
            return true;
            // 关键：** 只需判断当前根节点，其他交给递归
        } else if (root1 && root2 && root1->val == root2->val) {
            return LaunchIsSameTree(root1->left, root2->left)
                    && LaunchIsSameTree(root1->right, root2->right);
        } else { // 一个是空，一个不是空 或，都不空但val不同, 那一定same
            return false;
        }
    }
};

// #257. 返回所有从root到根的路径
// ***体会如何使用递归函数的返回值

// #129. Sum Root to Leaf Numbers.树中所有的从root到leaf的路径，之和
class SumRoot2LeafNumbers{
public:
    int Solver(TreeNode* root) {
        return dfs(root, "");
    }
private:
    int dfs(TreeNode* node, string curr_path) {
        if (!node) return 0;
        curr_path += to_string(node->val);

        if (!node->left && !node->right) {
            return stoi(curr_path);
        }
        return dfs(node->left, curr_path) + dfs(node->right, curr_path);
    }
};

#endif // RECURSION_ALGS_HEADER
