#ifndef BINARYTREE_ALGOS_HEADER
#define BINARYTREE_ALGOS_HEADER
#pragma once

#include <stack>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <functional> // std::function
#include "tree_node.h"
using namespace std;

/* 只用递归实现的放在了recursion_algo.h */

/*
[94 E]. inorder traversal

inorder：做-》中-》右
*/

class InorderTraversalSolver {
private:
    void In(TreeNode *node, vector<int> &res) {
        if (node) {
            In(node->left, res);
            res.push_back(node->val);
            In(node->right, res);
        }
    }
public:
    vector<int> LaunchSolver(TreeNode *root) {
        vector<int> res;
        In(root, res);
        return res;
    }

    /*
    Non recursive inorder traversal。需要一个容器辅助
    */
    vector<int> InorderStack(TreeNode *root) {
        vector<int> res;
        stack<TreeNode *> s;
        TreeNode *cur = root;
        while (cur || !s.empty()) {
            if (cur) {
                s.push(cur);
                cur = cur->left;
            } else {
                // Key: 保证cur 回到上一个根节点
                cur = s.top(); s.pop(); // 回到子树根节点
                res.push_back(cur->val); // 记录根节点
                cur = cur->right;      // 移动到根节点的right
            }
        }
        return res;
    }

};


/*
[144 E]. binary tree preorder traversal
*/
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
            // Key: 保证cur 回到上一个根节点
            cur = s.top(); s.pop(); // 先移动到上个节点
            cur = cur->right;       // 后移动到right
        }
    }
    return res;
}

/*
[145 E]. Postorder traversal

这个实现有问题。。。
*/
vector<int> PostOrderStackII(TreeNode* root) {
    vector<int> res;
    stack<TreeNode*> s;
    TreeNode* cur = root;
    TreeNode* lastVisited = nullptr;  // 记录上次访问过的节点

    while (cur || !s.empty()) {
        while (cur) {
            s.push(cur);
            cur = cur->left;
        }
        cur = s.top();                // 看一眼栈顶
        if (cur->right == nullptr || cur->right == lastVisited) {
            res.push_back(cur->val);  // 右子树已访问完，才访问根
            s.pop();
            lastVisited = cur;
            cur = nullptr;            // 重要：不继续往左走
        } else {
            cur = cur->right;         // 右子树还没访问，先去右边
        }
    }
    return res;
}

/*
[102 M]. Binary tree level order traversal
Key: Queue 主要处理的问题就是广度优先遍历
*/
class LevelOrderSolver {
public:
    vector<vector<int>> LaunchSolver(TreeNode *root) {
        vector<vector<int>> res;
        if (!root) { return res; }

        queue<pair<TreeNode *, int>> q;
        // 可以同时知道当前节点属于哪一层，方便将节点值添加到结果 res 中的对应层级。 ***
        q.push(make_pair(/*节点=*/root, /*所在层index=*/0)); // 从第0层开始
        while (!q.empty()) {
            // 首先取队头元素
            TreeNode *cur_node = q.front().first; // 队头
            int level = q.front().second;         // 队头
            q.pop();

            // Key: 它确保了在将节点值添加到 res 之前，res 中已经存在对应的层级。
            // 如果当前层数 level 等于 res 的大小，说明 res 中还没有该层级的向量， ***
            // 需要先创建一个新的向量。
            if (level == res.size()) { res.push_back(vector<int>()); }
            // res 在此构建
            res[level].push_back(cur_node->val);
            if (cur_node->left) { q.push(make_pair(cur_node->left, level + 1)); }
            if (cur_node->right) { q.push(make_pair(cur_node->right, level + 1)); }
        }
        return res;
    }
};

/*
[958 M]. check completeness of binary tree

完全二叉树（Complete Binary Tree）：
条件1. 除最后一层外，其余层全满
条件2. 最后一层节点靠左连续排列

思路：层序遍历的过程，
*/

class CompleteBinaryTreeSolver {
public:
    bool LaunchSolver(TreeNode *root) {
        if (!root) { return true; }

        // *** 定义queue中元素<节点，idx> id表示层序遍历的节点idx
        queue<pair<TreeNode *, unsigned int>> q;
        q.push(make_pair(root, 0));
        unsigned int count = 0;  // 记录节点个数,个数不是负数
        unsigned int last_id = 0; // 层序便利时，在数组中的index
        // 根据二叉树的性质，
        while (!q.empty()) {
            // ***维护一个还有节点指针的容器，其中的指针包含以该指针为root的子树
            TreeNode *cur_node = q.front().first;
            unsigned int id = q.front().second;
            q.pop();

            count++;
            last_id = id;
            if (cur_node->left) { q.push(make_pair(cur_node->left, id * 2 + 1)); }
            if (cur_node->right) { q.push(make_pair(cur_node->right, id * 2 + 2)); }
        }
        return count == last_id + 1;
    }
};

/*
[101 E]. Symmetric tree
*** 先返回所有可返回的情况，最后递归； 注意这里的3个if的顺序，很清晰 ***体会体会
Key：从root开始到子树
*/

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


/*
[105 M]. 从前序遍历和中序遍历 构建二叉树（树中没有重复元素）

Key:
前序遍历：[根][左子树][右子树] 前序提供根节点
中序遍历：[左子树][根][右子树] 中序划分左右子树
Key: 关键是计算左右子树在两种便利时的 起始位置

Key：找到结论，根据结论即可写出代码

    3
   / \
  9  20
     / \
    15  7
Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]

*/
class ConstructBT {
public:
    TreeNode *LaunchSolver(vector<int> &preorder, vector<int> &inorder) {
        int n = inorder.size();
        int m = preorder.size();
        if (n != m) { throw invalid_argument("Incorrect input"); }
        // 中序遍历的值和index
        for (int i = 0; i < n; ++i) {
            inorder_map[inorder[i]] = i;
        }

        // 递归入口是传入整个区间
        return _build(preorder, inorder, 0, n - 1, 0, n - 1);
    }

private:
    // 中序序列中 {节点值, idx}
    unordered_map<int, int> inorder_map;
    // *** 同一棵树的前序和中序，的起始位置。****所以本质上是找同一棵树的前序和后续的起始位置
    TreeNode *_build(vector<int> &preorder, vector<int> &inorder, 
                    /*pre start=*/int preStart,
                    /*pre end=*/int preEnd, 
                    /*inorder start=*/int inStart, 
                    /*inorder end=*/int inEnd) {

        if (preStart > preEnd || inStart > inEnd) { return nullptr; }

        // 新构建的树
        TreeNode *root = new TreeNode(preorder[preStart]);

        // 根据当前区间边界，计算前序
        int root_id = inorder_map[preorder[preStart]];
        int left_size = root_id - inStart;

        // 左子树分别在pre、in中的区间范围
        root->left = _build(preorder, inorder, 
                            preStart + 1, 
                            left_size + preStart, 
                            inStart, 
                            root_id - 1); 
        // 右子树分别在pre、in中的区间范围
        root->right = _build(preorder, inorder,
                             left_size + preStart + 1, 
                             preEnd, 
                             root_id + 1, 
                             inEnd);
        return root;
    }
};

/*
[todo][106 M] build tree from 后序 + 中序

Key:
后序遍历：[左子树][右子树][根] 后序提供根节点
中序遍历：[左子树][根][右子树] 中序划分左右子树
Key: 关键是计算左右子树在两种便利时的 起始位置
*/
class ConstructBTfromPI {
public:
    TreeNode *LaunchSolver(vector<int> &postorder, vector<int> &inorder) {
        int n = inorder.size();
        int m = postorder.size();
        if (n != m) { throw invalid_argument("Incorrect input"); }
        // 中序遍历的值和index
        for (int i = 0; i < n; ++i) {
            inorder_map[inorder[i]] = i;
        }

        // 递归入口是传入整个区间
        return _build(postorder, inorder, 0, n - 1, 0, n - 1);
    }
private:
    // 中序序列中 {节点值, idx}
    unordered_map<int, int> inorder_map;
    TreeNode* _build(vector<int> &postorder, vector<int> &inorder, 
                    /*pre start=*/int postStart,
                    /*pre end=*/int postEnd, 
                    /*inorder start=*/int inStart, 
                    /*inorder end=*/int inEnd) {
        TreeNode* res = new TreeNode(0);
        return res;
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

/*
[124 H]. Binary Tree Maximum path ， 二叉树中最大路径和

    1
   / \
  2   3

→ 可能路径：[1], [2], [3], [1,2], [1,3], [2,1,3]
→ 最大路径和：2+1+3 = 6

   -10
   / \
  9  20
    /  \
   15   7

→ 最大路径和：15+20+7 = 42（路径：15→20→7）

Key: 后序遍历
Insight: dfs 函数执行过程中记录最终结果，这与 dfs 函数返回值是两回事。函数返回值是保证dfs的定义。过程中记录最终结果是我的最终目的
*/
class BTMpath {
public:
    int LaunchSolver(TreeNode *root) {
        long long max_sum = LLONG_MIN;

        // 函数定义：node为根的树，左或右 路径的最大长度
        function<int(TreeNode*)> dfs = [&](TreeNode* node) {
            if (!node) return 0;

            int left_path = dfs(node->left);  // dfs函数定义不变
            int right_path = dfs(node->right);

            // left_root_right 用于记录可能的最大值
            long long left_root_right = max(left_path, 0) + max(right_path, 0) + node->val;
            max_sum = max(max_sum, left_root_right);
            // return 与 left_root_right 无关
            return max(max(left_path, right_path), 0) + node->val;
        };

        dfs(root);
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

/*
[236 M]
给定一个二叉树和两个节点 p 和 q，找到它们的最近公共祖先（LCA）

公共祖先：同时是 p 和 q 的祖先节点（一个节点也可以是自己的祖先）
最近：在所有公共祖先中，距离 p 和 q 最近的那个

例：
        3
       / \
      5   1
     / \ / \
    6  2 0  8
      / \
     7   4

p = 5, q = 1 → LCA = 3（根节点）
p = 5, q = 4 → LCA = 5（p 本身是 q 的祖先）
p = 6, q = 2 → LCA = 5

Key: 绘出处递归树：自顶向下递归，后自底向上返回：

                        [3]. LCA(3,6,2) 返回5
                         /          \
                        /            \
            [5]. LCA(5,6,2) 返回5       [1]. LCA(1,6,2) 返回nullptr
             /         \
            /           \
[6]. LCA(6,6,2) 返回6    [2]. LCA(2,6,2) 返回2

*/
class  LowestCommonAncestorofaBinaryTree {
public:
    TreeNode* Sovler(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 定义：以 node 为根的子树中，返回 节点 p 和 q 的最近公共祖先
        function<TreeNode*(TreeNode*)> dfs = [&](TreeNode* node){
            if(!node || node == p || node == q) return node;
            TreeNode* left  = dfs(node->left);
            TreeNode* right = dfs(node->right);

            if (!left) return right;  // p,q 都在right 子树
            if (!right) return left;  // p,q 都在left 子树
            // 若 left right 都不是空，当前节点是 LCA
            return node;
        };

        return dfs(root);
    }
};


/*
[314 M]. verticalOrder 
一个二叉树，按垂直列从上到下、从左到右遍历
根节点坐标为 (0, 0)
左子节点：(row+1, col-1)
右子节点：(row+1, col+1)

    3
   / \
  9  20
    /  \
   15   7

输出：[[9], [3,15], [20], [7]]
col -1: [9], col 0: [3,15], col 1: [20], col 2: [7]
*/
class VerticalOrder {
public:
    // BFS, 行自然有序。map本身按key 有序
    vector<vector<int>> SolverBFS(TreeNode* root) {
        vector<vector<int>> res;
        if (!root) return res;
        
        // map<column, list of values in top-to-bottom order>
        map<int, vector<int>> col_map;
        
        // queue: {node, column}
        queue<pair<TreeNode*, int>> q;
        q.push({root, 0});
        
        while (!q.empty()) {
            auto [node, col] = q.front();
            q.pop();
            
            col_map[col].push_back(node->val); // BFS 保证上层优先访问
            
            if (node->left) q.push({node->left, col - 1});
            if (node->right) q.push({node->right, col + 1});
        }

        // map 已按 column 从小到大排序，直接取出
        for (auto& p : col_map) {
            res.push_back(move(p.second));
        }
        
        return res;
    }

    // map 天然按key 有序, 但是col 需要排序
    vector<vector<int>> SolverDFS(TreeNode* root) {
        if (!root) return {};
        
        map<int, vector<pair<int, int>>> col_map;  // col -> [(row, val)]
        function<void(TreeNode*, int, int)> dfs = [&](TreeNode* node, int row, int col) {
            if (!node) return;
            
            col_map[col].push_back({row, node->val});
            dfs(node->left, row + 1, col - 1);
            dfs(node->right, row + 1, col + 1);
        };
        
        dfs(root, 0, 0);
        
        vector<vector<int>> result;
        for (auto& [col, nodes] : col_map) {
            sort(nodes.begin(), nodes.end());  // 按行排序
            vector<int> colVals;
            for (auto& [row, val] : nodes) {
                colVals.push_back(val);
            }
            result.push_back(colVals);
        }
        return result;
    }
};


/*
[572 E]. Subtree of Another Tree
二叉树 s 和 t，检查树 t 是否与树 s 的某个子树具有相同的结构和节点值。

Key: 先序遍历。两个递归函数交叉调用
*/
class SubtreeofAnotherTree {
public:
    bool IsSubTree(TreeNode* root, TreeNode* subRoot){
        if (!root) return false;
        // 如果两个树本身相同
        if (IsSame(root, subRoot)) return true;
        return IsSubTree(root->left, subRoot) || IsSubTree(root->right, subRoot);
    }

private:
    /*
    判断以t1 和 t2 为root的两个树，是否完全相同。先序遍历
    */
    bool IsSame(TreeNode* t1, TreeNode* t2) {
        // 递归底部边界，如果节点都是空，则same，如果都不是空但是 val不同，则not same, 如果一个空一个不空，则not same
        if (!t1 && !t2) return true;
        if ((!t1 && t2) || (t1 && !t2) || (t1 && t2 && t1->val != t2->val)) {
            return false;
        }
        // 两节点不空且val同，则分别考察左右子树
        if (t1 && t2 && t1->val == t2->val) {
            return IsSame(t1->left, t2->left) && IsSame(t1->right, t2->right);
        } else {
            return false; // 其他可能的情况
        }
    }
};

/*
[508 M] Most Frequent Subtree Sum
一个二叉树的根节点 root，返回出现次数最多的子树元素和（如果有多个，返回所有）

    5
   / \
  2  -3

子树和：
- 节点2：2
- 节点-3：-3  
- 节点5：5+2+(-3)=4

频数都是1，返回 [2-3,4]

    5
   / \
  2  -5

子树和：
- 节点2：2
- 节点-5：-5
- 节点5：5+2+(-5)=2
节点和为2 的频数最高， 返回[2]

Key: 后序遍历，马上给出后序遍历部分code
Key: 需要一个 hash 表，记录 {子树和：出现次数}

Insight: 递归函数中一定会call自己，在理解时，把call自己的部分作为已知。思维不要递归进入。
Insight: dfs的返回值和中途维护的值，是两回事。
*/
class MostFrequentSubtreeSum {
public:
    vector<int> Solver(TreeNode* root) {
        unordered_map</*子树和=*/int, /*出现次数=*/int> sum_freq;
        int max_freq = 0;
        // 函数定义：以node为根的树，左+根+右 的sum
        function<int(TreeNode*)> dfs = [&](TreeNode* node){
            if (!node) return 0;

            // 按照题意，算子树节点sum要从叶节点开始，故后续遍历
            int left_sum = dfs(node->left);
            int right_sum = dfs(node->right);
            int curr_sum = node->val + left_sum + right_sum;

            sum_freq[curr_sum]++;
            // dfs 中途记录我的目标
            max_freq = max(max_freq, sum_freq[curr_sum]);
            return curr_sum;
        };

        dfs(root);

        vector<int> res;
        for (auto& [sum, freq] : sum_freq) {
            if (freq == max_freq) {
                res.push_back(sum);
            }
        }
        return res;
    }
};

/*
[1973 M] Count Nodes Equal to Sum of Descendants
一个二叉树的根节点 root，统计有多少个节点的值等于其所有后代节点的值之和

后代节点：节点的所有子树中的节点（不仅是直接子节点）

    10
   /  \
  3   -4
 / \
2   1

分析：
- 节点2：后代和=0，值=2 ≠ 0 → 不满足
- 节点1：后代和=0，值=1 ≠ 0 → 不满足
- 节点-4：后代和=0，值=-4 ≠ 0 → 不满足  
- 节点3：后代和=2+1=3，值=3 = 3 → 满足 ✓
- 节点10：后代和=3+(-4)=−1，值=10 ≠ -1 → 不满足
结果：1个节点满足条件

Key: 从子树开始，故后序遍历,马上给出后序遍历部分code，并明确并维持 dfs 定义
Note：long long 防止整数溢出

Insight: 递归函数中一定会call自己，在理解时，把call自己的部分作为已知。思维不要递归进入。
insight: 递归中一定会体现 遍历顺序  
*/
class SumofDescendants {
public:
    int Solver (TreeNode* root) {
        int count = 0;

        // 函数定义：返回整个子树的节点sum
        function<long long(TreeNode*)> dfs = [&](TreeNode* node){
            if (!node ) return 0;

            int left_sum = dfs(node->left); // 返回整个子树的节点sum
            int right_sum = dfs(node->right); // 返回整个子树的节点sum
            int d_sum = left_sum + right_sum; // 注意这里不包括当前阶段的值

            if (node->val == d_sum){
                count++;
            }
            // 返回当前子树总和给其 caller，对于caller而言，我要子树所有节点和
            return node->val + d_sum;  
        };

        dfs(root);
        return count;
    }
};

/*
[110 E]. Balanced Binary Tree
树的所有左右子树左右深度差不超过1

输入：[3,9,20,null,null,15,7]
    3
   / \
  9  20
    /  \
   15   7
→ 每个节点左右子树高度差 ≤ 1 → true

输入：[1,2,2,3,3,null,null,4,4]
       1
      / \
     2   2
    / \
   3   3
  / \
 4   4
→ 节点2的左右子树高度差为2 → false

Key: 后续遍历
*/
class BalancedBinaryTree {
public:
    bool Solver(TreeNode* root) {
        if (!root) return -1;  // 空不是tree

        // 定义：以node为根的树，平衡返回树的高度，不平衡返回-1
        function<int(TreeNode*)> dfs = [&](TreeNode* node) {
            if(!node) return 0;
            int left_depth = dfs(node->left);
            int right_depth = dfs(node->right);

            if (abs(left_depth - right_depth)>1) return -1;
            if (left_depth == -1 || right_depth == -1) return -1;
            return max(left_depth, right_depth) + 1; 
        };

        return dfs(root) != -1;
    }
};


/*
[563 E] Binary Tree Tilt 二叉树的坡度
节点的坡度 = 该节点左子树节点之和 与 右子树节点之和 的绝对值差
整棵树的坡度 = 所有节点的坡度之和

    1
   / \
  2   3
 / \
4   5

计算过程：
- 节点4：左子树和=0，右子树和=0 → 坡度=|0-0|=0
- 节点5：左子树和=0，右子树和=0 → 坡度=|0-0|=0  
- 节点2：左子树和=4，右子树和=5 → 坡度=|4-5|=1
- 节点3：左子树和=0，右子树和=0 → 坡度=|0-0|=0
- 节点1：左子树和=2+4+5=11，右子树和=3 → 坡度=|11-3|=8
总坡度：0+0+1+0+8 = 9

Key: 后序遍历; 明确的贵函数定义
*/
class BinaryTreeTilt{
public:
    int Solver(TreeNode* root){
        int tilts = 0;
        // 以node为根树的节点之和
        function<int(TreeNode*)> dfs = [&](TreeNode* node) {
            if (!node) return 0;
            int left_sum = dfs(node->left);  // 左子树的节点之和
            int right_sum = dfs(node->right);
            // 中途计算坡度，并记录坡度
            int curr_tilt = abs(left_sum - right_sum);
            tilts += curr_tilt;
            return node->val + left_sum + right_sum;
        };
        dfs(root);
        return tilts;
    }
};


/*
[687 M]. Longest Univalue Path
返回树中最长路径的长度，该路径上所有节点具有相同的值

    5
   / \
  4   5
 / \   \
1   1   5
→ 最长同值路径：右子树的 5-5 → 长度 1
→ 或者左子树的 4-1 或 4-1 → 长度 1
→ 但右子树 5-5-5 → 长度 2 ✅

    1
   / \
  4   5
 / \   \
4   4   5
→ 最长同值路径：左子树的 4-4-4 → 长度 2

Key: 后序遍历；
*/
class LongestUnivaluePath{
public:
    int Solver(TreeNode* root){
        int max_path = 0;

        // 定义：以node为根树的单值最长路径长度
        function<int(TreeNode*)> dfs = [&](TreeNode* node) {
            if (!node) return 0;
            int left_maxpath = dfs(node->left);
            int right_maxpath = dfs(node->right);

            // Key: node->val 一定要参与两边的比较
            int left_plus = (node->left && node->left->val == node->val ) ? left_maxpath + 1 : 0;
            int right_plus = (node->right && node->right->val == node->val ) ? right_maxpath + 1 : 0;

            max_path = max(max_path, left_plus + right_plus);
            return max(left_plus, right_plus); // 左右都已经包含根了
        };

        dfs(root);
        return max_path;
    }
};

/*
[965 E]. Univalued Binary Tree
判断树中的节点是否是单一的值

Key：✅先序：父节点值直接用于验证子节点,并且可以提前终止。以根为准，检查子树
      x 后序：需要子树返回信息再做判断。需要额外补充状态传递
Key: 左右子节点要与根节点作比较
*/
class UnivaluedBinaryTree{
public:
    bool Solver(TreeNode* root) {
        function<bool(TreeNode*)> dfs = [&](TreeNode* node) {
            if (!node) return true;

            if (node->left && node->left->val != node->val) return false;
            if (node->right && node->right->val != node->val) return false;

            // left 或 right 的val == node->val 才会进入递归：
            return dfs(node->left) && dfs(node->right);
        };

        return dfs(root);
    }

    // 稍微更好理解，记录root 的val
    bool Solverii(TreeNode* root) {
        if (!root) return true;
        int root_val = root->val;

        function<bool(TreeNode*)> dfs = [&](TreeNode* node) {
            if (!node) return true;
            if (node->left && node->left->val != root_val) return false;
            if (node->right && node->right->val != root_val) return false;

            // left 或 right 的val == root_val 才会进入递归：
            return dfs(node->left) && dfs(node->right);
        };

        return dfs(root);
    }
};

#endif // BINARYTREE_ALGOS_HEADER
