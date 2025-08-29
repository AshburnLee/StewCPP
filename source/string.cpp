#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "string.hpp"

using namespace std;
int main() {
    vector<string> s = {"apple", "banana", "ape", "application"};
    std::sort(s.begin(), s.end(), [](const string a, const string b){ return a < b; });

    for (auto word: s) {
        cout << word <<" ";
    }
    cout << endl;
    return 0;
}
