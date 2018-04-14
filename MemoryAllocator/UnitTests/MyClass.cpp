//
//  MyClass.cpp
//  MemoryAllocator
//
//  Created by Jieyang Qian on 2/12/18.
//  Copyright © 2018 Jieyang Qian. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include "MyClass.hpp"

using namespace std;

MyClass::MyClass(char a, int x) : a(a), x(x)
{
}

char MyClass::GetA()
{
    return a;
}

int MyClass::GetX()
{
    return x;
}

void* MyClass::operator new(size_t size)
{
    void* p = Allocator::Allocate(size, alignof(MyClass));
    return p;
}

void MyClass::operator delete(void* ptr)
{
    Allocator::Free(ptr);
}



