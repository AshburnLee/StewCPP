#ifndef LINKEDLIST_ALGS_HEADER
#define LINKEDLIST_ALGS_HEADER
#pragma once

#include "list_node.h"

// #206. reverse linked list
// 关键：保证循环能正确进行，要维持变量的定义不变
class ReverseSolver {
public:
    ListNode *LaunchSolver(ListNode *head) {
        ListNode *cur = head;
        ListNode *pre = nullptr;
        ListNode *nxt = head; // 防止链表断掉
        while (cur) {
            nxt = cur->next;
            cur->next = pre; // reverse op
            // *** 这两步是保证pre和cur的定义不变，循环不变量
            pre = cur;
            cur = nxt;
        }
        return pre;
    }
};

// #92. reverse linked list from left to right
class ReverseBetween {
public:
    ListNode *LaunchSolver(ListNode *head, int left, int right) {
        ListNode *pre = nullptr;
        ListNode *cur = head;
        ListNode *nxt = head;
        // step1: 先移动到left，找到left及原本left前的节点，分别为tag1&tag2
        // 用于翻转后的链接
        for (int i = 1; i < left; ++i) {
            pre = cur;
            cur = cur->next;
        }
        ListNode *tag1 = pre;
        ListNode *tag2 = cur;

        // step2: reverse from m to n, loop (n-m)
        for (int i = left; i <= right; ++i) {
            nxt = cur->next;
            cur->next = pre;
            pre = cur;
            cur = nxt;
        }
        // step3: link
        if (tag1 != nullptr) { // m>1
            tag1->next = pre;
        } else {
            head = pre;
        }
        tag2->next = cur;
        return head;
    }
};

// #141. 判断list中是否有环
class DetectCycle {
public:
    bool LaunchSolver(ListNode *head) {
        // step1: 确定有环并且快慢指指针相遇
        if (!head) { return false; }
        ListNode *slow = head;
        ListNode *fast = head;
        bool has_cycle = false;

        while (slow && fast) {
            slow = slow->next;
            fast = fast->next;

            if (fast) fast = fast->next;
            // 为什么 fast == slow 就有环？因为一快一慢，如果有环，快的一定可以追上慢的 **
            if (fast && (fast == slow)) {
                has_cycle = true;
                break;
            }
        }
        return has_cycle;
    }
};

// #142. linked list cycle II, return the node where the cycle starts
class DetectCycleII {
public:
    ListNode *LaunchSolver(ListNode *head) {
        // step1: 确定有环并且快慢指指针相遇
        if (!head) { return nullptr; }
        ListNode *slow = head;
        ListNode *fast = head;
        bool has_cycle = false;

        while (slow && fast) {
            slow = slow->next;
            fast = fast->next;

            if (fast) fast = fast->next;
            if (fast && (fast == slow)) {
                has_cycle = true;
                break;
            }
        }
        
        // step2:逻辑是，当相遇后，fast从head出发，两个指针同时走一步，
        // 直到相遇，相遇点就是环的入口
        if (!has_cycle) return nullptr;
        fast = head;
        while (fast != slow) {
            slow = slow->next;
            fast = fast->next;
        }
        if (fast && slow)
            return fast;
        else
            return nullptr;
    }
};

// #160. Intersection of Two Linked Lists
class Intersection {
public:
    ListNode *LaunchSolver(ListNode *headA, ListNode *headB) {
        ListNode *n1 = headA;
        ListNode *n2 = headB;

        // one step at the same time
        // 当两指针所走过的路程一样长时，二者相遇，相遇节点及交叉点
        while (n1 != n2) {
            if (n1 == nullptr) {
                n1 = headB;
            } else {
                n1 = n1->next;
            }
            if (n2 == nullptr) {
                n2 = headA;
            } else {
                n2 = n2->next;
            }
        }
        return n1;
    }
};

// #1721. Swapping Nodes in a Linked List
class SwapNodes {
public:
    ListNode *LaunchSolver(ListNode *head, int k) {
        ListNode *cur = head;
        ListNode *left = head;
        ListNode *right = head;
        int count = 1;
        // step1:根据k找到需要交换的两个节点
        while (cur->next) {
            // cur 走的距离=left走的距离+right走的距离!
            if (count < k) {
                left = left->next;
            } else {
                right = right->next;
            }
            count++;
            cur = cur->next;
        }

        // step2: 交换节点数值
        if (left && right) {
            int tmp = left->val;
            left->val = right->val;
            right->val = tmp;
        }

        return head;
    }
};

// #24. Swap nodes in pairs
class SwapPairs {
public:
    ListNode *LaunchSolver(ListNode *head) {
        if (!head || head->next == nullptr) return head;
        ListNode *dhead = new ListNode(0, head);
        ListNode *cur = dhead;
        // 确保每次循环cur,l,r的含义不变，相对位置不变
        while (cur->next && cur->next->next) {
            ListNode *l = cur->next;
            ListNode *r = cur->next->next;
            cur->next = r;
            l->next = r->next;
            r->next = l;
            cur = l;
        }
        return dhead->next;
    }
};

// #24. EX, Reverse list every k nodes
// 每k个节点翻转
// NOTE: cur始终是遍历的节点，中途不要改变其定义和功能
// 每个变量哟啊保证循环时的定义和功能不变
class ReverseKNodes {
public:
    ListNode *LaunchSolver(ListNode *head, int k) {
        ListNode *dhead = new ListNode(-1, head);
        ListNode *cur = dhead;
        while (cur) {
            ListNode *tmp = cur;
            for (int i = 0; i < k; ++i) {
                tmp = tmp->next;
                if (!tmp) return dhead->next;
            }
            ListNode *nxt = tmp->next; // 不使链断掉
            // 得到局部反转后的头和尾
            pair<ListNode *, ListNode *> reverse = ReverseList(cur->next, tmp);
            tmp = reverse.first;
            ListNode *p_head = reverse.second;
            // 衔接
            cur->next = tmp;
            p_head->next = nxt;
            cur = p_head;
        }
        return dhead->next;
    }

private:
    // 将列链表从节点head到节点tail翻转，注意tail不一定是nullptr
    // 保证了结果是从head到tail，翻转，这样作为子函数才可用
    pair<ListNode *, ListNode *> ReverseList(ListNode *head, ListNode *tail) {
        ListNode *pre = tail->next;
        ListNode *cur_tail = nullptr;
        ListNode *cur = head;
        while (cur != pre) {
            ListNode *tmp = cur->next;
            cur->next = cur_tail;
            cur_tail = cur;
            cur = tmp;
        }
        return pair<ListNode *, ListNode *>(tail, head);
    }
};

// #19. 删除倒数第n个node
// 关键逻辑：保证两个指针的距离是n
// 注意：量表长度未知，
// mid, O(n), O(1)
class RemoveNthNodeFromEndofList {
public:
    ListNode *LaunchSolver(ListNode *head, int n) {
        ListNode *dhead = new ListNode(-1, head);
        ListNode *pre = new ListNode(-1, dhead);  // 新node

        ListNode *cur = dhead; 
        ListNode *tar = dhead; // 不是新node

        // 1) cur 走 n-1 步
        int count = 0;
        while (count < n - 1) {
            cur = cur->next;
            count++;
        }

        // 2) cur 走到底，同时pre和tar 与cur步伐一致，
        // 保证了当cur走到底时，tar恰好指向待删除node，pre恰好执行待删除node前面的node
        while (cur->next) {
            cur = cur->next;
            pre = pre->next;
            tar = tar->next;
        }
        pre->next = tar->next;
        return dhead->next;
    }
};

// #2. add two numbers
/*
Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Explanation: 342 + 465 = 807
*/
// mid, O(n), O(1)
class AddTwo {
public:
    ListNode *LaunchSolver(ListNode *l1, ListNode *l2) {
        ListNode *res_head = nullptr;
        ListNode *pre = nullptr; // 当前节点cur的前一个节点
        int carry = 0;

        while (l1 || l2) {
            int val1 = l1 ? l1->val : 0;
            int val2 = l2 ? l2->val : 0;
            int sum = val1 + val2 + carry;

            carry = sum / 10;
            int val = sum % 10;
            ListNode *cur = new ListNode(val);

            // 链接输出链表
            if (!res_head) res_head = cur; // 只执行第一次
            if (pre) pre->next = cur; // 目的是链接节点
            pre = cur; // 每次loop后，pre和cur指向同一节点

            // 保证下次循环不变量
            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
        }
        if (carry > 0) {
            ListNode *tail = new ListNode(carry);
            pre->next = tail;
        }
        return res_head;
    }
};

// 148. Sort List,无需链表，返回升序排列后的链表
// 算法：merge sort , 分治***
// Insight：使用快慢指针找到中间节点
// 与#108 一样，新分，分分分，后做动作
class SortList {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }
        // 通过快买指针找到中间节点
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast->next && fast->next->next) {
            // 访问之前要判断是否为空，间while()中
            slow = slow->next;
            fast = fast->next->next;
        }
        // 1. 分割链表
        ListNode* sec_sorted = slow->next; 
        slow->next = nullptr;

        // 2. 递归排序两个字链表
        ListNode* l1 = sortList(head);
        ListNode* l2 = sortList(sec_sorted);

        // 3. 理解为l1 和 l2 已经分别有序了，然后
        // 合并两个已排序的链表
        return merge_lists(l1, l2);
    }
private:
    ListNode* merge_lists(ListNode* l1, ListNode* l2) {
        ListNode d_head(0);
        ListNode* curr = &d_head; 

        while (l1 && l2) {
            if (l1->val > l2->val) {
                curr->next = l2;
                l2 = l2->next;
            } else {
                curr->next = l1;
                l1 = l1->next;
            }
            curr = curr->next; // 指向尾节点
        }

        if(l1) curr->next = l1;
        if(l2) curr->next = l2;

        return d_head.next;
    }
};
#endif // LINKEDLIST_ALGS_HEADER
