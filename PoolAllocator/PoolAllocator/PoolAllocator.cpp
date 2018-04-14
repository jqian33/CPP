//
//  HeaderPool.cpp
//  MemoryAllocator
//
//  Created by Jieyang Qian on 3/22/18.
//  Copyright © 2018 Jieyang Qian. All rights reserved.
//

#include "PoolAllocator.hpp"

void* PoolAllocator::start;
uintptr_t PoolAllocator::listStart;
uintptr_t PoolAllocator::listEnd;
int PoolAllocator::numberOfBlocks;
size_t PoolAllocator::size;
size_t PoolAllocator::alignment;
bool PoolAllocator::outOfBlocks;

// Allocate a memory pool of object with identical size
void PoolAllocator::Init(int numOfBlocks, size_t objectSize, size_t objectAlignment)
{
    if (numOfBlocks > 0) {
        outOfBlocks = false;
    }
    else {
        outOfBlocks = true;
        return;
    }
    numberOfBlocks = numOfBlocks;
    size = objectSize;
    alignment = objectAlignment;
    // Add extra space = objectAlignment, because first block will need space to readjust for alignment
    start = new char [numberOfBlocks * size + objectAlignment];
    
    // Calculate the adjustment by masking off the lower bits
    // of the address, to determine how misaligned it is.
    uintptr_t rawAddress = reinterpret_cast<uintptr_t>(start);
    size_t mask = (alignment - 1);
    uintptr_t misalignment = (rawAddress & mask);
    ptrdiff_t adjustment = alignment - misalignment;
    
    // Calculate the adjusted address
    uintptr_t alignedAddress = rawAddress + adjustment;
    listStart = alignedAddress;
    uintptr_t address = alignedAddress;
    
    // Set up a linked list of all blocks, initally all blocks are free.
    // The pointers are stored in the first byte of the block it self to save space.
    for (int i = 0; i < numberOfBlocks; i++) {
        uintptr_t nextAddress = address + size;
        uintptr_t* pAddress = (uintptr_t*)address;
        // Do not set pointer to next memory block when reaching end of the pool
        if (i < numberOfBlocks - 1)
        {
            *pAddress = nextAddress;
            address = nextAddress;
        }
        else {
            listEnd = address;
        }
    }
}

// Return the address of a free block.
// This will always be the block at the top of the list;
void* PoolAllocator::Allocate()
{
    if (!outOfBlocks)
    {
        uintptr_t freeBlock = listStart;
        if (listStart == listEnd) {
            outOfBlocks = true;
        }
        else {
            uintptr_t* pListStart = (uintptr_t*)listStart;
            uintptr_t nextAddress = *pListStart;
            listStart = nextAddress;
        }
        return (void*)freeBlock;
    }
    else {
        throw std::bad_alloc();
    }
}

// Free a memory block and append it to the end of the list
void PoolAllocator::Free(void* ptr)
{
    uintptr_t address = reinterpret_cast<uintptr_t>(ptr);
    if (outOfBlocks) {
        listEnd = address;
        listStart = address;
        outOfBlocks = false;
    }
    else {
        uintptr_t* pListEnd = (uintptr_t*)listEnd;
        *pListEnd = address;
        listEnd = address;
    }
}

// Release all memory held by the pool
void PoolAllocator::FreeAll()
{
    delete [] (char*)start;
}
