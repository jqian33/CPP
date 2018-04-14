//
//  PoolAllocator.hpp
//  MemoryAllocator
//
//  A memory allocator that can allocte one object type
//
//  Created by Jieyang Qian on 3/22/18.
//  Copyright © 2018 Jieyang Qian. All rights reserved.
//

#ifndef PoolAllocator_hpp
#define PoolAllocator_hpp

#include <stdio.h>
#include <stdlib.h>
#include <new>

//
class PoolAllocator {

public:
    // Initialize pool by providing number of objects it can hold, object alignement and object size
    static void Init(int numOfBlocks, size_t objectSize, size_t objectAlignment);
    
    // Allocate an object
    static void* Allocate();
    
    // Free an object
    static void Free(void* ptr);
    
    // Free up all memory held by the pool
    static void FreeAll();
    
private:
    // Starting address of pool
    static void* start;
    // First free block
    static void* firstFree;
    static int numberOfBlocks;
    static size_t size;
    static size_t alignment;
    static bool outOfBlocks;
    // A linked list of the address of the blocks are used to keep track of all free memory blocks.
    // Address of start of linked list
    static uintptr_t listStart;
    // Address of end of linked list
    static uintptr_t listEnd;
    
};

#endif /* HeaderPool_hpp */
