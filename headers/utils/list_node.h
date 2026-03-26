#ifndef LISTNODE_HEADER
#define LISTNODE_HEADER
#pragma once

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct DLLNode {
    int key, val;  // 该 DLL 存储两个值
    DLLNode* prev;
    DLLNode* next;
    DLLNode(int k, int v):key(k),val(v),prev(nullptr),next(nullptr){}
};

#endif // LISTNODE_HEADER