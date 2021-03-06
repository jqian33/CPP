//
//  MyClass.cpp
//  PoolAllocator
//
//  Created by Jieyang Qian on 2/12/18.
//  Copyright © 2018 Jieyang Qian. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include "MyClass.hpp"
#include "PoolAllocator.hpp"

using namespace std;

MyClass::MyClass(char a, int x) : a(a), x(x)
{
}

MyClass::MyClass()
{
    a = 'a';
    x = 0;
}

char MyClass::GetA()
{
    return a;
}

int MyClass::GetX()
{
    return x;
}

// override operator new
void* MyClass::operator new(size_t size)
{
    void* p = PoolAllocator::Allocate();
    return p;
}

// override operator delete
void MyClass::operator delete(void* ptr)
{
    PoolAllocator::Free(ptr);
}



