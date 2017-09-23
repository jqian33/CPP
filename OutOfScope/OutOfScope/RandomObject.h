//
//  RandomObject.h
//  OutOfScope
//
//  Created by Jieyang Qian on 9/23/17.
//  Copyright © 2017 Jieyang Qian. All rights reserved.
//

#ifndef RandomObject_h
#define RandomObject_h

class RandomObject
{
    public:
        RandomObject(int x);
        int GetX() const;
        ~RandomObject();
    
    private:
        int x;
};


#endif /* RandomObject_h */
