//
//  Header.cpp
//  MemoryAllocator
//
//  Created by Jieyang Qian on 2/17/18.
//  Copyright © 2018 Jieyang Qian. All rights reserved.
//

#include "Header.hpp"

using namespace std;

void Header::Initialize(size_t objectSize)
{
    size = objectSize;
    prev = nullptr;
    next = nullptr;
    isFree = true;
}

void* Header::operator new(size_t size)
{
    throw logic_error("Invalid function call.");
}

void Header::operator delete(void* ptr)
{
}

Header* Header::GetNext()
{
    return next;
}

void Header::SetSize(size_t objectSize)
{
    size = objectSize;
}

Header* Header::GetPrev()
{
    return prev;
}

size_t Header::GetSize()
{
    return size;
}

const size_t Header::GetSize() const
{
    return size;
}

bool Header::IsFree()
{
    return isFree;
}

void Header::SetNext(Header* nextBlock)
{
    next = nextBlock;
}

void Header::SetPrev(Header* prevBlock)
{
    prev = prevBlock;
}

void Header::SetFree()
{
    isFree = true;
}

void Header::SetUsed()
{
    isFree = false;
}
