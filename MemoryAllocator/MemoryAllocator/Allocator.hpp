//
//  Allocator.hpp
//  MemoryAllocator
//
//  Created by Jieyang Qian on 2/18/18.
//  Copyright © 2018 Jieyang Qian. All rights reserved.
//

#ifndef Allocator_hpp
#define Allocator_hpp

#include <stdio.h>
#include "FreeList.hpp"

class Allocator
{
public:
    
    // Initialize Allocator
    static void Init(size_t size);
    // Free up all memory initialized by Allocator
    static void FreeAll();
    // Allocate a block in memory for an object
    static void* Allocate(size_t objectSize);
    // Free up memory block
    static void Free(void* ptr);
    // Get total size of Allocator pool
    static size_t TotalSize();
    // Get spaces used in bytes
    static size_t SpacesUsed();
    // Get number of free blocks available
    static int NumberOfFreeBlocks();
    // Get total number of blocks
    static int NumberOfBlocks();
    
private:
    static void* start;
    static size_t spaceUsed;
    static size_t totalSize;
    static FreeList* freeList;
    static int numberOfBlocks;
};


#endif /* Allocator_hpp */


