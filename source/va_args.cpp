#include <iostream>
#include <string>

#define DEBUG_PRINT(...)   \
std::cout << "DEBUG: " << __VA_ARGS__ << std::endl;

void debug_print_main() {
    int x = 42;
    // prints "DEBUG: The value of x is 42"
    DEBUG_PRINT("The value of x is " << x); 
}


int main() {
    debug_print_main();
    return 0;
}
