//
//  TestUtility.hpp
//  MemoryAllocator
//
//  Utility class that provide methods for testing
//
//  Created by Jieyang Qian on 3/31/18.
//  Copyright © 2018 Jieyang Qian. All rights reserved.
//

#ifndef TestUtility_hpp
#define TestUtility_hpp

#include <stdio.h>

class TestUtility {

public:
    // Check if a pointer to an object is aligned (Address of object need to be multiple of object alignment)
    static bool IsAligned(void* ptr, size_t objectAlignment);

};

#endif /* TestUtility_hpp */
