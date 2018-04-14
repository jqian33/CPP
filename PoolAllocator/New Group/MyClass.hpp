//
//  MyClass.h
//  PoolAllocator
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
        MyClass(char a, int x);
        char GetA();
        int GetX();
  
        void* operator new(size_t);
        void operator delete(void* ptr);
    
    private:
        char a;
        int x;
};

#endif /* MyClass_h */
