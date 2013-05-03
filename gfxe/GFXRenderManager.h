//
//  GFXRenderManager.h
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/09.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#ifndef __gfxe_GFXRenderManager__
#define __gfxe_GFXRenderManager__

#include "Singleton.h"
#include "IRenderable.h"
#include <vector>
#include <mutex>
#include <memory>

namespace gfxe {

    enum RenderGroup
    {
        RenderGroup_Solid,
        RenderGroup_Alpha,
        RenderGroup_End
    };

    class GFXRenderer
    {
    private:
        class RenderFuncBase
        {
        public:
            virtual ~RenderFuncBase() {}
            virtual void CallFunc() = 0;
            virtual void* GetTarget() = 0;
        };

        template <class T>
        class RenderFunc : public RenderFuncBase
        {
        private:
            typedef void (T::*render_func_t)();

            T* m_pTarget;
            render_func_t m_pFunc;
        public:
            RenderFunc( T* pTarget, render_func_t pFunc ) :
                m_pTarget( pTarget ), m_pFunc( pFunc ) {}
            void CallFunc() override {
                (m_pTarget->*m_pFunc)();
            }
            void* GetTarget() override {
                return m_pTarget;
            }
        };

    private:
        std::mutex m_mutex;
        std::vector< RenderFuncBase* > m_vecRenderFunc;

    public:
        virtual ~GFXRenderer();
        template <class T>
        void AddRenderFunc( T* pTarget, void (T::*pFunc)() )
        {
//            std::unique_ptr<RenderFuncBase> p;
//            p.reset( new RenderFunc<T>( pTarget, pFunc ) );
            m_vecRenderFunc.push_back( new RenderFunc<T>( pTarget, pFunc ) );
        }
        void RemoveRenderFunc( void* pTarget );
        void Render();
    };

    class GFXRenderManager : public ragtime::Singleton<GFXRenderManager>
    {
    private:
        GFXRenderer m_arrRenderer[ RenderGroup_End ];

    public:
        template <class T>
        void AddRenderFunc( T* pTarget, void (T::*pFunc)(), int renderGroup ) {
            m_arrRenderer[ renderGroup ].AddRenderFunc( pTarget, pFunc );
        }
        void RemoveRenderFunc( void* pTarget );
        void Render();

    };


}

#endif /* defined(__gfxe_test__GFXRenderManager__) */
