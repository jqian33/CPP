//
//  MyClass.cpp
//  Pointer and Reference
//
//  Created by Jieyang Qian on 2/12/18.
//  Copyright © 2018 Jieyang Qian. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include "MyClass.h"

using namespace std;

MyClass::MyClass(char a, char b, int x, int y, int z) : a(a), b(b), x(x), y(y), z(z)
{
}

MyClass::MyClass()
{
    a = 'a';
    b = 'b';
    x = 0;
    y = 0;
    z = 0;
}

// override operator new
void* MyClass::operator new(size_t size)
{
    cout << "Overloaded operator new called." << endl;
    void *p = malloc(size);
    return p;
}

// override operator delete
void MyClass::operator delete(void* ptr)
{
    cout << "Overloaded operator delete called." << endl;
    free(ptr);
}



