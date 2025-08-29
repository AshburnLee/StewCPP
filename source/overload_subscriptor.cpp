#include "overload_subscriptor.h"

using grammer::overload_subscriptor::Array;
using namespace std;

int main() {
    cout << "------------------------overload_subscript\n";
    int n = 5;
    Array arr(n);
    for (int i = 0; i < arr.length(); ++i) {
        // arr[i] = i * 5;
        arr.operator[](i) = i * 5; // ***** 调的非const， 因为被写入了
    }
    // arr.display();

    // 对const 对象，要调
    // 通过 const 对象只能调用 const 成员函数***
    const Array brr(n);
    cout << brr[0] << " " << brr[n - 1] << endl;

    return 0;
}
