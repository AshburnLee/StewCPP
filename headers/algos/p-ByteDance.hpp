#ifndef BYTEDANCE_HEADER
#define BYTEDANCE_HEADER
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
#include "graph.h"
#include "helper.h" // CheckValue PrintVector PrintMap

/*
ByteDance & 寒武纪
一般考察的是实现简短的题目，
*/
namespace bytedance {
int count = 0;
bool final_res = 0;
void Launcher(){
    std::cout << "================ByteDance ================\n";
        // DP
        UniquePath up;
        ClimbStairs cs;
        CoinChange cc;
        RobHouse rh;
        LongestCommonSubsequence lcs;
        MaxSubArray msa;

        // 滑动窗口、频数容器
        LongestSubstringWithoutRepeatingCharacters lswrc;  // 3
        FindAllAnagramsinaString faa;
        ThreeSum ts;
        TwoSum ts2;
        MinSubArrayLenSolver msal;
        BestTime2BuyAndSellStock btbs;
        MaxConsecutiveOnesIII mco;
        LongestRepeatingCharacterReplacement lrcr;

        // Tree
        InorderTraversalSolver io;
        LowestCommonAncestorofaBinaryTree lca;
        ConstructBT cbst;
        SubtreeofAnotherTree stt;
        MostFrequentSubtreeSum mfss;
        SumofDescendants sd;
        BinaryTreeTilt btt;
        LongestUnivaluePath lup;
        UnivaluedBinaryTree ub;

        // linked list
        OddEvenList oel;
        IntersectionofTwoLinkedLists itl; 
        
        // bit 操作
        PowerOfTwo pt;
        SingleNumber sn;
        ReverseBits rb;

        // heap
        TopFrequnt tf;

        // DFS
        NumIsLands ni;
        DiameterofBinaryTree dbt;
        MaxDepth md;

        // set map
        LogestConsecutiveSequence lcsii;  // 128
        LRUCache lruc(0);
        MinimunIndexSumLists mis;

        // stack, queue
        ValidParetheses vp;
        QueueusingStacks qs;
        LevelOrderSolver lo;
        VerticalOrder vo;

        CourseSchedule csii;
    }
} // bytedance

#endif  // BYTEDANCE_HEADER
