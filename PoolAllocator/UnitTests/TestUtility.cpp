//
//  TestUtility.cpp
//  MemoryAllocator
//
//  Created by Jieyang Qian on 3/31/18.
//  Copyright © 2018 Jieyang Qian. All rights reserved.
//

#include "TestUtility.hpp"

bool TestUtility::IsAligned(void* ptr, size_t objectAlignment)
{
    uintptr_t rawAddress = reinterpret_cast<uintptr_t>(ptr);
    uintptr_t remainder = rawAddress % (uintptr_t)objectAlignment;
    if (remainder == 0) {
        return true;
    }
    else {
        return false;
    }
};

