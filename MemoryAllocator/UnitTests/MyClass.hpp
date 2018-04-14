//
//  MyClass.h
//  MemoryAllocator
//
//  Dummy class for testing
//
//  Created by Jieyang Qian on 2/12/18.
//  Copyright © 2018 Jieyang Qian. All rights reserved.
//

#ifndef MyClass_h
#define MyClass_h

#include "Allocator.hpp"

class MyClass
{
public:
    // Initialize an instance of MyClass
    MyClass(char a, int x);
    
    // Get char value for A
    char GetA();
    
    // Get int value for X
    int GetX();
  
    // override operator new
    void* operator new(size_t);
    
    // override operator delete
    void operator delete(void* ptr);
    
private:
    char a;
    int x;
};

#endif /* MyClass_h */
