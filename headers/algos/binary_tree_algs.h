#ifndef BINARYTREE_ALGOS_HEADER
#define BINARYTREE_ALGOS_HEADER
#pragma once

#include <stack>
#include <vector>
#include <queue>
#include <algorithm>
#include "tree_node.h"
using namespace std;

/* 只用递归实现的放在了recursion_algo.h */

// #94. inorder traversal
class InorderTraversalSolver {
public:
    vector<int> LaunchSolver(TreeNode *root) {
        vector<int> res;
        In(root, res);
        return res;
    }

private:
    void In(TreeNode *node, vector<int> &res) {
        if (node) {
            In(node->left, res);
            res.push_back(node->val);
            In(node->right, res);
        }
    }
};

// Non recursive inorder traversal
vector<int> InorderStack(TreeNode *root) {
    vector<int> res;
    stack<TreeNode *> s;
    TreeNode *cur = root;
    while (cur || !s.empty()) {
        if (cur) {
            s.push(cur);
            cur = cur->left;
        } else {
            // 这里不好想
            cur = s.top(); // *** 先移动到上一个节点
            s.pop();
            res.push_back(cur->val);
            cur = cur->right; // 后移动到right
        }
    }
    return res;
}

// #144. binary tree preorder traversal
vector<int> PreorderStack(TreeNode *root) {
    vector<int> res;
    stack<TreeNode *> s;
    TreeNode *cur = root;
    while (cur || !s.empty()) {
        if (cur) {
            s.push(cur);
            res.push_back(cur->val);
            cur = cur->left;
        } else {
            cur = s.top(); // 先移动到上个节点
            s.pop();
            cur = cur->right; // 后移动到right
        }
    }
    return res;
}


// #145. Postorder traversal
vector<int> PostOrderStack(TreeNode *root) {
    vector<int> res;
    stack<TreeNode *> s;
    TreeNode *cur = root;
    while (cur || !s.empty()) {
        while (cur) {
            s.push(cur);
            res.push_back(cur->val);
            cur = cur->right;
        }
        cur = s.top();
        s.pop();
        cur = cur->left;
    }
    reverse(res.begin(), res.end());
    return res;
}

// #102. Binary tree level order traversal
// ***Queue 主要处理的问题就是广度优先遍历
class LevelOrderSolver {
public:
    vector<vector<int>> LaunchSolver(TreeNode *root) {
        vector<vector<int>> res;
        if (!root) { return res; }

        queue<pair<TreeNode *, int>> q;
        // 可以同时知道当前节点属于哪一层，方便将节点值添加到结果 res 中的对应层级。 ***
        q.push(make_pair(/*节点=*/root, /*所在层index=*/0)); // 从第0层开始
        while (!q.empty()) {
            // 取队头元素
            TreeNode *cur_node = q.front().first; // 队头
            int level = q.front().second; // 队头
            q.pop();

            // 这行代码非常关键。 它确保了在将节点值添加到 res 之前，res 中已经存在对应的层级。
            // 如果当前层数 level 等于 res 的大小，说明 res 中还没有该层级的向量， ***
            // 需要先创建一个新的向量。
            if (level == res.size()) { res.push_back(vector<int>()); }
            // res 在此构建
            res[level].push_back(cur_node->val);
            if (cur_node->left) {
                q.push(make_pair(cur_node->left, level + 1));
            }
            if (cur_node->right) {
                q.push(make_pair(cur_node->right, level + 1));
            }
        }
        return res;
    }
};

// #958. check completeness of binary tree
// 思路：层序遍历的过程，
class CompleteBinaryTreeSolver {
public:
    bool LaunchSolver(TreeNode *root) {
        if (!root) { return true; }

        // ***定义queue中元素<节点，id> id表示层序遍历的节点id
        queue<pair<TreeNode *, int>> q;
        q.push(make_pair(root, 1));
        int count = 0; // 记录节点个数
        int last_id = 1; //
        // 根据二叉树的性质，
        while (!q.empty()) {
            // ***维护一个还有节点指针的容器，其中的指针包含以该指针为root的子树
            TreeNode *cur_node = q.front().first;
            int id = q.front().second;
            q.pop();

            count++;
            last_id = id;
            if (cur_node->left) { q.push(make_pair(cur_node->left, id * 2)); }
            if (cur_node->right) {
                // 如果测试用例中超出了int的可表示数的范围，就要将int改为double
                q.push(make_pair(cur_node->right, id * 2 + 1));
            }
        }
        return count == last_id;
    }
};

// #101. Symmetric tree
// *** 先返回所有可返回的情况，最后递归； 注意这里的3个if的顺序，很清晰 ***体会体会
// 理解关键：从root开始到子树
class SymmetricBinaryTree {
public:
    bool LaunchSolver(TreeNode *root) { return IsSymmetric(root, root); }

    bool IsSymmetric(TreeNode *root1, TreeNode *root2) {
        // 递归终止，
        if (root1 == nullptr && root2 == nullptr) { return true; }
        // 不对称
        if (root1 == nullptr || root2 == nullptr) { return false; }
        // 不对称,。*** 如果root不同，直接返回；如果root相同，则考察子树
        if (root1->val != root2->val) { return false; }
        // root节点值相同时：
        return IsSymmetric(root1->left, root2->right)
                && IsSymmetric(root1->right, root2->left);
    }
};

// #105. mid. 从前序遍历和中序遍历 构建二叉树（树中没有重复元素）
// *** 根据中序序列找到 前序序列中 左右子树的区间
// 找到结论，根据结论即可写出代码
class ConstructBT {
public:
    TreeNode *LaunchSolver(vector<int> &preorder, vector<int> &inorder) {
        int n = inorder.size();
        int m = preorder.size();
        if (n != m) { throw invalid_argument("Incorrect input"); }
        // 中序遍历的数值和位置
        for (int i = 0; i < n; ++i) {
            posi[inorder[i]] = i;
        }

        // 递归入口是传入整个区间
        return _build(preorder, inorder, 0, n - 1, 0, n - 1);
    }

private:
    // map表示：中序序列中 每个节点，及其位置
    unordered_map<int, int> posi;
    // *** 同一棵树的前序和中序，的起始位置。****所以本质上是找同一棵树的前序和后续的起始位置
    // (preorder, inorder, /*pre start=*/, /*pre end=*/, /*inorder start=*/, /*inorder end=*/)
    TreeNode *_build(vector<int> &preorder, vector<int> &inorder, int pl,
            int pr, int il, int ir) {
        // 终止条件，传入的区间不构成区间
        if (pl > pr || il > ir) { return nullptr; }

        // 新构建的树
        TreeNode *root = new TreeNode(preorder[pl]);

        // 根据当前区间边界，计算前序
        int root_id = posi[preorder[pl]];
        root->left = _build(preorder, inorder, pl + 1, root_id - il + pl, il,
                root_id - 1); // 左子树分别在pre、in中的区间范围
        root->right = _build(preorder, inorder, root_id - il + pl + 1, pr,
                root_id + 1, ir); // 右子树分别在pre、in中的区间范围
        return root;
    }
};

// #98. 判断是否是BST,
// 画出递归树，
// O(n), O(1)
// insight: 中序遍历（左根右）思路跟着递归，跳进跳出
class IsValidBST {
private:
    long long last_val = LLONG_MIN;

public:
    // 逻辑关键：通过【左根右】遍历，过程中更新全局last_val【更新的过程中是单调递增的】***
    // 使得每次遍历到的节点 val 可以与 last_val 比较.
    // 本质上是中序遍历得到遍历结果，如果结果是单调递增的，则返回true。此实现只不过是在遍历的过程中比较的
    bool IsValid(TreeNode *root) {
        if (!root) return true;
        if (!IsValid(root->left)) return false; // 1. left

        if (root->val <= last_val) return false;  // 只有这一句判断是否是BST
        last_val = root->val; // 2. root

        return IsValid(root->right); // 3. right
    }
};

// #114. Flatten a binary tree to Linked list，自底向上，对于每个子树，构建出只有left的链表
// 逻辑：看问题描述，
class Flatten {
public:
    void LaunchSolver(TreeNode *root) {
        if (!root) return;
        LaunchSolver(root->left); // left

        if (root->left) { // root
            //1. 保存左树
            TreeNode *t = root->left; 
            //2. 将t指针执行左树的最右节点
            while (t->right) {
                t = t->right;
            }
            //3. 交换位置
            t->right = root->right;
            root->right = root->left;
            root->left = nullptr;
            // 所以，这一步之前要抱枕root的左子树已经flatten过。
        }
        LaunchSolver(root->right); // 相同的方式处理右子树
    }
};

// #257. easy 二叉树所有路径【返回所有的路径】
// *** 递归执行时，是自下而上的执行，
// 所以实现代码时，要想着，假如下一层已经计算完了，那么当前层的逻辑是啥。
class TreePath {
    // 节点定义：从root到叶子所有的路径。存在一个vector中
    vector<string> FindTreePath(TreeNode *root) {
        vector<string> res; // res 是一条路径
        if (!root) { return res; }
        // 当是叶节点时
        if (root->left == nullptr && root->right == nullptr) {
            res.push_back(to_string(root->val));
            return res;
        }

        if (root->left) {
            vector<string> left_path = FindTreePath(root->left);
            for (int i = 0; i < left_path.size(); ++i) {
                res.push_back(to_string(root->val) + "->" + left_path[i]);
            }
        }
        if (root->right) {
            vector<string> right_path = FindTreePath(root->right);
            for (int i = 0; i < right_path.size(); ++i) {
                res.push_back(to_string(root->val) + "->" + right_path[i]);
            }
        }
        return res;
    }

public:
    vector<string> LaunchSolver(TreeNode *root) { return FindTreePath(root); }
};

// #124. hard. Binary Tree Maximum path  TODO
class BTMpath {
private:
    long long max_sum = LLONG_MIN;

    // 包括root的最大path
    int MaxPathFromRoot(TreeNode *root) {
        if (!root) return 0;
        int left = MaxPathFromRoot(root->left);
        int right = MaxPathFromRoot(root->right);

        long long tmp = max(left, 0) + max(right, 0) + root->val;
        max_sum = max(max_sum, tmp);

        return max(max(left, right), 0) + root->val;
    }

public:
    int LaunchSolver(TreeNode *root) {
        int tmp = MaxPathFromRoot(root);
        return max_sum;
    }
};

// #199. 二叉树的右视图节点
// insight： 使用后续遍历，记录当前层的第一个节点。
class RightViewTree {
private:
    void right_root_left(TreeNode *root, vector<int> &res, int level) {
        if (!root) return;
        if (res.size() < level) { // ** 难点是什么时候将节点的值记录：通过后续遍历，将当前层第一个节点记录即可
            res.push_back(root->val);
        }
        right_root_left(root->right, res, level + 1);
        right_root_left(root->left, res, level + 1);
    }
public:
    vector<int> Solver(TreeNode *root) {
        vector<int> res;
        right_root_left(root, res, 1);
        return res;
    }

public:
    vector<int> SolverByQueue(TreeNode *root) {
        vector<int> res;
        if (!root) return res;
        queue<TreeNode *> q;
        q.push(root);
        while (q.size()) {
            int level_size = q.size(); // 当前层的节点数
            for (int i = 0; i < level_size; ++i) {
                auto node = q.front();
                q.pop();
                // 当这一层i指的是最后一个节点（这一层最右边的节点）时，记录该节点的值，***
                // 因为push时总是先左后右，所以当前层中i==level_size-1 的节点一定是最右节点 ***
                if (i == level_size - 1) {
                    res.push_back(node->val);
                }
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        return res;
    }
};

// #530. 找到 BST 中任意两节点的差的绝对值的最小值
// insight: BST 的中序遍历结果是递增的，记录中序遍历过程中两个节点值之差的最小值
// insight: 首先知道了遍历顺序，然后根据一个最小子树，写出核心逻辑。***
class GetMinDiff{
public:
    int min_diff;
    TreeNode* pre;
    void in_order(TreeNode *node) {
        if (!node) return;
        in_order(node->left);
        // 如果存在前一个节点，更新最小差值
        if (pre) {
            min_diff = min(min_diff, node->val - pre->val);
        }
        pre = node;
        in_order(node->right);
    }

    int Solver(TreeNode* root) {
        min_diff = INT_MAX;
        pre = nullptr;

        in_order(root);
        return min_diff == INT_MAX ? 0 : min_diff;
    }
};

// #637. 二叉树每一层的平均值
// insight: 通过q.size() 记录当前层节点个数
class AverageOfLevels {
	vector<double> averageOfLevels(TreeNode* root){
		vector<double> res;
		if (!root) return res;
		queue<TreeNode*> q;
		q.push(root);

		while(!q.empty()){
            // l 表示当前层的节点数
			int l = q.size();
			double sum = 0;
			for (int i = 0; i < l; i++){
				TreeNode* node = q.front();
				q.pop();
                // 累加当前层的节点值
				sum += node->val;
				if (node->left)
					q.push(node->left);
				if (node->right)
					q.push(node->right);
			}
			res.push_back(sum/l);
		}
		return res;
	}
};

// #103. Binary Tree Zigzag Level Order Traversal
// insight: 1. 使用双端队列, 使得可以从头和尾插入，2. 如何左右翻转
class ZigzagLevelOrderTraversal {
public:
    vector<vector<int>> Solver(TreeNode *root) {
        vector<vector<int>> res;
        if (!root) return res;

        queue<TreeNode *> q;
        q.push(root);
        bool left_to_right = true; // 记录当前层遍历方向

        while (!q.empty()) {
            int level_size = q.size();
            deque<int> curr_level; // 使用双端队列，方便左右翻转

            for (int i = 0; i < level_size; ++i) {
                auto node = q.front(); // 队首元素出队
                q.pop();

                if (left_to_right) {
                    curr_level.push_back(node->val);
                } else {
                    curr_level.push_front(node->val);
                }

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            res.push_back(vector<int>(curr_level.begin(), curr_level.end()));

            left_to_right = !left_to_right; // 改变遍历方向 ***
        }
        return res;
    }
};

// #230. Kth Smallest Element in a BST
// 中序遍历，就该问题讲，下面的方法有冗余
class KthSmallestElemBST {
private:
    vector<int> vec;
    void inOrder(TreeNode* node) {
        if (!node) return;
        inOrder(node->left);
        vec.push_back(node->val);
        inOrder(node->right);
    }
public:
    // 最直观的解法，需要额外空间保存中序遍历额节点值
    int kthSmallest(TreeNode* root, int k) {
		inOrder(root);
		return vec[k-1];
    }
};

// # 230. Kth Smallest Element in a BST
// 更好的解法：中序遍历会按照从小到大的顺序访问 BST 中的所有节点。
// 在遍历过程中，我们可以维护一个计数器来跟踪已经访问的节点数，当计数器达到 K 时，我们就找到了第 K 小的元素。
// 找到第k个就停止计算，更高效.

// 扩展：同样的方法可以用于查找 BST 中最大值和最小值，实际上查找min/max 可以更简单。
class KthSmallestElemBST2 {
public:
    int Solver(TreeNode* root, int k) {
        k_ = k;
        InOrder(root);
        return res_;
    }
private:
    int count = 0;
    int k_;
    int res_ = -1;
    void InOrder(TreeNode* node) {
        if (!node) return;
        InOrder(node->left);
        count++;
        if (count == k_) {
            res_ = node->val;
            return;
        }
        InOrder(node->right);
    }
};

class OutScope{
private:
    int check_min(TreeNode* root) {
        if (!root) {
            cout << "empty tree\n";
            return -1;
        }
        while (root->left) {
            root = root->left;
        }
        return root->val;
    }
private:
    int check_max(TreeNode* root) {
        if (!root) {
            cout << "empty tree\n";
            return -1;
        }
        while (root->right) {
            root = root->right;
        }
        return root->val;
    }
public:
    void get_min_max(TreeNode* root) {
        cout << "min: " << check_min(root) << ", max: " << check_max(root);
    }
};


// #108. Convert Sorted Array to Binary Search Tree，
// 问题中强调 输出应该是 height-balanced bst，所以需要找到中间节点，左右子树分别递归构建！
// insight: 与#148 一样，新分，分分分，后做动作
class ConvertSortedArray2BST{
private:
    TreeNode* build_bst(vector<int>& nums, int start, int end) {
        if (start > end) return nullptr;

        int mid = start + (end - start) / 2; // 左右平衡
        // 如果没有这个 height-balanced bst 的限制，也可以树退化为链表
        // int mid = end; // 只有左子树
        // int mid = start; // 只有右子树
        TreeNode* node = new TreeNode(nums[mid]);
        node->left = build_bst(nums, start, mid - 1);
        node->right = build_bst(nums, mid + 1, end);
        return node;
    }
public:
    TreeNode* Solver(vector<int>& nums) {
        return build_bst(nums, 0, nums.size() - 1);
    }
};

#endif // BINARYTREE_ALGOS_HEADER
