#ifndef PRIORITY_Q_ALGOS_HEADER
#define PRIORITY_Q_ALGOS_HEADER
#pragma once

#include <functional>
#include <queue>

using namespace std;

// priority_queue 默认是最大堆
//
class PQBasic {
public:
    void MaxPQueue() {
        priority_queue<int> max_pq; // 最大堆
        for (int i = 0; i < 10; ++i) {
            int num = rand() % 100;
            max_pq.push(num);
            cout << "insert: " << num << endl;
        }

        while (!max_pq.empty()) {
            cout << max_pq.top() << " ";
            max_pq.pop();
        }
    }

    void MinPQueue() {
        // 定义个最小堆
        priority_queue<int, /*堆的底层实现=*/vector<int>,
                /*greater表示是最小堆*/ greater<int>>
                min_pq;
        for (int i = 0; i < 10; ++i) {
            int num = rand() % 100;
            min_pq.push(num);
            cout << "insert: " << num << endl;
        }

        while (!min_pq.empty()) {
            cout << min_pq.top() << " ";
            min_pq.pop();
        }
    }

    // 自定义比较函数
    void CustomPQueue() {
        // *** 个位数小的 排前面
        auto MyComp = [](int a, int b) { return a % 10 < b % 10; };
        priority_queue<int, vector<int>, decltype(MyComp)> cus_pq(MyComp);
    }
};

// #347. Top k Frequent Elements
class TopFrequnt {
public:
    vector<int> LaunchSolver(vector<int> &nums, int k) {
        unordered_map</*元素*/ int, /*频率*/ int> freq;
        for (int i = 0; i < nums.size(); ++i) {
            freq[nums[i]]++;
        }
        // 维护一个含有k个元素的最小堆PQ,如果遍历到的元素比队列中的最小频率元素频数高，则取出队列中的最小频数元素，将新的元素入队
        // 最终，在队列中剩下的就是出现频率最高的K个元素
        priority_queue<pair</*频率*/ int, /*元素*/ int>, vector<pair<int, int>>,
                greater<pair<int, int>>>
                pq;
        for (auto itr = freq.begin(); itr != freq.end(); itr++) {
            if (pq.size() == k) {
                if (pq.top().first < itr->second) {
                    pq.pop();
                    pq.push(make_pair(itr->second, itr->first));
                }
            } else {
                pq.push(make_pair(itr->second, itr->first));
            }
        }
        // 返回pq中每个元素的second
        vector<int> res;
        while (!pq.empty()) {
            res.push_back(pq.top().second);
            pq.pop();
        }
        return res;
    }

    // 自定义比较函数
    vector<int> LaunchSolver2(vector<int> &nums, int k) {
        // 1) build a map
        unordered_map</*元素*/ int, /*频率=*/int> mp;
        for (auto item : nums) {
            mp[item]++;
        }

        //2) build a Min heap（greater 比较函数）
        auto comp = [](pair<int, int> &a, pair<int, int> &b) {
            return a.second
                    > b.second; // 不是必要的：|| (a.second == b.second && a.first > b.first);
        };
        priority_queue<pair</*元素*/ int, /*频率=*/int>, vector<pair<int, int>>,
                decltype(comp)>
                pq(comp);

        for (auto itr = mp.begin(); itr != mp.end(); itr++) {
            if (pq.size() == k) {
                if (pq.top().second < itr->second) {
                    pq.pop();
                    pq.push(make_pair(itr->first, itr->second));
                }
            } else {
                pq.push(make_pair(itr->first, itr->second));
            }
        }

        // 3) push top k words to 'res'
        vector<int> res;
        while (!pq.empty()) {
            res.push_back(pq.top().first);
            pq.pop();
        }
        return res;
    }
};

// #692. Top k Frequent words
class TopKWords {
public:
    vector<string> LaunchSolver(vector<string> &words, int k) {
        // 1) build a map <words, frequency>
        unordered_map<string, int> mp;
        for (auto item : words) {
            mp[item]++;
        }

        // 2) build a min heap，考察如何从输入中构建最小堆
        // 理解为什么用最小堆
        auto comp = [](pair<string, int> a, pair<string, int> b) {
            // 注意要满足“Sort the words with the same frequency by their lexicographical order.”
            if (a.second == b.second) {
                return a.first < b.first;  // ***
            } else {
                return a.second > b.second; //  小的靠近堆顶，故时最小堆
            }
        };
        // pq的模板参数：
        // priority_queue<T, Container, Compare>
        priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(comp)> pq(comp); // *** 细节很多
        for (auto itr = mp.begin(); itr != mp.end(); itr++) {
            if (pq.size() == k) {  // 始终维持k个元素的最小堆，节省空间
                // 这里调谓词，当谓词返回true时的操作。具体讲，当当前元素频数大于top时，执行函数体。
                if (comp(make_pair(itr->first, itr->second), pq.top())) {  // 频率大的加入pq
                    pq.pop();
                    pq.push(make_pair(itr->first, itr->second));
                }
            } else {
                pq.push(make_pair(itr->first, itr->second));
            }
        }

        // 3) push top k words to 'res'
        vector<string> res;
        while (!pq.empty()) {
            // res.push_back(pq.top().first);  // 最后需要reverse(res.begin(), res.end());
            res.insert(res.begin(),pq.top().first);  // 从头insert，就不需要reverse了
            pq.pop();
        }

        return res;
    }
};

// 225. Implement Stack using Queues
class MyStack {
private:
    queue<int> q;
public:
    MyStack() {}
    
    void push(int x) {
        q.push(x);
        for (int i{0}; i < q.size() - 1; ++i) {
            q.push(q.front());
            q.pop();
        }
    }
    int pop() {
        int res = q.front();
        q.pop();
        return res;
    }
    
    int top() {
        return q.front();
    }
    
    bool empty() {
        return q.empty();
    }
};

#endif // PRIORITY_Q_ALGOS_HEADER
