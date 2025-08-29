#ifndef TOP_150_HEADER
#define TOP_150_HEADER
#pragma once

#include <iostream>
#include <cmath>
#include <bitset>
#include <memory>  // make_unique, unique_ptr

#include "array_algs.h"
#include "binary_tree_algs.h"
#include "bit_algs.h"
#include "dfs_algos.h"
#include "dp_algos.h"
#include "linked_list_algs.h"
#include "matrix_algs.h"
#include "priority_queue_algos.h"
#include "tree_recursive_algs.h"
#include "search_algs.h"
#include "stack_algs.h"
#include "string_algos.h"
#include "math_algos.h"
#include "hash_algs.h"
#include "trie_algos.h"
#include "helper.h" // CheckValue PrintVector PrintMap

namespace top_150 {
int count = 0;
bool final_res = 0;
void Launcher(){
    std::cout << "================ top 150 ================\n";
    // # ----------------------------------------------------- array
    // #88
    MergeSortedArray msa;
    vector<int> num_88_1 = {2,5,6,0,0,0};
    vector<int> num_88_2 = {1,2,3};
    msa.LaunchSolver(num_88_1, 3, num_88_2, 3);
    PrintVector(num_88_1); // # 编译器可以自动推断类型，不需要<int>
    count++;

    // #27
    vector<int> nums_27 = {2,1,2,2,3,2,4,2};
    RemoveElement re;
    std::cout << re.LaunchSolver(nums_27, 2) << "\n";
    PrintVector(nums_27);
    count++;

    // #26
    vector<int> nums_26 = {0,0,1,1,1,2,2,3,3,4};
    RemoveDuplicates rd;
    cout << rd.LaunchSolver(nums_26) << "\n";
    PrintVector(nums_26);
    count++;

    // #80
    vector<int> nums_80 = {0,0,1,1,1,2,2,2,3,3,4};
    RemoveDuplicatesII rdii;
    cout << rdii.LaunchSolver(nums_80) << "\n";
    PrintVector(nums_80);
    count++;

    // #169
    vector<int> nums_169 = {55,0,55,55,55,2,2,55,2,3,3,55,55};
    MajorityElements me;
    cout << me.LaunchSolver(nums_169) << "\n";
    cout << me.LaunchSolverII(nums_169) << "\n";
    count++;

    // #189
    vector<int> num_189 = {1,2,3,4,5,6,7};
    RotateArray ra;
    ra.LaunchSolver(num_189, 3);
    PrintVector(num_189);
    count++;

    // #121 见 HUAWEI
    // #122 见 HUAWEI

    // #55
    JumpGame jg;
    final_res |= CheckValue(jg.LaunchSolver({2, 3, 1, 1, 4}), true);
    final_res |= CheckValue(jg.LaunchSolver({3, 2, 1, 0, 4}), false);
    final_res |= CheckValue(jg.LaunchSolver({0}), true);
    final_res |= CheckValue(jg.LaunchSolver({2, 5, 0, 0}), true);
    count++;

    // #45 x 不会，没理解
    // #274
    HIndex hi;  // # 记住这个算法，没意思，你知道这个算法就会了
    vector<int> num_274 = {3,0,6,1,5};
    final_res |= CheckValue<int>(hi.Launch(num_274), 3);
    count++;

    // #380 没看
    // #238
    Product p;  // # 不需要额外空间，简单的计算，需要理解理解
    vector<int> num_238 = {1,2,3,4};
    final_res |= CheckValue<vector<int>>(p.LaunchII(num_238), {24, 12, 8, 6});
    final_res |= CheckValue(p.LaunchIII(num_238),{24, 12, 8, 6});
    count++;

    // #134
    // #135
    // #42
    // #13
    RomanToInt rti;
    final_res |= CheckValue<int>(rti.Launch("MCMXCIV"), 1994);  // # key: 记住这个算法，你知道这个算法就会了
    count++;

    // #12
    IntToRoman itr;
    final_res |= CheckValue<string>(itr.Launch(3749), "MMMDCCXLIX"); // # key: 记住这个算法，你知道这个算法就会了
    count++;
    // #58
    // #14
    // #151
    // #6
    // #28
    // #68

    // # ----------------------------------------------------- two pointers
    // #125
    ValidPalindrome vp;
    string s_125 = "A man, a plan, a canal: Panama";
    final_res |= CheckValue(vp.Launch(s_125), true);
    count++;
    // #392
    // #167
    // #11
    MaxWater mw;
    vector<int> nums_11 = {1,8,6,2,5,4,8,3,7};
    final_res |= CheckValue<int>(mw.LaunchSolver(nums_11), 49);
    count++;

    // #15

    // # ----------------------------------------------------- sliding window
    // #209  
    vector<int> nums_209 = {2,3,1,2,4,3};
    MinSubArrayLenSolver msals;
    final_res |= CheckValue(msals.LaunchSolver(7, nums_209), 2); // # key: 理解这个窗口是如何滑动的
    count++;

    // #3
    LongestSubstringWithoutRepeatingCharacters lrc;
    string s_3 = "abcbcabb";
    string s_3_1 = "pwwkew";
    final_res |= CheckValue(lrc.Launch(s_3), 3);
    final_res |= CheckValue(lrc.Launch(s_3_1), 3);
    count++;
    // #30
    // #76
    // # ----------------------------------------------------- matrix
    // #36
    // #54
    SpiralMatrix sm;
    vector<vector<int>> matrix =  {{1,2,3},{4,5,6},{7,8,9}};
    final_res |= CheckValue(sm.Launch(matrix), {1,2,3,6,9,8,7,4,5});
    count++;

    // #48
    // #73
    // #289
    
    // # ----------------------------------------------------- hashmap
    // #383
    RandomNote rn;
    final_res |= CheckValue(rn.Solver("aa", "aba"), true);
    final_res |= CheckValue(rn.Solver("aab", "aba"), true);
    final_res |= CheckValue(rn.Solver("aab", "aba"), true);
    count++;


    // #205
    // #290
    // #242
    // #49
    // #1 有
    vector<int> nums_1 = {15,2,11,7};
    TwoSum ts;
    final_res |= (CheckValue(ts.LaunchSolver(nums_1, 9), vector<int> {3,1}) & CheckValue(ts.LaunchSolver(nums_1, 9), vector<int> {1,3}));
    count++;

    // #202
    // #219

    // #128
    LogestConsecutiveSequence lcs;
    vector<int> lcs_vec = {100,4,200,1,3,2};
    final_res |= CheckValue(lcs.LaunchSolver(lcs_vec), 4);
    count++;

    // # ----------------------------------------------------- intervals
    // #228
    SummaryRanges sr;
    vector<int> nums_229 = {0,1,2,4,5,7};
    final_res |= CheckValue(sr.Launch(nums_229), vector<string> {"0->2","4->5","7"});
    count++;

    // #56 见 HUAWEI


    // #57
    // #452
    ///////////////////////////////////////
    // # ----------------------------------------------------- stack
    // #20
    ValidParetheses vpa;
    final_res |= CheckValue(vpa.Solver("()"), true);
    final_res |= CheckValue(vpa.Solver(")[]{}"), false);
    final_res |= CheckValue(vpa.Solver("(){[]}"), true);
    final_res |= CheckValue(vpa.Solver("(){[}"), false);
    count++;

    // #71
    SimplifyPath sp;
    final_res |= CheckValue<string>(sp.Solver("/.../a/../b/c/../d/./"), "/.../b/d");
    final_res |= CheckValue<string>(sp.Solver("/../"), "/");
    final_res |= CheckValue<string>(sp.Solver("/home//foo/"), "/home/foo");
    count++;

    // #155
    MinStack ms; (void)ms;
    count++;
 
    // #150
    // #224
    // # no top150
    Infix2Postfix i2p;
    final_res |= CheckValue<string>(i2p.Solver("A*B+C"), "AB*C+");
    final_res |= CheckValue<string>(i2p.Solver("A*(B+C)"), "ABC+*");
    count++;

    // infix prefix postfix 相关
    Calculatefix cpf;
    final_res |= CheckValue<int>(cpf.SolverPostfix("2 3 + 4 *"), 20);
    final_res |= CheckValue<int>(cpf.SolverPrefix("+ 2 * 3 4"), 14);
    count++;
    ///////////////////////////////////
    // # ----------------------------------------------------- linked list
    // #141
    ListNode* n1_141 = new ListNode(3);ListNode* n2_141 = new ListNode(2);
    ListNode* n3_141 = new ListNode(0);ListNode* n4_141 = new ListNode(-4);
    n1_141->next = n2_141;n2_141->next = n3_141;n3_141->next = n4_141;n4_141->next = n2_141;
    DetectCycle dc;
    PrintLinkedList(n1_141);
    final_res |= CheckValue(dc.LaunchSolver(n1_141), true);
    delete n1_141;delete n2_141; delete n3_141; delete n4_141;  // # 释放变量所指向的内存
    count++;

    // #2 有
    // #21
    // #138
    // #92 有
    // #25
    // #19
    vector<int> nodes_19 = {1,2,3,4,5,6};
    ListNode* l_19 = CreateList(nodes_19);
    PrintLinkedList(l_19);
    RemoveNthNodeFromEndofList rnnel;
    PrintLinkedList(rnnel.LaunchSolver(l_19, 3));
    count++;

    // #82
    // #61
    // #86
    // #146
    
    // #206 (outside 150)
    vector<int> nodes_206 = {1,2};
    ListNode* l_206 = CreateList(nodes_206);
    PrintLinkedList(l_206);
    ReverseSolver rs;
    PrintLinkedList(rs.LaunchSolver(l_206));
    count++;

    // # ----------------------------------------------------- binary tree
    // #104 有
    MaxDepth md; (void)md;
    count++;

    // #100 有
    IsSameTree ist; (void)ist;
    count++;

    // #226 有
    InvertBT ibt; (void)ibt;
    count++;

    // #101  有
    SymmetricBinaryTree sbs; (void)sbs;
    count++;

    // #105  有
    // #106 
    // #117 
    // #114  记住这个逻辑：1 保存左子树，2 找到左子树最优节点t，3 交换位置，形成链表。 
    Flatten fl; (void)fl; count++;

    // #112  有
    PathHasSum phs; (void)phs;
    count++;

    // #129
    SumRoot2LeafNumbers sr2ln; (void)sr2ln; count++;

    // #124  有
    // #173 
    // #222 
    // #236

    // # ----------------------------------------------------- binary tree BFS
    // #199
    RightViewTree right_view_tree; (void)right_view_tree;
    count++;

    // #637
    AverageOfLevels aol; (void)aol; count++;
    // #102
    LevelOrderSolver los;
    count++;

    // #103
    ZigzagLevelOrderTraversal zlot; (void)zlot; count++;
    // # ----------------------------------------------------- Binary Search Tree
    // #530 
    GetMinDiff get_min_diff;
    count++;

    // #230 
    KthSmallestElemBST ksebst; (void)ksebst;
    KthSmallestElemBST2 ksebst2; (void)ksebst2; count++;
    // #98
    IsValidBST ivbst;
    count++;
    
    // # ----------------------------------------------------- Graph 
    // #200
    NumIsLands ni;
    vector<vector<char>> num_200 = {{'1','1','0','0','0'},
                                    {'1','1','0','0','0'},
                                    {'0','0','1','0','0'},
                                    {'0','0','0','1','1'} };

    final_res |= CheckValue(ni.LaunchSolver(num_200), 3);
    count++;

    // #130
    // #133 
    // #399 
    // #207 
    // #210

    // # ----------------------------------------------------- graph BFS
    // #909 
    // #433
    // #127

    // # ----------------------------------------------------- Trie
    // #208 

    // #211
    // #212

    // # ----------------------------------------------------- backtracing
    // #17 
    LetterCombinations lc;
    final_res |= CheckValue<vector<string>>(lc.LaunchSolver("23"), vector<string> {"ad","ae","af","bd","be","bf","cd","ce","cf"});
    count++;

    // #77  有
    Combination com;
    final_res |= CheckValue(com.LaunchSolver(3, 2), vector<vector<int>> {{1,2},{1,3},{2,3}});
    count++;

    // #46  有 找到combination
    Permutation perm;
    vector<int> vec_46 = {1,2,3};
    vector<vector<int>> res_46 = perm.Perm(vec_46);
    PrintVector(res_46);
    count++;
    // #39 
    // #52 
    // #22  有
    // #79
    WordSearch ws;
    vector<vector<char>> board = {{'A','B','C','E'}, {'S','F','C','S'}, {'A','D','E','E'}};
    std::string word = "ABCCED";
    final_res |= CheckValue<bool>(ws.LaunchSolver(board, word), true);
    count++;

    // # ----------------------------------------------------- divide & conquer
    // #108 
    ConvertSortedArray2BST csa2bst;
    std::vector<int> nums_108 = {-10,-3,0,5,9};
    TreeNode* root_108 = csa2bst.Solver(nums_108);
    count++;
    // #148 
    SortList slist; (void)slist; count++;
    // #427 
    // #23

    // # ----------------------------------------------------- Kadane's Algorithm
    // #53 Kadane's Algorithm 记住这个算法
    MaxSubArray ma;
    final_res |= CheckValue(ma.Solver({-2,1,-3,4,-1,2,1,-5,4}), 6);
    final_res |= CheckValue(ma.Solver({0}), 0);
    final_res |= CheckValue(ma.Solver({5,4,-1,7,8}), 23);
    count++;

    // #918

    // # ----------------------------------------------------- Binary Search
    // #35
    SearchInsert si;
    vector<int> nums_35 = {1,3,6,8,9};
    final_res |= CheckValue<int>(si.LaunchSolver(nums_35, 7), 3);
    final_res |= CheckValue<int>(si.LaunchSolver(nums_35, 6), 2);
    final_res |= CheckValue<int>(si.LaunchSolver(nums_35, 5), 2);
    count++;

    // #74
    SearchMatrix2 s2dm;
    vector<vector<int>> mat_74 = {{1,3,5}, {9,10,11}};
    vector<vector<int>> mat_74_2 = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
    final_res |= CheckValue<bool>(s2dm.LaunchSolver(mat_74, 1), true);
    final_res |= CheckValue<bool>(s2dm.LaunchSolver(mat_74, 8), false);
    final_res |= CheckValue<bool>(s2dm.LaunchSolver(mat_74_2, 3), true);
    final_res |= CheckValue<bool>(s2dm.LaunchSolver(mat_74_2, 60), true);
    count++;

    // #162 
    FindPeak find_peak;
    vector<int> nums_162 = {1,2,1,3,5,6,4};
    final_res |= CheckValue<int>(find_peak.Solver(nums_162), 5);
    count++;

    // #33
    FindTargetInRotate ftir;
    vector<int> nums_33 = {6,8,9,10,11,14,2,4,5};
    final_res |= CheckValue<int>(ftir.LaunchII(nums_33, 12), -1);
    final_res |= CheckValue<int>(ftir.LaunchII(nums_33, 2), 6);
    count++;

    // #34
    SearchRange search_range;
    vector<int> num_34 = {5,7,7,8,8,10};
    final_res |= CheckValue<vector<int>>(search_range.Solver(num_34, 8), vector<int>{3,4});
    count++;

    // #153
    FindMinInRotate find_min_in_roteate;
    vector<int> nums_153 = {4,5,6,7,1,2};
    final_res |= CheckValue<int>(find_min_in_roteate.LaunchSolver(nums_153), 1);
    count++;

    // #4

    // # ----------------------------------------------------- heap
    // Heap Sort, 优先队列
    // #215
    KthLargest kl;
    vector<int> nums_215 = {3,2,3,1,2,4,5,5,6};
    final_res |= CheckValue<int>(kl.Solver(nums_215, 4), 4);
    count++;

    // #502 
    // #373 
    // #295
    
    // # ----------------------------------------------------- bit
    // insight 是，bit相关操作是不符合人脑直觉，所以要记住一些关于bit的基本操作，作为尝试
    // #67 有
    BinarySum bs;
    final_res |= CheckValue<string>(bs.Launch("1111", "10101"), "100100");
    count++;

    // #190 有 理解了
    ReverseBits rb;
    uint32_t n_190 = 123;
    final_res |= CheckValue<uint32_t>(rb.Launch(n_190), (uint32_t)3724541952);
    count++;

    // #191
    Number1Bits n1b;
    int n_191 = 2147483645;  // 30 个 1
    final_res |= CheckValue<int>(n1b.Hamming(n_191), 30);
    count++;

    // #136 xor 异或性质
    vector<int> nums_136 = {4,2,4,3,2};
    SingleNumber sl;
    final_res |= CheckValue<int>(sl.Doit(nums_136), 3);
    count++;

    // #137
    vector<int> nums_137 = {2,2,3,4,2,3,3};
    SingleNumberII snii;
    final_res |= CheckValue<int>(snii.Doit(nums_137), 4);
    count++;


    // #201

    // # ----------------------------------------------------- Math
    // #9 
    isPalindrome ip;
    final_res |= CheckValue<bool>(ip.Solve(1234), false);
    final_res |= CheckValue<bool>(ip.Solve(-1221), false);
    final_res |= CheckValue<bool>(ip.Solve(320), false);
    final_res |= CheckValue<bool>(ip.Solve(1234321), true);
    count++;

    // #66
    // #172 
    // #69 
    // #50 有
    RecursivePow rp;
    double x = 34.00515;
    int n = -3;
    cout << rp.LaunchSolver(x,n) << " " << std::pow(x,n) <<"\n";
    final_res |= CheckValue(rp.LaunchSolver(x,n), std::pow(x,n));
    count++;
    // #149

    // # ----------------------------------------------------- 1D DP
    // #70 有
    ClimbStairs cs;
    final_res |= CheckValue<int>(cs.Solver(5), 8);
    final_res |= CheckValue<int>(cs.Solverii(6), 13);
    final_res |= CheckValue<int>(cs.Solveriii(7), 21);
    count++;

    // #198 有
    RobHouse robh;
    vector<int> nums_198 = {2,7,9,3,1};
    final_res |= CheckValue<int>(robh.SolverDP1(nums_198), 12);
    final_res |= CheckValue<int>(robh.SolverRecursive(nums_198), 12);
    count++;

    // #139 
    WordBreak wb;
    string s = "applepenapple";
    vector<string> wordDict = {"apple", "pen"};
    final_res |= CheckValue<bool>(wb.Solver(s, wordDict), true);
    count++;

    // #322 
    // #300 有
    vector<int> nums_300 = {10,9,2,5,3,7,101,18};
    LIS lis; // 理解状态转移方程，你要首先理解什么是子序列
    final_res |= CheckValue<int>(lis.LaunchSolver(nums_300), 4);
    count++;

    // # ----------------------------------------------------- DP
    // #120 
    std::unique_ptr<Triangle> tr_ptr = std::make_unique<Triangle>();
    vector<vector<int>> triangle = {{2}, {3,4}, {6,5,7}, {4,1,8,3}};
    final_res |= CheckValue<int>(tr_ptr->LaunchSolverDP2(triangle), 11);
    count++;

    // #64 
    MinPathSum mps;
    vector<vector<int>> mps_vec = {{1,3,1},{1,5,1},{4,2,1}};
    final_res |= CheckValue<int>(mps.LaunchSolver(mps_vec), 7);
    count++;

    // #63 
    // #5 
    // #97 
    // #72 
    // #123 
    // #188 
    // #221

    // # ----------------------------------------------------- string
    // #43
    // #415
    AddString add_string;
    final_res |= CheckValue<string>(add_string.Launch("123", "456"), "579");
    final_res |= CheckValue<string>(add_string.Launch("456", "456"), "912");
    final_res |= CheckValue<string>(add_string.Launch("456", "2234"), "2690");
    count++;

    MulString mul_string;
    final_res |= CheckValue<string>(mul_string.Launch("123", "456"), "56088");
    final_res |= CheckValue<string>(mul_string.Launch("0", "456"), "0");
    count++;

    cout << "=====\nHas Failed? " << final_res <<"\n";
    cout << "Tasks done: " << count << "\n";
}
} // namespace top_150


#endif  // # TOP_150_HEADER