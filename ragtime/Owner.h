//
//  RTOwn.h
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/08.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#ifndef __ragtime_RTOwn__
#define __ragtime_RTOwn__

#include <functional>

namespace ragtime
{
    template <class T>
    class PredNormalDelete {
    public:
        void operator()( T* obj ) { delete obj; }
    };

    template <class T>
    class PredArrayDelete {
    public:
        void operator()( T* obj) { delete [] obj; }
    };


    template <class T>
    class RTOwn
    {
    private:

        T* m_pObj;
        std::function< void ( T* ) > m_fncDeleter;

        // prevent copy
        RTOwn<T> operator=( RTOwn<T>& obj ) {}
        RTOwn( RTOwn<T>& obj ) {}

    public:
        static const std::function< void( T* ) > normalDeleter;
        static const std::function< void( T* ) > arrayDeleter;

        RTOwn() : m_pObj(nullptr), m_fncDeleter( RTOwn<T>::normalDeleter ) {
        }
        RTOwn( T* obj, std::function< void( T* ) > fncDeleter = RTOwn<T>::normalDeleter ) : m_pObj(obj), m_fncDeleter( fncDeleter ) {
        }
        ~RTOwn() {
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
    using own = RTOwn<T>;

    template <class T>
    const std::function< void( T* ) > RTOwn<T>::normalDeleter = []( T* obj ) {
        delete obj;
    };
    template <class T>
    const std::function< void( T* ) > RTOwn<T>::arrayDeleter = []( T* obj ) {
        delete [] obj;
    };

}

#endif /* defined(__gfxe_test__RTOwn__) */
