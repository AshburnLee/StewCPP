#ifndef SELF_UNIQUE_PTR_H
#define SELF_UNIQUE_PTR_H

/*
unique_ptr 的行为是什么？

独占所有权: unique_ptr 无法复制，只能移动。这保证了只有一个 unique_ptr 指向一个对象。
自动销毁: 当 unique_ptr 超出作用域或被重置时，它会自动销毁所指向的对象。
可移动性: unique_ptr 可以通过移动语义 (move semantics) 转移所有权。
    使用 std::move 可以将一个 unique_ptr 的所有权转移给另一个 unique_ptr。
*/

#include <iostream>



#endif  // SELF_UNIQUE_PTR_H
