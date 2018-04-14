//
//  CustomCompare.hpp
//  MemoryAllocator
//
//  Contain custom compare operators
//
//  Created by Jieyang Qian on 4/12/18.
//  Copyright © 2018 Jieyang Qian. All rights reserved.
//

#ifndef CustomCompare_hpp
#define CustomCompare_hpp

#include <stdio.h>
#include "Header.hpp"


class CustomCompare
{
public:
    // Compare to Header object, will return true if size of a is bigger than size of b
    bool operator()(Header* a, Header* b) const;
    
};


#endif /* CustomCompare_hpp */
