//
//  TargetFunction.h
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/05/16.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#ifndef __gfxe_test__TargetFunction__
#define __gfxe_test__TargetFunction__

namespace gfxe {

    template <class R, class... A>
    class ITargetFunction
    {
    public:
        virtual ~ITargetFunction() {}
        virtual R call( A... ) = 0;
    };

    template <class T, class R, class... A >
    class TargetFunction : public ITargetFunction< R, A... >
    {
    public:
        typedef R (T::*func_t)( A... );

        TargetFunction( T* target, func_t func ) :
            _target( target ), _func( func ) {}

    private:
        T* _target;
        func_t _func;

    public:
        void set( T* target, func_t func )
        {
            _target = target;
            _func = func;
        }

        T* getTarget()
        {
            return _target;
        }

        func_t getFunction()
        {
            return _func;
        }

        virtual R call( A... params )
        {
            if( _target != nullptr && _func != nullptr )
                return (_target->*_func)( params... );
            return R();
        }

        static ITargetFunction<R,A...>* newTargetFunction( T* obj, func_t func )
        {
            return new TargetFunction<T, R, A...>( obj, func );
        }

    };
}
#endif /* defined(__gfxe_test__TargetFunction__) */
