//
//  RandomObject.cpp
//  OutOfScope
//
//  Created by Jieyang Qian on 9/23/17.
//  Copyright © 2017 Jieyang Qian. All rights reserved.
//

#include "RandomObject.h"
#include <iostream>

RandomObject::RandomObject(int x)  : x(x) {
    
}

int RandomObject::GetX() const
{
    return x;
}

RandomObject::~RandomObject() {
    std::cout << "Object out of scope and is going to get destoryed.\n";
}


