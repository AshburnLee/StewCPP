#include "copy_deep.h"

using grammer::copy_deep::Base2;
using grammer::copy_deep::Base;
using grammer::copy_deep::My_Array;
using namespace std;

void Test_My_Array() {
    My_Array arr1(5);
    for (int i = 0; i < 5; ++i) {
        arr1[i] = i;
    }
    PrintMy_Array(arr1);
    My_Array arr2 = arr1; // 同 arr2(arr1);
    PrintMy_Array(arr2);
    arr1[0] = 10; // 因为是深拷贝 所以修改arr1 不影响arr2
    PrintMy_Array(arr1);
    PrintMy_Array(arr2);
}

void TestBase() {
    int a = 10;
    int b = a; //拷贝
    Base obj1(10, 20);
    Base obj2 = obj1; //拷贝
    return;
}

void TestBase2() {
    Base2 obj1(10);
    cout << "obj1: " << obj1.GetCount() << " time: " << obj1.GetTime() << endl;
    sleep(5 /*second*/);
    Base2 obj2 = obj1;
    cout << "obj2: " << obj2.GetCount() << " time: " << obj2.GetTime() << endl;
    sleep(5);
    Base2 obj3(20);
    cout << "obj3: " << obj3.GetCount() << " time: " << obj3.GetTime() << endl;
}

int main() {
    cout << "------------------------copy_deep\n";
    TestBase();
    Test_My_Array();

    TestBase2();
    /* 的输出:
	obj1: 1 time: 1654255854
	obj2: 2 time: 1654255856
	obj3: 3 time: 1654255858
	*/
    return 0;
}
