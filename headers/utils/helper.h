#ifndef HELPER_HEADER
#define HELPER_HEADER
#pragma once

#include <vector>
#include <string>
#include <map>
#include <unordered_map>

#include "list_node.h"


template <typename T>  
void PrintVector(const std::vector<T>& vec) {
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

template <>
void PrintVector<std::vector<int>>(const std::vector<std::vector<int>>& vec) {
    for (const auto& innerVec : vec) {
        for (int elem : innerVec) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}


template <typename K, typename V>
void PrintMap(const std::map<K, V>& hash) {
    for (const auto& pair : hash ) {
        std::cout << "[ " << pair.first << ": " << pair.second << "]" << "\n";
    }
}

template <typename K, typename V>
void PrintMap(const std::unordered_map<K, V>& hash) {
    for (const auto& pair : hash ) {
        std::cout << "[ " << pair.first << ": " << pair.second << "]" << "\n";
    }
}

// T: int, float, std::vector, ...
template <typename T>  
bool CheckValue(const T& valueToCheck, const T& specifiedValue) {  
    if (valueToCheck == specifiedValue) {  
        return 0;
    } else {
        std::cout << "CheckValue failed\n";
        return 1;
    }
} 


/*
============================== linkedlist
*/

ListNode* CreateList(const std::vector<int>& nodes) {
    if (nodes.empty()) return nullptr;

    ListNode* head = new ListNode(nodes[0]);
    ListNode* curr = head; 
    for (int i = 1; i < nodes.size(); ++i) {
        curr->next = new ListNode(nodes[i]);
        curr = curr->next;
    }
    return head;
}

bool SameList(ListNode* head1, ListNode* head2){
    ListNode* curr1 = head1;
    ListNode* curr2 = head2;

    while(curr1 && curr2){
        if (curr1->val != curr2->val)
            return false;
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    return curr1 == nullptr && curr2 == nullptr;
}

void PrintLinkedList(ListNode* head, int max_iter = 50) {
    ListNode* curr = head;
    int iter = 0;
    while (curr != nullptr && iter < max_iter) {
        std::cout << curr->val << "=>";
        curr = curr->next;
        iter++;
    }

    if (iter == max_iter && curr->next != nullptr) {
        std::cout << "loop in list\n";
    } else {
        std::cout << "nullptr\n";
    }
}

#endif  // HELPER_HEADER
