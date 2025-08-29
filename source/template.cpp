#include "template.h"

using namespace std;
using ::grammer::my_template::MyPair;


int main() {
    MyPair<double, double> p1(3.12, 2.34);
    MyPair<double, int> p2(3.12, 2);
    p1.Log();

    return 0;
}
