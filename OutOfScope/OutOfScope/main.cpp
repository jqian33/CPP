#include <iostream>
#include "RandomObject.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    RandomObject obj (2);
    std::cout << obj.GetX();
    std::cout << "\n";
    return 0;
}
