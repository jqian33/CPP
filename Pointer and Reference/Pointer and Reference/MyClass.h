//
//  MyClass.h
//  Pointer and Reference
//
//  Created by Jieyang Qian on 2/12/18.
//  Copyright © 2018 Jieyang Qian. All rights reserved.
//

#ifndef MyClass_h
#define MyClass_h

class MyClass
{
    public:
        MyClass();
        MyClass(char a, char b, int x, int y, int z);
        void* operator new(size_t);
    void operator delete(void* ptr);
    
    private:
        char a;
        char b;
        int x;
        int y;
        int z;
};

#endif /* MyClass_h */
