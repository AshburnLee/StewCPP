#include "overload_assignment.h"

using grammer::overload_assignment::Array;


int main() {
    std::cout << "------------------------overload_assignment\n";
    Array arr(3);
    for (int i = 0; i < arr.length(); ++i) {
        arr[i] = i;
    }
    ShowArray(arr);

    Array arr2(10);
    for (int i = 0; i < arr2.length(); ++i) {
        arr2[i] = i;
    }
    ShowArray(arr2);

    // arr2 = arr;  // 调赋值运算符
    arr2.operator=(arr); // 同上
    ShowArray(arr2);
    arr[0] = 123;
    ShowArray(arr); // 修改了arr
    ShowArray(arr2); // 没有修改arr2

    return 0;
}