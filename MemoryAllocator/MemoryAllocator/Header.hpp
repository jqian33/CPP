//
//  Header.hpp
//  MemoryAllocator
//
//  Header that holds meta data about a memory block
//
//  Created by Jieyang Qian on 2/17/18.
//  Copyright © 2018 Jieyang Qian. All rights reserved.
//

#ifndef Header_hpp
#define Header_hpp

#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

class Header
{
    
public:
    // Initailze the header for a memory block by providing the size
    void Initialize(size_t objectSize);
    
    // Pointer to next memory block
    Header* GetNext();
    
    // Pointer to previous memory block
    Header* GetPrev();
    
    // Check if memory block is free
    bool IsFree();
    
    // Get size of memory block
    size_t GetSize();
    
    // Get size of memory block
    const size_t GetSize() const;
    
    // Set size of memory block
    void SetSize(size_t objectSize);
    
    // Set reference to next memory block
    void SetNext(Header* nextBlock);
    
    // Set reference to previous memory block
    void SetPrev(Header* prevBlock);
    
    // Mark memory block as free
    void SetFree();
    
    // Mark memory block as used
    void SetUsed();
    
    // Override new operator
    void* operator new(size_t size);
    
    // Override delete operator
    void operator delete(void* ptr);
    
private:
    bool isFree;
    size_t size;
    Header* next;
    Header* prev;
    
};

#endif /* Header_hpp */
