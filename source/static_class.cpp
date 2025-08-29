#include "static_class.h"

using grammer::static_class::StaticObj;
using grammer::static_class::Student2;
using grammer::static_class::Student;
using grammer::static_class::_func;
using namespace std;

void TestStaticClass() {

    // std::cout<<"StaticObj::a: "<<StaticObj::a<<std::endl; // 3). error
    std::cout << "StaticObj::b: " << StaticObj::b << std::endl;
    std::cout << "StaticObj::c: " << StaticObj::c << std::endl;

    StaticObj s1; // b = 3
    cout << s1.GetB() << "\n";
    StaticObj s[3]; // b = 6
    StaticObj s2; // b = 7
    cout << s2.GetB() << "\n"; // 4). 所有类实例间共享
}

void TestStaticVar() {
    for (int i = 0; i < 5; ++i) {
        _func();
    }
}

void TestStudent() {
    // 创建匿名对象，之所以使用匿名对象，
    // 是因为每次创建对象后只会使用它的 show() 函数，不再进行其他操作。
    // 不过使用匿名对象无法回收内存，会导致内存泄露，在中大型程序中不建议使用。
    (new Student("Michael", 90))->Show();
    (new Student("Mike", 92))->Show();
    (new Student("Tommy", 87))->Show();
}

void TestStudent2() {
    (new Student2("Zve", 90.6))->Show();
    (new Student2("Coco", 80.5))->Show();
    (new Student2("Swiatech", 99.0))->Show();
    int total = Student2::getTotal();
    float points = Student2::getPoints();
    cout << "There are: " << total << " students. "
         << "the average score is: " << points / total << endl;
}

int main() {
    cout << "------------------------static_class\n";
    TestStaticClass();
    TestStaticVar();
    TestStudent();
    TestStudent2();
    return 0;
}
