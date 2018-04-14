//
//  Allocator.cpp
//  MemoryAllocator
//
//  Implementation of a general purpose memory allocator.
//  Objects are always allocated on the largest free block,
//  any excess large enough will result in a new free block.
//  When a block is freed, the allocator will merge it with neighboring free blocks to form a larger one.
//
//  Created by Jieyang Qian on 2/18/18.
//  Copyright © 2018 Jieyang Qian. All rights reserved.
//

#include "Allocator.hpp"

size_t Allocator::totalSize;
size_t Allocator::spaceUsed;
void* Allocator::start;
FreeList* Allocator::freeList;
int Allocator::numberOfBlocks;

void Allocator::Init(size_t size)
{
    totalSize = size;
    start = new char [size];
    freeList = new FreeList();
    void* alignedHeaderPtr = Allocator::GetAlignedPtr(start, alignof(Header));
    Header* firstBlock = (Header*)alignedHeaderPtr;
    size_t headerSize = Allocator::GetSize(alignedHeaderPtr, sizeof(Header));
    firstBlock->Initialize(size - headerSize);
    freeList->Push(firstBlock);
    spaceUsed = headerSize;
    numberOfBlocks = 1;
}

void* Allocator::Allocate(size_t objectSize, uintptr_t alignment)
{
    Header* freeBlock = freeList->Top();
    if (freeBlock != nullptr) {
        size_t blockSize = freeBlock->GetSize();
        void* unalignedBlockPtr = Allocator::GetNextUnalignedPtr(freeBlock, sizeof(Header));
        size_t actualObjSize = Allocator::CalculateSize(unalignedBlockPtr, objectSize, alignment);
        if (blockSize >= actualObjSize) {
            // Remove free block from free list and calculate aligned address for object pointer
            freeList->Pop();
            void* alignedBlockPtr = Allocator::GetAlignedPtr(unalignedBlockPtr, alignment);
            freeBlock->SetSize(actualObjSize);
            
            // When the free block is larger than the size of the object we need to
            // create a new block with left over spaces
            size_t leftover = blockSize - actualObjSize;
            void* unalignedNextBlockPtr = GetNextUnalignedPtr(alignedBlockPtr, objectSize);
            size_t newHeaderSize = Allocator::CalculateSize(unalignedNextBlockPtr, sizeof(Header), alignof(Header));
            if (leftover > newHeaderSize) {
                size_t newBlockSize = leftover - newHeaderSize;
                Header* newBlock = (Header*)Allocator::GetAlignedPtr(unalignedNextBlockPtr, alignof(Header));
                newBlock->Initialize(newBlockSize);
                newBlock->SetPrev(freeBlock);
                newBlock->SetNext(freeBlock->GetNext());
                freeBlock->SetNext(newBlock);
                freeList->Push(newBlock);
                spaceUsed += newHeaderSize;
                numberOfBlocks += 1;
            }
            spaceUsed += actualObjSize;
            freeBlock->SetUsed();
            return alignedBlockPtr;
        }
    }
    throw std::bad_alloc();
}

void Allocator::Free(void* ptr)
{
    Header* current = (Header*)Allocator::GetHeader(ptr);
    spaceUsed -= Allocator::GetSize(current, sizeof(Header)) + current->GetSize();
    Header* prev = current->GetPrev();
    Header* next = current->GetNext();
    bool merge = false;
    // merge with previous block if it is free
    if (prev) {
        if (prev->IsFree()) {
            merge = true;
            freeList->Remove(prev);
            freeList->Remove(current);
            prev->SetNext(next);
            if (next != nullptr) {
                next->SetPrev(prev);
            }
            size_t mergePrevSize = Allocator::GetSize(current, sizeof(Header)) + current->GetSize() + prev->GetSize();
            prev->SetSize(mergePrevSize);
            current = prev;
            prev = current->GetPrev();
            freeList->Push(current);
            numberOfBlocks -= 1;
        }
    }
    // merge with next block if it is free
    if (next) {
        if (next->IsFree()) {
            merge = true;
            freeList->Remove(current);
            freeList->Remove(next);
            Header* nextNext = next->GetNext();
            current->SetNext(nextNext);
            if (nextNext != nullptr) {
                nextNext->SetPrev(prev);
            }
            size_t mergeNextSize = current->GetSize() + Allocator::GetSize(next, sizeof(Header)) + next->GetSize();
            current->SetSize(mergeNextSize);
            freeList->Push(current);
            numberOfBlocks -= 1;
        }
    }
    if (!merge)
    {
        freeList->Push(current);
        current->SetFree();
    }
}

size_t Allocator::TotalSize()
{
    return totalSize;
}

size_t Allocator::SpacesUsed()
{
    return spaceUsed;
}

int Allocator::NumberOfFreeBlocks()
{
    return freeList->Size();
}

int Allocator::NumberOfBlocks()
{
    return numberOfBlocks;
}

void Allocator::FreeAll()
{
    delete [] (char*)start;
    delete freeList;
    totalSize = 0;
    spaceUsed = 0;
    numberOfBlocks = 0;
}

ptrdiff_t Allocator::CalculateAdjustment(void* pointer, uintptr_t alignment)
{
    // Calculate the adjustment by masking off the lower bits
    // of the address, to determine how misaligned it is.
    uintptr_t rawAddress = reinterpret_cast<uintptr_t>(pointer);
    size_t mask = (alignment - 1);
    uintptr_t misalignment = (rawAddress & mask);
    ptrdiff_t adjustment = alignment - misalignment;
    return adjustment;
}

size_t Allocator::CalculateSize(void* pointer, size_t objectSize, uintptr_t alignment)
{
    ptrdiff_t adjustment = Allocator::CalculateAdjustment(pointer, alignment);
    size_t actualSize = objectSize + adjustment;
    return actualSize;
}

void* Allocator::GetAlignedPtr(void* pointer, uintptr_t alignment)
{
    // Calculate the adjusted address
    uintptr_t rawAddress = reinterpret_cast<uintptr_t>(pointer);
    ptrdiff_t adjustment = Allocator::CalculateAdjustment(pointer, alignment);
    uintptr_t alignedAddress = rawAddress + adjustment;
    
    // Store adjustment in memory location 1 byte ahead of the adjusted address
    uint8_t* pAlignedAddress = reinterpret_cast<uint8_t*>(alignedAddress);
    pAlignedAddress[-1] = static_cast<uint8_t>(adjustment);
    
    return static_cast<void*>(pAlignedAddress);
}

uint8_t Allocator::GetAdjustment(void* pointer)
{
    uint8_t* pAlignedAddress = reinterpret_cast<uint8_t*>(pointer);
    uint8_t adjustment = pAlignedAddress[-1];
    return adjustment;
}

size_t Allocator::GetSize(void* pointer, size_t objectSize)
{
    uint8_t adjustment = Allocator::GetAdjustment(pointer);
    size_t actualSize = objectSize + adjustment;
    return actualSize;
}

void* Allocator::GetUnAlignedPtr(void* pointer)
{
    uint8_t adjustment = Allocator::GetAdjustment(pointer);
    uintptr_t alignedAddress = reinterpret_cast<uintptr_t>(pointer);
    uintptr_t unalignedAddress = alignedAddress - adjustment;
    return reinterpret_cast<void*>(unalignedAddress);
}

void* Allocator::GetNextUnalignedPtr(void* pointer, size_t objectSize)
{
    uintptr_t rawAddress = reinterpret_cast<uintptr_t>(pointer);
    uintptr_t nextRawAddress = rawAddress + objectSize;
    return reinterpret_cast<void*>(nextRawAddress);
}

void* Allocator::GetHeader(void* pointer)
{
    void* unalignedAddress = Allocator::GetUnAlignedPtr(pointer);
    uintptr_t rawAddress = reinterpret_cast<uintptr_t>(unalignedAddress);
    uintptr_t alignedHeaderAddress = rawAddress - sizeof(Header);
    return reinterpret_cast<void*>(alignedHeaderAddress);
}
