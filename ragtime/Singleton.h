//
//  Singleton.h
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/09.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#ifndef __gfxe_Singleton__
#define __gfxe_Singleton__

namespace ragtime {

    template <class T>
    class Singleton
    {
    private:
        static T* s_instance;
    public:
        Singleton() { s_instance = nullptr; }
        virtual ~Singleton() {}

        static void CreateInstance() {
            delete s_instance;
            s_instance = new T();
        }

        static T* Instance() { return s_instance; }
    };

    template <class T>
    T* Singleton<T>::s_instance;

}


#endif /* defined(__gfxe_test__Singleton__) */
