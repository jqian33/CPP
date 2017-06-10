//
//  main.cpp
//  Hello World
//
//  Created by Jieyang Qian on 6/9/17.
//  Copyright © 2017 Jieyang Qian. All rights reserved.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    
    // Pointer section
    int i = 5;
    int * pi = &i;
    int ** ppi = &pi;
    std::cout << "i is: " + std::to_string(i) + "\n";
    std::cout << "value at pi is: " + std::to_string(*pi) + "\n";
    std::cout << "value at ppi is: " + std::to_string(**ppi) + "\n";
    
    **ppi = 7;
    std::cout << "i is: " + std::to_string(i) + "\n";
    std::cout << "value at pi is: " + std::to_string(*pi) + "\n";
    std::cout << "value at ppi is: " + std::to_string(**ppi) + "\n";
    
    // Reference section
    int j = 4;
    int &rj = j;
    std::cout << "j is: " + std::to_string(j) + "\n";
    std::cout << "value at rj is: " + std::to_string(rj) + "\n";
    
    rj = 8;
    std::cout << "j is: " + std::to_string(j) + "\n";
    std::cout << "value at rj is: " + std::to_string(rj) + "\n";
    
    return 0;
}
