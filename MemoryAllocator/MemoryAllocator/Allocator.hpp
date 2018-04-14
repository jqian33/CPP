//
//  Allocator.hpp
//  MemoryAllocator
//
//  General purpose allocator that can allocate and free objects of any arbitrary size.
//  Allocation will always return aligned memory address.
//
//  Created by Jieyang Qian on 2/18/18.
//  Copyright © 2018 Jieyang Qian. All rights reserved.
//

#ifndef Allocator_hpp
#define Allocator_hpp

#include <stdio.h>
#include "FreeList.hpp"
#include "Header.hpp"

class Allocator
{
public:
    
    // Initialize Allocator
    static void Init(size_t size);
    
    // Free up all memory initialized by Allocator
    static void FreeAll();
    
    // Allocate a block in memory for an object
    static void* Allocate(size_t objectSize, uintptr_t alignment);
    
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
    
    // Calculate adjustment needed to align a pointer address
    static ptrdiff_t CalculateAdjustment(void* pointer, uintptr_t alignment);
    
    // Calculate actual size of object including adustment needed for alignment
    static size_t CalculateSize(void* pointer, size_t objectSize, uintptr_t alignment);
    
    // Pass in an unaligned pointer address and return a aligned pointer address
    static void* GetAlignedPtr(void* pointer, uintptr_t alignment);
    
    // Get adjustment made for an aligned pointer
    static uint8_t GetAdjustment(void* pointer);
    
    // Pass in an unaligned pointer address and calculate the actual size include padding bytes for alignment adjustment
    static size_t GetSize(void* pointer, size_t objectSize);
    
    // Pass in an aligned pointer address and return an unaligned pointer address
    static void* GetUnAlignedPtr(void* pointer);
    
    // Pass in an aligned pointer address, and get next available unaligned pointer address
    static void* GetNextUnalignedPtr(void* pointer, size_t objectSize);
    
    // Pass in aligned object pointer and return aligned pointer of immediate header
    static void* GetHeader(void* pointer);
};


#endif /* Allocator_hpp */


