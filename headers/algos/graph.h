#ifndef GRAPH_ALG_HEADER
#define GRAPH_ALG_HEADER
#pragma once

#include <algorithm>
#include <queue>
using namespace std;

/*
[207 M]. Course Schedule  (拓扑排序检测环) 没有灵活性可言，记住这个方法，他是固定的

你总共需要上 numCourses 门课程，课程编号从 0 到 numCourses-1。
给定一个数组 prerequisites，其中 prerequisites[i] = [ai, bi] 表示：
要学习课程 ai，必须先完成课程 bi。

这是一个有向图问题
每个 [a, b] 表示一条 b → a 的有向边
问题转化为：图中是否存在环？
    有环 → 无法完成（循环依赖）→ 返回 false
    无环 → 可以完成 → 返回 true

例：
numCourses = 2, prerequisites = [[1,0]]
课程 1 依赖课程 0。 图：0 → 1 无环 true

numCourses = 2, prerequisites = [[1,0],[0,1]] 
课程 1 依赖课程 0，课程 0 依赖课程 1。图：0 ↔ 1 有环 false


逻辑：

*/
class CourseSchedule {
public:
    bool Solver(int numCourses, vector<vector<int>>& prerequisites) {
        // 步骤1：构建图和入度数组
        vector<vector<int>> graph(numCourses);      // graph[bi] = [依赖bi的课程列表]
        vector<int> indegree(numCourses, 0);        // indegree[ai] = ai的前置课程数
        
        for (auto& pre : prerequisites) {
            int ai = pre[0], bi = pre[1];
            graph[bi].push_back(ai);                // bi → ai (依赖关系)
            indegree[ai]++;                         // ai的前置+1
        }
        
        // 步骤2：初始化队列（记录入度为0的课程）
        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (indegree[i] == 0) q.push(i);        // 可直接学习的课程
        }
        
        // 步骤3：BFS处理
        int learned = 0;                            // 已学习课程数
        while (!q.empty()) {
            int current = q.front(); q.pop();
            learned++;                              // 学习当前课程
            
            // 检查当前课程是否是其他课程的前置
            for (int next : graph[current]) {
                indegree[next]--;                   // 释放对next的依赖
                if (indegree[next] == 0) {          // next的所有前置都已学完
                    q.push(next);                   // next现在可学习
                }
            }
        }
        
        // 步骤4：判断是否学完所有课程
        return learned == numCourses;               // 无环 = 能学完

    }
};

#endif  // GRAPH_ALG_HEADER
