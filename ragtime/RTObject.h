//
//  RTObject.h
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/05.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#ifndef __ragtime_RTObject__
#define __ragtime_RTObject__

#include <pthread.h>

namespace ragtime {

    class RTObject
    {
    private:
        int m_nRefCnt;
        

    public:
        RTObject();
        virtual ~RTObject();
        inline void Retain() { ++m_nRefCnt; };
        inline void Release() { --m_nRefCnt; };
    };
    
}

#endif /* defined(__ragtime_RTObject__) */
