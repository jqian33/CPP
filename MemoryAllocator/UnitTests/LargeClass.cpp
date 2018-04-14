//
//  LargeClass.cpp
//  MemoryAllocator
//
//  Created by Jieyang Qian on 4/14/18.
//  Copyright © 2018 Jieyang Qian. All rights reserved.
//

#include "LargeClass.hpp"

using namespace std;

LargeClass::LargeClass(string a, string b, string c, string d, string e, string f) : a(a), b(b), c(c), d(d), e(e), f(f)
{
}

string LargeClass::GetA()
{
    return a;
}

string LargeClass::GetB()
{
    return b;
}

string LargeClass::GetC()
{
    return c;
}

string LargeClass::GetD()
{
    return d;
}

string LargeClass::GetE()
{
    return e;
}

string LargeClass::GetF()
{
    return f;
}

void* LargeClass::operator new(size_t size)
{
    void* p = Allocator::Allocate(size, alignof(LargeClass));
    return p;
}

void LargeClass::operator delete(void* ptr)
{
    Allocator::Free(ptr);
}
