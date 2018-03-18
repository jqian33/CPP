//
//  Header.hpp
//  MemoryAllocator
//
//  Created by Jieyang Qian on 2/17/18.
//  Copyright © 2018 Jieyang Qian. All rights reserved.
//

#ifndef Header_hpp
#define Header_hpp

#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Header
{
    
public:
    void* operator new(size_t size);
    void operator delete(void* ptr);
    Header* GetNext();
    Header* GetPrev();
    bool IsFree();
    size_t GetSize();
    void SetSize(size_t objectSize);
    void Initialize(size_t objectSize);
    void SetNext(Header* nextBlock);
    void SetPrev(Header* prevBlock);
    void SetFree();
    void SetUsed();
    
private:
    // If memory block if free
    bool isFree;
    // Size of object in memory block
    size_t size;
    // Pointer to next block in physical memory
    Header* next;
    // Pointer to previous block in physical memory
    Header* prev;
    
};

#endif /* Header_hpp */
