//
//  FreeList.hpp
//  MemoryAllocator
//
//  Created by Jieyang Qian on 2/23/18.
//  Copyright © 2018 Jieyang Qian. All rights reserved.
//

#ifndef FreeList_hpp
#define FreeList_hpp

#include <stdio.h>
#include <set>
#include "Header.hpp"

 //List of free memory blocks (Only contain pointers to memory block headers)
class FreeList
{
public:
    // Initialize an emepty list
    FreeList();
    // Add a free memory block to list
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
    std::multiset<Header*> list;
    bool (FreeList::*fp) (Header*, Header*);
    bool CompareSize(Header* a, Header* b);
};

#endif /* FreeList_hpp */
