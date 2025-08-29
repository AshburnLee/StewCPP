#include <queue>
#include <vector>
#include "lambda.h"

using grammer::lambda::add;  // 直接使用add
using namespace std;
using namespace grammer::lambda; // 直接使用这个namespace下的所有对象

/*
less 谓词：a < b, b (较大的) 更接近堆顶, 故这是最大堆！ CHECK
greater 谓词：a > b, b (较小的) 更接近堆顶，故这是最小堆！  CHECK
*/
void Test_Priority_Queue() {
    priority_queue<Person, vector<Person>, decltype(AgeLess)> root_max(AgeLess);
    priority_queue<Person, vector<Person>, decltype(AgeGreater)> root_min(AgeGreater);

    Person Jack(20, "Jacky");
    Person Tommy(30, "Tommy");
    Person Adam(40, "Adam");

    root_max.push(Jack);
    root_max.push(Tommy);
    root_max.push(Adam);

    root_min.push(Jack);
    root_min.push(Tommy);
    root_min.push(Adam);

    cout << "Root max: \n";
    while (!root_max.empty()) {
        cout << root_max.top().GetName() << " " << root_max.top().GetAge() << endl;
        root_max.pop();
    }

    cout << "Root min: \n";
    while (!root_min.empty()) {
        cout << root_min.top().GetName() << " " << root_min.top().GetAge() << endl;
        root_min.pop();
    }
}

void Test_Lambda() {
    Person *ptr1 = new Person(20, "Jacky");
    Person *ptr2 = new Person(30, "Tommy");

    if (AgeGreater(*ptr1, *ptr2)) {
        cout << "20 is greater than 30\n";
    } else {
        cout << "20 is not greater than 30\n";
    }
}


int main() {
    cout << "lambda adder, exp 15, actual is: [" << add(5) << "]" << endl;
    Test_Priority_Queue();
    return 0;
}
