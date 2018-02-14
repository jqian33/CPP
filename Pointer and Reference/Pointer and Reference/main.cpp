//
//  main.cpp
//  Hello World
//
//  Created by Jieyang Qian on 6/9/17.
//  Copyright © 2017 Jieyang Qian. All rights reserved.
//

#include <iostream>
#include "MyClass.h"

using namespace std;

int main(int argc, const char * argv[]) {
    cout << "Hello, World!" << endl;
    
    // Pointer section
    int i = 5;
    int * pi = &i;
    int ** ppi = &pi;
    cout << "i is: " << std::to_string(i) << endl;
    cout << "value at pi is: " << std::to_string(*pi) << endl;
    cout << "value at ppi is: " << std::to_string(**ppi) << endl;

    **ppi = 7;
    cout << "i is: " << to_string(i) << endl;
    cout << "value at pi is: " << to_string(*pi) << endl;
    cout << "value at ppi is: " << to_string(**ppi) << endl;

    // Reference section
    int j = 4;
    int &rj = j;
    cout << "j is: " << to_string(j) << endl;
    cout << "value at rj is: " << to_string(rj) << endl;

    rj = 8;
    cout << "j is: " << to_string(j) << endl;
    cout << "value at rj is: " << to_string(rj) << endl;
    
    // memory is a pointer to memory location of first block for char[];
    char *memory = new char[10];
    memory[0] = 'z';
    memory[1] = 'p';
    cout << &memory << endl;
    delete [] memory;
    
    // Example of class that ovrrides operator new and operator delete
    MyClass *myClass = new MyClass('p', 'z', 9, 10, 11);
    cout << "Size of MyClass is: " + to_string(sizeof(MyClass)) + "." << endl;
    delete myClass;
    
    return 0;
}
