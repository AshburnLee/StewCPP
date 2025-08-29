#include "copy_constructor.h"

using grammer::copy_constructor::Student;

int main() {
    Student s1("Xioaming", 21, 99);
    Student s3(s1); //调拷贝构造函数
    Student s2 = s1; //调拷贝构造函数，这个其实值赋值运算符
    Student s4("Junhui", 20, 100);
    s4 = s1; //

    s1.Display();
    s2.Display();
    s3.Display();
    s4.Display();
    return 0;
}


