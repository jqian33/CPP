//
//  FreeList.cpp
//  MemoryAllocator
//
//  Implementation of free list using a multiset.
//  This is mostly just a wrapper class for std::multiset.
//
//  Created by Jieyang Qian on 2/23/18.
//  Copyright © 2018 Jieyang Qian. All rights reserved.
//

#include "FreeList.hpp"

FreeList::FreeList()
{
    //fp = &FreeList::CompareSize;
    //std::multiset<Header*, bool(FreeList::*)(const Header*, const Header*)> list(fp);
    std::multiset<Header*, CustomCompare> list;
}

void FreeList::Push(Header* block)
{
    list.insert(block);
}

bool FreeList::Empty()
{
    return list.empty();
}

int FreeList::Size()
{
    return (int)list.size();
}

Header* FreeList::Top()
{
    std::set<Header*>::iterator it = list.begin();
    return *it;
}

Header* FreeList::Pop()
{
    std::set<Header*>::iterator it = list.begin();
    Header* top = *it;
    list.erase(it);
    return top;
}

void FreeList::Remove(Header* target)
{
    list.erase(target);
}

