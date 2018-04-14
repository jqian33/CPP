//
//  CustomCompare.cpp
//  MemoryAllocator
//
//  Created by Jieyang Qian on 4/12/18.
//  Copyright © 2018 Jieyang Qian. All rights reserved.
//

#include "CustomCompare.hpp"

bool CustomCompare::operator()(Header* a, Header* b) const
{
    if (a->GetSize() > b->GetSize()) {
        return true;
    }
    else
    {
        return false;
    }
}


