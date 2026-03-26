// for windows:
// cd build
// cmake -G "MinGW Makefiles" ..
// make -j2

// for Linux:
// cd build
// cmake ..
// make -j

#include <iostream>
#include <string>
#include "p-top_interview_150.h"   // top_150::Launcher()
#include "collection_sorting.h"  // collection_sorting::Launcher()
#include "p-huawei.hpp"  // huawei::Launcher()
#include "p-ByteDance.hpp" 


using namespace std;

int main() {
    top_150::Launcher();
    // huawei::Launcher();
    /*
    printf("-------------------collection sorting \n");
    collection_sorting::Launcher();
    */
    return 0;
}
