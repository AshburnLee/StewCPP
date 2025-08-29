#ifndef HUAWEI_HEADER
#define HUAWEI_HEADER
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

/*
 map, set, dfs, bfs, 表，lambda+自定义排序，based on sort 的贪心，stack，queue，dp
 题目特点是可以通过穷举法，但是一定有更好的方法！
*/
namespace huawei {
int count = 0;
bool final_res = 0;
void Launcher(){
    std::cout << "================ HUAWEI ================\n";
    // 1909 [e]
    CanBeIncreasing cbi;
    vector<int> cbi_vec1 = vector<int>{1,2,3};
    vector<int> cbi_vec2 = vector<int>{1,2,10,5,7};
    vector<int> cbi_vec3 = vector<int>{1,3,10,2,7};
    vector<int> cbi_vec4 = vector<int>{1,3,10,2,10};
    final_res |= CheckValue<bool>(cbi.Solver(cbi_vec1), true);
    final_res |= CheckValue<bool>(cbi.Solver(cbi_vec2), true);
    final_res |= CheckValue<bool>(cbi.Solver(cbi_vec3), false);
    final_res |= CheckValue<bool>(cbi.Solver(cbi_vec4), false);
    count++;

    // 735 [m]
    Collision ac; // 使用 stack
    vector<int> ac_arr1 = {5,10,-5};
    vector<int> ac_arr2 = {5,8,-8};
    vector<int> ac_arr3 = {10,2,-5};
    final_res |= CheckValue<vector<int>>(ac.Solver(ac_arr1), vector<int>{5,10});
    final_res |= CheckValue<vector<int>>(ac.Solver(ac_arr2), vector<int>{5});
    final_res |= CheckValue<vector<int>>(ac.Solver(ac_arr3), vector<int>{10});
    count++;

    // 56  lambda, 自定义比较函数
    MergeIntervals mi;  
    vector<vector<int>> vecs_56 = {{1,3},{2,6},{8,10},{15,18}};
    final_res |= CheckValue(mi.Solver(vecs_56), vector<vector<int>> {{1,6},{8,10},{15,18}});
    count++;

    // 121  遍历过程中的最大值
    BestTime2BuyAndSellStock bt2bass; 
    vector<int> bt2bass_vec = {7,1,5,3,6,4};
    final_res |= CheckValue<int>(bt2bass.Solver(bt2bass_vec), 5);
    final_res |= CheckValue<int>(bt2bass.LaunchSolverDP(bt2bass_vec), 5);
    count++;

    // 122  贪婪
    BestTime2BuyAndSellStockII btbsii;
    final_res |= CheckValue<int>(btbsii.LaunchSolver(bt2bass_vec), 7);
    count++;

    // 123  DP 
    BestTime2BuyAndSellStockIII btbsiii;  // DP, 第二次与第一次有关
    vector<int> btbsiii_vec = {3, 3, 5, 0, 0, 3, 1, 4};
    final_res |= CheckValue<int>(btbsiii.Solver(btbsiii_vec), 6);
    count++;

    // LongestNumber in string
    LongestNumber ln;  // string, string 常用函数
    string lns1 = "abcd12345efg";
    final_res |= CheckValue<string>(ln.Solver(lns1), "12345");
    string lns2 = "a123bc4567def890";
    final_res |= CheckValue<string>(ln.Solver(lns2), "4567");
    string lns3 = "abc123def1234";
    final_res |= CheckValue<string>(ln.Solver(lns3), "1234");
    string lns4 = "abcdefg";
    final_res |= CheckValue<string>(ln.Solver(lns4), "");
    string lns5 = "12abc12";
    final_res |= CheckValue<string>(ln.Solver(lns5), "12");
    count++;

    // 739 stack
    DailyTemprature dt;
    vector<int> dt_vec = {73, 74, 75, 71, 69, 72, 76, 73};
    final_res |= CheckValue<vector<int>>(dt.Solver(dt_vec), vector<int>{1,1,4,2,1,1,0,0});
    count++;

    // 102  queue, 队列辅助层序遍历。 队列的特性（先进先出，FIFO）完美契合了层序遍历的顺序
    LevelOrderSolver los;
    count++;

    // 225. Queues
    MyStack mstck;
    count++;

    // 435. 基于sort的贪婪,首先判断这个问题是这一类的，比如你发现了题目中有求最值。
    EraseOverlapIntervals eoi;
    vector<vector<int>> eoi_vec1 = {{1,2},{2,3},{3,4},{1,3}};
    vector<vector<int>> eoi_vec2 = {{1,2},{1,2},{1,2}};
    vector<vector<int>> eoi_vec3 = {{1,2},{2,3}};
    final_res |= CheckValue<int>(eoi.Solver(eoi_vec1), 1);
    final_res |= CheckValue<int>(eoi.Solver(eoi_vec2), 2);
    final_res |= CheckValue<int>(eoi.Solver(eoi_vec3), 0);
    count++;

    // 629. map 优先队列, lambda
    TopKWords tkw;
    vector<string> tkw_vec = {"i", "love", "leetcode", "i", "love", "coding"};
    final_res |= CheckValue<vector<string>>(tkw.LaunchSolver(tkw_vec, 2), vector<string>{"i", "love"});
    count++;

    // 3. set
    LongestSubstringWithoutRepeatingCharacters lrc;
    string s_3 = "abcbcabb";
    string s_3_1 = "pwwkew";
    final_res |= CheckValue(lrc.Launch(s_3), 3);
    final_res |= CheckValue(lrc.Launch(s_3_1), 3);
    count++;

    // 128. set
    LogestConsecutiveSequence lcs;
    vector<int> lcs_vec = {100,4,200,1,3,2};
    final_res |= CheckValue(lcs.LaunchSolver(lcs_vec), 4);
    count++;

    // 159 . map
    LongestSubstringwithAtMostTwoDistinctCharacters lss;
    string s_159 = "eceba";
    string s_159_1 = "ccaabbb";
    final_res |= CheckValue(lss.LaunchSolver(s_159), 3);
    final_res |= CheckValue(lss.LaunchSolver(s_159_1), 5);
    count++;

    // 438. 长度时26 的计数器，滑动窗口
    FindAllAnagramsinaString faas;
    final_res |= CheckValue(faas.LaunchSolver("cbaebabacd", "abc"), vector<int>{0,6});
    final_res |= CheckValue(faas.LaunchSolver("ababba", "ba"), vector<int>{0,1,2,4});
    count++;

    // Combination Sum    Longest Increasing Path in a Matrix
    // 200. [m] dfs
    NumIsLands ni;
    vector<vector<char>> num_200 = {{'1','1','0','0','0'},
                                    {'1','1','0','0','0'},
                                    {'0','0','1','0','0'},
                                    {'0','0','0','1','1'} };
    final_res |= CheckValue(ni.LaunchSolver(num_200), 3);
    count++;

    // 39. [m] Combination sum  dfs 回溯  数字可重用  记住这个套路 target = target - curr
    CombinationSum cs;
    vector<int> cs1 = {2,3,6,7}; int cs_target = 7;
    final_res |= CheckValue(cs.LaunchSolver(cs1, cs_target), vector<vector<int>>{{2,2,3},{7}});
    count++;

    // 77. [m] combination   dfs 回溯 数字不能重用  记住这个套路 target = target - curr
    Combination com;
    final_res |= CheckValue(com.LaunchSolver(3, 2), vector<vector<int>> {{1,2},{1,3},{2,3}});
    count++;

    // 322. [m] DP
    CoinChange cc;
    vector<int> cc_vec = {1,2,5};
    final_res |= CheckValue(cc.LaunchSolver(cc_vec, 11), 3);
    count++;

    // 120  [m] DP
    std::unique_ptr<Triangle> tr_ptr = std::make_unique<Triangle>();
    vector<vector<int>> triangle = {{2}, {3,4}, {6,5,7}, {4,1,8,3}};
    final_res |= CheckValue<int>(tr_ptr->LaunchSolverDP3(triangle), 11);
    count++;

    // 64 [m] dp 
    MinPathSum mps;
    vector<vector<int>> mps_vec = {{1,3,1},{1,5,1},{4,2,1}};
    final_res |= CheckValue<int>(mps.LaunchSolver(mps_vec), 7);
    count++;

    // 198 [m] dp
    RobHouse robh;
    vector<int> nums_198 = {2,7,9,3,1};
    final_res |= CheckValue<int>(robh.SolverDP1(nums_198), 12);
    final_res |= CheckValue<int>(robh.SolverDP2(nums_198), 12);
    count++;

    // 130. [m]  bfs Surrounded Regions
    

    //   . bfs
    //   . hash table
    //  . 前缀和    
    cout << "=====\nHas Failed? " << final_res <<"\n";
    cout << "Tasks done: " << count << "\n";
    }
}

#endif  // HUAWEI_HEADER
