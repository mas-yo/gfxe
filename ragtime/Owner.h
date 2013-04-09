//
//  Owner.h
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/08.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#ifndef __ragtime_Owner__
#define __ragtime_Owner__

#include <functional>

namespace ragtime
{
    template <class T>
    class Owner
    {
    private:

        T* m_pObj;
        std::function< void ( T* ) > m_fncDeleter;

        // prevent copy
        Owner<T> operator=( Owner<T>& obj ) {}
        Owner( Owner<T>& obj ) {}

    public:
        static const std::function< void( T* ) > normalDeleter;
        static const std::function< void( T* ) > arrayDeleter;

        Owner() : m_pObj(nullptr), m_fncDeleter( Owner<T>::normalDeleter ) {
        }
        Owner( T* obj, std::function< void( T* ) > fncDeleter = Owner<T>::normalDeleter ) : m_pObj(obj), m_fncDeleter( fncDeleter ) {
        }
        ~Owner() {
            m_fncDeleter( m_pObj );
        }
        void SetPointer( T* obj, std::function< void( T* ) > fncDeleter ) {
            if( !m_pObj ) {
                m_pObj = obj;
                m_fncDeleter = fncDeleter;
            }
        }
        operator T*() { return m_pObj; }
        T* operator->() {
            return m_pObj;
        }
    };

    template<class T>
    using own = Owner<T>;

    template <class T>
    const std::function< void( T* ) > Owner<T>::normalDeleter = []( T* obj ) {
        delete obj;
    };
    template <class T>
    const std::function< void( T* ) > Owner<T>::arrayDeleter = []( T* obj ) {
        delete [] obj;
    };

}

#endif /* defined(__gfxe_test__RTOwn__) */
