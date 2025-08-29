#ifndef STACK_ALGS_HEADER
#define STACK_ALGS_HEADER
#pragma once

#include <stack>
#include <iostream>
#include <sstream> // stringstream
using namespace std;

// 735 [m]：Asteroid Collision
/*
对于数组中的每一个小行星，正数表示它向右移动，负数表示它向左移动。每一颗小行星的速度都相等。
找出碰撞后剩下的所有小行星。碰撞规则：两个行星相互碰撞，绝对值较小的行星会爆炸。
如果两颗行星大小相同，则两颗行星都会爆炸。朝同一方向移动的行星永远不会发生碰撞。
*/ 
// 使用栈来存储幸存的行星。 栈的特点是后进先出，这非常适合模拟碰撞的传递性。
class Collision{
public:
    vector<int> Solver(vector<int> asteroids) {
        stack<int> stck;    
        for (int ast: asteroids) {
            if (ast > 0) {
                stck.push(ast);
            } else {
                while (!stck.empty() && stck.top() > 0 && stck.top() < -ast) {
                    stck.pop();
                }

                if (stck.empty() || stck.top() < 0) {
                    stck.push(ast);
                } else if (stck.top() == -ast) {
                    stck.pop();
                } else {

                }
            }
        }
    
        vector<int> res;
        while (!stck.empty()) {
            res.insert(res.begin(), stck.top());
            stck.pop();
        }
        return res;
    }
};

// 739 medium：每日温度
/*
返回值表示从这一个数开始往后需要多少个数，才能遇到第一个比这个数大的数，如果找不到，返回零，例：
Input: temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]

Key：单调栈的应用 , 栈中存的是索引 而非温度 *** 记住经典问题 ***
*/
class DailyTemprature {
public:
    vector<int> Solver(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> res(n, 0);
        stack<int> stack;
    
        for (int i = 0; i < n; ++i) {
            while (!stack.empty() && temperatures[i] > temperatures[stack.top()]) {
                int index = stack.top();
                stack.pop(); // 意味着我们找到了栈顶索引 index 对应的温度的升温日 ***
                res[index] = i - index; // 在这里更新结果结果，
            }
            stack.push(i);
        }
    
        return res;
    }
};


class QueueFromStacks {
private:
    stack<int> stack_in;
    stack<int> stack_out;

public:
    void AppendFromTail(int value) { stack_in.push(value); }

    void DeleteFromHead() {
        // 当 out是空，先将in中加入到out
        if (stack_out.empty()) {
            while (!stack_in.empty()) {
                int tmp = stack_in.top();
                stack_out.push(tmp);
                stack_in.pop();
            }
        }
        // 当 out不是空，后 才删除顶部数据
        if (!stack_out.empty()) { stack_out.pop(); }
    }
};

// 20. valid parentheses
// 栈的基本使用，一般的，取top元素进行比较等操作
/*
Input: s = "()[]{}"
Output: true
*/
class ValidParetheses {
public:
    bool Solver(string s) {
        stack<char> stck;
        for (int i = 0; i < s.length(); ++i) {
            // 左括号直接入栈
            if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
                stck.push(s[i]);
            } else { // 如果是右括号，则判断是否与栈顶元素匹配
                // 
                if (stck.empty()) return false;
                char cur = stck.top(); // top之前，先判断stck是否为空**

                char exp;
                if (s[i] == ')')
                    exp = '(';
                else if (s[i] == ']')
                    exp = '[';
                else if (s[i] == '}')
                    exp = '{';

                if (cur != exp) return false;
                stck.pop();
            }
        }
        if (!stck.empty()) return false;
        return true;
    }
};

// 71. Simplify Path
/*
Input: path = "/home//foo/"
Output: "/home/foo"

Input: path = "/../"
Output: "/"

Input: path = "/.../a/../b/c/../d/./"
Output: "/.../b/d"
*/
// insight: 首先要清楚构成路径的规则；使用stack处理 "/a/.." 这种情况
class SimplifyPath {
public:
    string Solver(const string path) {
        std::stack<std::string> st;
        std::string res = "";
        std::vector<std::string> tokens; // 将path以“/”分割
        std::string token; // 暂存两个"/"之间的内容

        // step1 get tokens, 用"/"分割path
        for (char c : path) {
            if (c == '/') {
                if (!token.empty()) {
                    tokens.push_back(token);
                    token = "";
                }
            } else {
                token += c;
            }
        }
        if (!token.empty()) tokens.push_back(token);

        // step2 construct stack，来处理"/a/../"情况
        for (const string& t : tokens) {
            if (t == "..") {
                if (!st.empty()) st.pop(); // Pop if it's ".." and the stack isn't empty
            } else if (t != "." && !t.empty()) {
                st.push(t); // Push if it's not "." or empty
            }
        }

        // step3 build res
        while (!st.empty()) {
            res = "/" + st.top() + res; // Build the simplified path from the stack
            st.pop();
        }

        return res.empty() ? "/" : res; // Return "/" if the stack was empty (only "/")
    }
};

// 155. Min Stack
/*
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
*/
// 在常量时间内获取最小值

// insight: 这里有个tricky的地方，min_stk的长度不定，，但是可以满足只要你想找min值，
// min_stk 中一直有这个最小值。
/*
例：
s:     4,3,2,1  顶
min_s: 4,3,2,1  顶

s:     1,2,3,4  顶
min_s: 1        顶

s:     4,3,1,2  顶
min_s: 4,3,1    顶
*/
class MinStack {
private:
    stack<int> stk;     // 存贮所有元素
    stack<int> min_stk; // 用于存储最小值

public:
    MinStack() {}
    ~MinStack() {}

    void push(int val) {
        stk.push(val);
        // 维护 min_stk
        if (min_stk.empty() || val <= min_stk.top()) {
            min_stk.push(val);
        }
    }

    void pop() {
        if (min_stk.top() == stk.top() ) {
            min_stk.pop();
        }
        stk.pop();
    }

    int top() {
        return stk.top();
    }
    int getMin() {
        return min_stk.top();
    }
};

class Infix2Postfix {
private:
    // 定义运算符优先级
    unordered_map<char, int> precedence = {
        {'(', 0},
        {'+', 1},
        {'-', 1},
        {'*', 2},
        {'/', 2},
        {'^', 3}
    };

    // 函数用于检查字符是否为运算符
    bool isOperator(char c) {
        return precedence.count(c) > 0; // count 返回 map 中 key 的数量
    }

    // 函数用于获取运算符的优先级
    int getPrecedence(char c) {
        return precedence[c];
    }

    string infixToPostfix(string infix) {
        stack<char> s;
        string postfix = "";

        for (char c : infix) {
            // 1. 如果是操作数，直接添加到后缀表达式, 因为infix和postfix 中操作数的相对顺序是不变的 ***
            if (isalnum(c)) {
                postfix += c;
            }
            // 2. 如果是左括号，压入栈中
            else if (c == '(') {
                s.push(c);
            }
            // 3. 如果是右括号，弹出栈中所有运算符直到遇到左括号
            else if (c == ')') {
                while (!s.empty() && s.top() != '(') {
                    postfix += s.top();
                    s.pop();
                }
                s.pop(); // 弹出左括号 ')'
            }
            // 4. 如果是运算符
            else if (isOperator(c)) {
                // 弹出栈中所有优先级大于等于当前运算符的运算符
                // getPrecedence(s.top()) >= getPrecedence(c) ：当 c = +，s.top = (, c优先级低于s.top，不循环，直接将+入栈
                // 这里体现了，为什么'(' 优先级最低 ***
                while (!s.empty() && getPrecedence(s.top()) >= getPrecedence(c)) {
                    postfix += s.top();
                    s.pop();
                }
                // 将当前运算符压入栈中
                s.push(c);
            }
        }
        // 弹出栈中剩余的所有运算符
        while (!s.empty()) {
            postfix += s.top();
            s.pop();
        }
        return postfix;
    }

public:
    string Solver(string infix) {
        return infixToPostfix(infix);
    }
};

// 函数用于执行算术运算
double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                throw runtime_error("Division by zero");
            }
            return a / b;
        default: throw runtime_error("Invalid operator");
    }
}

class Calculatefix {
    // 计算后缀表达式的值
    double evaluatePostfix(const string& expression) {
        stack<double> s;
        stringstream ss(expression); /// 使用stringstream方便处理空格分隔的操作数
        string token;

        while (ss >> token) {
            // 检查是否为数字 (处理负数)
            if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) { 
                s.push(stod(token)); // 将数字压入栈
            } else { // 如果是操作数
                if (s.size() < 2) {
                    throw runtime_error("Not enough operands");
                }
                double val2 = s.top(); s.pop();  // val2 是后入栈的，所以它首先出栈 ***
                double val1 = s.top(); s.pop();  // ***
                s.push(applyOp(val1, val2, token[0])); // 执行运算并将结果压入栈 ***
            }
        }
        if (s.size() != 1) {
            throw runtime_error("Invalid expression");
        }
        return s.top();
    }

    double evaluatePrefix(string expression) {
        reverse(expression.begin(), expression.end()); // 反转字符串以便从左到右处理 ***
        stack<double> s;
        stringstream ss(expression);
        string token;

        while (ss >> token) {
            if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
                s.push(stod(token));
            } else {
                if (s.size() < 2) {
                    throw runtime_error("Not enough operands");
                }
                double val1 = s.top(); s.pop();  // 前操作数 ***
                double val2 = s.top(); s.pop();  // 后操作数 ***
                s.push(applyOp(val1, val2, token[0]));  // ***
            }
        }

        if (s.size() != 1) {
            throw runtime_error("Invalid expression");
        }

        return s.top();
    }

public:
    float SolverPrefix(string expression) {
        stringstream ss(expression); // 将experssion 转换为stringstream，方便处理空格分隔的操作数
        getline(ss, expression); // 使用getline读取包含空格的输入  
        try {
            float res = evaluatePrefix(expression);
            return res;
        } catch (const runtime_error& error) {
            cerr << "Error: " << error.what() << endl;
        }
        return 0;
    }
    float SolverPostfix(string expression) {
        stringstream ss(expression); // 将experssion 转换为stringstream，方便处理空格分隔的操作数
        getline(ss, expression); // 使用getline读取包含空格的输入  
        try {
            float res = evaluatePostfix(expression);
            return res;
        } catch (const runtime_error& error) {
            cerr << "Error: " << error.what() << endl;
        }
        return 0;
    }
};

#endif // STACK_ALGS_HEADER
