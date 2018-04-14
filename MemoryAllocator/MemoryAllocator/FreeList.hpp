//
//  FreeList.hpp
//  MemoryAllocator
//
//  A list that will keep track of all free memory blocks.
//  Top will return the largest block, and Pop will remove the largest block.
//
//  Created by Jieyang Qian on 2/23/18.
//  Copyright © 2018 Jieyang Qian. All rights reserved.
//

#ifndef FreeList_hpp
#define FreeList_hpp

#include <stdio.h>
#include <set>
#include "Header.hpp"
#include "CustomCompare.hpp"

class FreeList
{
public:
    // Initialize an emepty list
    FreeList();
    
    // Push a free memory block to list
    void Push(Header *block);
    
    // Check if list is empty
    bool Empty();
    
    // Get largest memory block from list
    Header* Top();
    
    // Get largest memory block from list and remove it from the list
    Header* Pop();
    
    // Remove specific item
    void Remove(Header* target);
    
    // Get list size;
    int Size();
    
private:
    std::multiset<Header*, CustomCompare> list;
    //bool (FreeList::*fp) (const Header*, const Header*);
};

#endif /* FreeList_hpp */
