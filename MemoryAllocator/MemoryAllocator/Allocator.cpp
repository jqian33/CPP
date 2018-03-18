//
//  Allocator.cpp
//  MemoryAllocator
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
    Header* firstBlock = (Header*)start;
    firstBlock->Initialize(size - sizeof(Header));
    freeList->Push(firstBlock);
    spaceUsed = sizeof(Header);
    numberOfBlocks = 1;
}

void* Allocator::Allocate(size_t objectSize)
{
    Header* freeBlock = freeList->Top();
    if (freeBlock != nullptr) {
        size_t blockSize = freeBlock->GetSize();
        if (blockSize >= objectSize) {
            freeList->Pop();
            // When the free block is larger than the size of the object we need to
            // create a new block with left over spaces
            size_t leftover = blockSize - objectSize;
            if (leftover > sizeof(Header)) {
                freeBlock->SetSize(objectSize);
                size_t newBlockSize = leftover - sizeof(Header);
                Header* newBlock = (Header*)((char*)freeBlock + sizeof(Header) + objectSize);
                newBlock->Initialize(newBlockSize);
                newBlock->SetPrev(freeBlock);
                newBlock->SetNext(freeBlock->GetNext());
                freeBlock->SetNext(newBlock);
                freeList->Push(newBlock);
                spaceUsed += sizeof(Header);
                numberOfBlocks += 1;
            }
            spaceUsed += objectSize;
            freeBlock->SetUsed();
            return (char*)freeBlock + sizeof(Header);
        }
    }
    throw std::bad_alloc();
}

void Allocator::Free(void* ptr)
{
    Header* current = (Header*)((char*)ptr - sizeof(Header));
    spaceUsed -= sizeof(Header) + current->GetSize();
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
            size_t mergePrevSize = sizeof(Header) + current->GetSize() + prev->GetSize();
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
            size_t mergeNextSize = current->GetSize() + sizeof(Header) + next->GetSize();
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
