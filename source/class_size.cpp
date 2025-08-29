#include "class_size.h"
#include "list_node.h"
#include "tree_node.h"

int main () {
    std::cout << "------------------------class_size\n";
    std::cout << "Base size: " << sizeof(grammer::class_size::Base) << "\n";
    std::cout << "Child size: " << sizeof(grammer::class_size::Child) << "\n";
    std::cout << "Empty size: " << sizeof(grammer::class_size::Empty) << "\n";;

    // 指针的大小取决于系统的位数：在 32 位系统上，指针通常占用 4 个字节；在 64 位系统上，指针通常占用 8 个字节。
    // 不论指针指向的类型是什么，指针本身的大小都是固定的。
    ListNode *listNodePtr = nullptr;
    TreeNode *treeNodePtr = nullptr;

    std::cout << "ListNode size: " << sizeof(ListNode) << "\n";  // 8+8
    std::cout << "listNodePtr size: " << sizeof(listNodePtr) << "\n"; // 8
    std::cout << "TreeNode size: " << sizeof(TreeNode) << "\n";   // 8+8+8
    std::cout << "treeNodePtr size: " << sizeof(treeNodePtr) << "\n";  // 8
    return 0;
}
