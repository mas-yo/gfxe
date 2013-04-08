//
//  stlutil.h
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/05.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#ifndef __gfxe_test__stlutil__
#define __gfxe_test__stlutil__

#include <vector>

template <class T>
void delete_all( std::vector<T> &vec )
{
    typename std::vector<T>::iterator it = vec.begin();
    for( ; it != vec.end(); ++it ) {
        delete (*it);
    }
    vec.clear();
}

#endif /* defined(__gfxe_test__stlutil__) */
