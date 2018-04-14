//
//  LargeClass.hpp
//  MemoryAllocator
//
//  Dummy class for testing. It is significantly bigger than MyClass.
//
//  Created by Jieyang Qian on 4/14/18.
//  Copyright © 2018 Jieyang Qian. All rights reserved.
//

#ifndef LargeClass_hpp
#define LargeClass_hpp

#include <stdio.h>
#include <string>
#include "Allocator.hpp"

class LargeClass
{
public:
    // Initialize an instance of LargeClass
    LargeClass(std::string a, std::string b, std::string c, std::string d, std::string e, std::string f);
    
    // Get string value for A
    std::string GetA();
    
    // Get string value for B
    std::string GetB();
    
    // Get string value for C
    std::string GetC();
    
    // Get string value for D
    std::string GetD();
    
    // Get string value for E
    std::string GetE();
    
    // Get string value for F
    std::string GetF();
    
    // override operator new
    void* operator new(size_t);
    
    // override operator delete
    void operator delete(void* ptr);
    
private:
    std::string a;
    std::string b;
    std::string c;
    std::string d;
    std::string e;
    std::string f;
};

#endif /* LargeClass_hpp */
