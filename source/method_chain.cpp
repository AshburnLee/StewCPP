#include <iostream>
#include "method_chain.hpp"

int main () {
    Calculator cal;
    int res = cal.add(5)
                 .sub(5)
                 .add(10)
                 .sub(10)
                 .GetResult();
    std::cout << "== res: " << res << "\n";
    return 0;
}
